 ///
 /// @file    tcpserver.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-02-09 14:17:21
 ///
 
#include "func.hpp"
int main(int argc,char**argv){
	int ret;
	if(3!=argc){
		perror("args error");
		_exit(-1);
	}
//1.	 int socket(int domain, int type, int protocol);
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	PERROR(-1,sfd,"socket()");

//2.	int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
//	struct sockaddr addr;
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;

	struct in_addr h_addr;	//h_addr为网络字节序
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

//4.int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	struct sockaddr_in addr_cli;
   //The  addrlen argument is a value-result argument: the caller must initialize
	//it to contain the size (in bytes) of the structure pointed to  by  addr;  on
    //return it will contain the actual size of the peer address.
	socklen_t len;//传入参数？？ yes,但是必须initialize
	len=sizeof(struct sockaddr_in);
//	len=sizeof(struct sockaddr);//all is right
	int newfd=accept(sfd,(struct sockaddr*)&addr_cli,&len);
	PERROR(-1,newfd,"accept()");
	printf("client ip:%s,port:%d\n",inet_ntoa(addr_cli.sin_addr),\
			ntohs(addr_cli.sin_port));

#if 0
	char buf[1024]={0};
	ret=recv(newfd,buf,sizeof(buf),0);
	PERROR(-1,ret,"recv()");
	puts(buf);
	ret=send(newfd,"hi",5,0);
	PERROR(-1,ret,"send()");
#endif

	char buf[1024]={0};
	int maxfd=max(newfd,newfd)+1;
	fd_set fdSet;//传入传出参数
	struct timeval timeout;
	while(1){//每一个循环都要清理fdset集合并重新加入吗？？？
		FD_ZERO(&fdSet);
		FD_SET(0,&fdSet);
		FD_SET(newfd,&fdSet);
		FD_SET(sfd,&fdSet);
		timeout.tv_sec=6;
//		ret=select(maxfd,&fdSet,NULL,NULL,NULL);//目前用来监控可写，但其也可以监控可读
		ret=select(maxfd,&fdSet,NULL,NULL,&timeout);//目前用来监控可写，但其也可以监控可读
		if(ret>0){
			if(FD_ISSET(sfd,&fdSet)){
				memset(&addr_cli,0,sizeof(struct sockaddr_in));
				socklen_t temp_len=sizeof(struct sockaddr_in);
				int temp_fd=accept(sfd,(struct sockaddr*)&addr_cli,&temp_len);
				PERROR(-1,temp_fd,"accept()");
				FD_SET(temp_fd,&fdSet);
				printf("client ip:%s,port:%d\n",inet_ntoa(addr_cli.sin_addr),\
						ntohs(addr_cli.sin_port));

				//监听temp_fd
			}
			if(FD_ISSET(0,&fdSet)){
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				PERROR(-1,ret,"read()");

				//退出机制 本端ctrl+d退出 ; ctrl+c进程退出,本段bye不打印
				if(ret==0){ 
					printf("bye\n");
					break;
				}

				ret=send(newfd,buf, strlen(buf)-1,0);
				PERROR(-1,ret,"send()");
			}
			if(FD_ISSET(newfd,&fdSet)){
				memset(buf,0,sizeof(buf));
				ret=recv(newfd,buf, sizeof(buf),0);
				PERROR(-1,ret,"recv()");

				//退出机制 对端ctrl+c退出，或ctrl+d退出
				if(ret==0){
					printf("bye\n");
					break;
				}
				printf("from client:%s\n",buf);
			}
		}
		else {
			printf("do other job\n");
		}
	}
	close(newfd);
	close(sfd);

	return 0;
}
