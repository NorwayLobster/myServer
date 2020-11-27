 ///
 /// @file    tcpserver.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-02-09 14:17:21
 ///
 
#include "func.hpp"
#define MAX_EVENT_NUMBER 1024
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


	char buf[1024]={0};

	struct timeval timeout;
	timeout.tv_sec=6;

	int epfd;
	epfd=epoll_create(1);
	assert(-1!=epfd);
//int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

	struct epoll_event event;
	event.events=EPOLLIN;

	event.data.fd=sfd;
	int op=EPOLL_CTL_ADD;
	ret=epoll_ctl(epfd,op,sfd,&event);//目前用来监控可写，但其也可以监控可读
	assert(-1!=ret);

	event.data.fd=0;
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,0,&event);//目前用来监控可写，但其也可以监控可读
	assert(-1!=ret);

	struct epoll_event events[MAX_EVENT_NUMBER];
	int timeOut=5;
	set<int> fdset;
	while(1){//每一个循环都要清理fdset集合并重新加入吗？？？
//int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
		int retval=epoll_wait(epfd,events,MAX_EVENT_NUMBER,timeOut);
		assert(-1!=retval);
		for(int i=0;i<retval;++i){
			int sockfd=events[i].data.fd;
			if(sfd==sockfd){
			//4.int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
				struct sockaddr_in addr_cli;
				memset(&addr_cli,0,sizeof(struct sockaddr_in));
			   //The  addrlen argument is a value-result argument: the caller must initialize
				//it to contain the size (in bytes) of the structure pointed to  by  addr;  on
				//return it will contain the actual size of the peer address.
				socklen_t len;//传入参数？？ yes,但是必须initialize
				len=sizeof(struct sockaddr_in);
			//	len=sizeof(struct sockaddr);//all is right
			//
				int newfd=accept(sockfd,(struct sockaddr*)&addr_cli,&len);
//int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
				int resue=1;	
				ret=setsockopt(newfd,SOL_SOCKET,SO_REUSEADDR,&resue,sizeof(int));
				assert(-1!=ret);

				fdset.insert(newfd);
				PERROR(-1,newfd,"accept()");
				printf("client ip:%s,port:%d\n",inet_ntoa(addr_cli.sin_addr), ntohs(addr_cli.sin_port));

				memset(&event,0,sizeof(struct epoll_event));
				event.events=EPOLLIN;
				event.data.fd=newfd;
				int op=EPOLL_CTL_ADD;
				ret=epoll_ctl(epfd,op,newfd,&event);//目前用来监控可写，但其也可以监控可读
				assert(-1!=ret);
			}
			else if(0==sockfd){
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				PERROR(-1,ret,"read()");

				//退出机制 本端ctrl+d退出 ; ctrl+c进程退出,本段bye不打印
				if(ret==0){ 
					printf("bye\n");
					break;
				}

				for(int e:fdset){
					ret=send(e,buf, strlen(buf)-1,0);
					PERROR(-1,ret,"send()");
				}

			}
			else if(EPOLLIN&events[i].events){
				memset(buf,0,sizeof(buf));
				ret=recv(sockfd,buf, sizeof(buf),0);
				PERROR(-1,ret,"recv()");

				//退出机制 对端ctrl+c退出，或ctrl+d退出
				if(ret==0){//水平触发，触发了表示有数据，ret应该大于0，但ret=0，表示sockfd关闭了
					fdset.erase(sockfd);

					memset(&event,0,sizeof(struct epoll_event));
					event.events=EPOLLIN;
					event.data.fd=sockfd;
					int op=EPOLL_CTL_DEL;
					ret=epoll_ctl(epfd,op,sockfd,&event);//目前用来监控可写，但其也可以监控可读
					assert(-1!=ret);

					close(sockfd);//关闭后，不解除注册，是否一直使epollwait触发？？
					printf("bye %d\n",sockfd);
					continue;
				}
				printf("from client:%s\n",buf);
			}
			else {
				printf("do other job\n");
			}
		}//for
	}//while
	close(epfd);
	close(sfd);
	for(int e:fdset){
		ret=close(e);
		PERROR(-1,ret,"close()");
	}


	return 0;
}
