 ///
 /// @file    tcpserver.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-02-09 14:17:21
 ///
 
#include "func.hpp"
#define MAX_EVENT_NUMBER 1024
#define BUF_SIZE 10
void setNonbloking(int fd){
//int fcntl(int fd, int cmd, ... /* arg */ );
//先get 后set
		int old_option=fcntl(fd,F_GETFL);
		assert(-1!=old_option);
		int new_option=old_option|O_NONBLOCK;

		int ret=fcntl(fd,F_SETFL,new_option);
		assert(-1!=ret);
}
void delFd(int epfd,int fd){
			struct epoll_event event;
			event.events=EPOLLIN;
			event.data.fd=fd;
			int ret=epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&event);//目前用来监控可写，但其也可以监控可读
			assert(-1!=ret);

}

void addFd(int epfd,int fd,bool enableET){
			struct epoll_event event;
			event.events=EPOLLIN;
			if(enableET){
				event.events=event.events|EPOLLET;
				setNonbloking(fd);
			}

			event.data.fd=fd;
			int op=EPOLL_CTL_ADD;
			int ret=epoll_ctl(epfd,op,fd,&event);//目前用来监控可写，但其也可以监控可读
			assert(-1!=ret);
}

void recv_onceforall(int epfd,int sockfd,set<int> &fdset,char *buf){
//buf:”退化”成指向首元素的指针
		while(1){
			memset(buf,0,BUF_SIZE);
//			memset(buf,0,sizeof(buf));
			int ret=recv(sockfd,buf, BUF_SIZE-1,0);//这里少接收一个是为了print buf的时候有字符串结束符
//			ret=recv(sockfd,buf, sizeof(buf)-1,0);
			if(ret<0){
				if(EAGAIN==errno||EWOULDBLOCK==errno){
					printf("---finish recv-ing---\n");
					break;	
				}
				else{//什么情景???
					PERROR(-1,ret,"recv()");
					printf("recv() error\n");
					_exit(-1);//recv出错，服务器挂掉???
				}
			} //退出机制 对端ctrl+c退出，或ctrl+d退出
		   else if(ret==0){//水平触发，触发了表示有数据，ret应该大于0，但ret=0，表示sockfd关闭了
				fdset.erase(sockfd);
				delFd(epfd,sockfd);
				close(sockfd);//关闭后，不解除注册，是否一直使epollwait触发？？
				printf("bye %d\n",sockfd);
		//						continue;
				break;
			}else{
				printf("from client:%s\n",buf);
			}
		}
}
int main(int argc,char**argv){
	int ret;
	if(3!=argc){
		perror("args error");
		_exit(-1);
	}
//1.	 int socket(int domain, int type, int protocol);
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	PERROR(-1,sfd,"socket()");
//int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
	int resue=1;	
	ret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&resue,sizeof(int));
	assert(-1!=ret);

//2.	int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
//	struct sockaddr addr;
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;

	struct in_addr h_addr;	
	h_addr.s_addr=inet_addr(argv[1]);
	addr.sin_addr=h_addr;

	short int h_port=atoi(argv[2]);
	addr.sin_port=htons(h_port);

	ret=bind(sfd,(struct sockaddr*)&addr,sizeof(struct sockaddr));//all is right
//	ret=bind(sfd,(struct sockaddr*)&addr,sizeof(struct sockaddr_in));
	PERROR(-1,ret,"bind()");
	int maxNoListen=10;
//3.	int listen(int sockfd, int backlog);
	ret=listen(sfd,maxNoListen);
	PERROR(-1,ret,"listen()");


	char buf[BUF_SIZE]={0};


	int epfd;
	epfd=epoll_create(1);
	assert(-1!=epfd);

	addFd(epfd,sfd,false);
	addFd(epfd,0,false);//标准输入为LT


	struct epoll_event events[MAX_EVENT_NUMBER];
	int timeOut=5000;//milisecond, -1,永久等待，即epoll_wait阻塞
	set<int> fdset;
	while(1){
//int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
		int retval=epoll_wait(epfd,events,MAX_EVENT_NUMBER,timeOut);//超时，ret=0，for进不去
		assert(-1!=retval);

		for(int i=0;i<retval;++i){
			int sockfd=events[i].data.fd;
			if(sfd==sockfd){
				struct sockaddr_in addr_cli;
				memset(&addr_cli,0,sizeof(struct sockaddr_in));
				socklen_t len;//传入参数？？ yes,但是必须initialize
				len=sizeof(struct sockaddr_in);
			//	len=sizeof(struct sockaddr);//all is right
				int newfd=accept(sockfd,(struct sockaddr*)&addr_cli,&len);
				printf("client ip:%s,port:%d\n",inet_ntoa(addr_cli.sin_addr), ntohs(addr_cli.sin_port));

//int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
				int resue=1;	
				ret=setsockopt(newfd,SOL_SOCKET,SO_REUSEADDR,&resue,sizeof(int));
				assert(-1!=ret);

				fdset.insert(newfd);
				PERROR(-1,newfd,"accept()");
				addFd(epfd,newfd,true);
			}
			else if(0==sockfd){
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				PERROR(-1,ret,"read()");

				//退出机制 本端ctrl+d退出 ; ctrl+c进程退出,本段bye不打印
				if(ret==0){ //目前不适用ctrl+d退出,除非使用goto
					printf("bye\n");
					break;
				}

				for(int e:fdset){
					ret=send(e,buf,ret,0);//读了ret，就send ret个字符
//					ret=send(e,buf, strlen(buf)-1,0);
					PERROR(-1,ret,"send()");
				}

			}
			else if(EPOLLIN&events[i].events){
				recv_onceforall(epfd,sockfd,fdset,buf);
			}
		}//for

		if(0==retval){
			printf("do other job,retval=%d\n",retval);
		}else{
			printf("retval=%d\n",retval);
		}
	}//while
	close(epfd);
	close(sfd);
	for(int e:fdset){
		ret=close(e);
		PERROR(-1,ret,"close()");
	}

	return 0;
}
