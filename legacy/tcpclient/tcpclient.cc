 ///
 /// @file    tcpserver.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-02-09 14:17:21
 ///
 
#include "func.hpp"

typedef struct train_tag{
	int len;
	char buf[4096];
}Train,*pTrain;

int recvn(int fd,char *buf,int len){
	int ret=0;
	int sum=0;
	while(sum<len){
		ret=recv(fd,buf+sum,len-sum,0);
		sum+=ret;
	}
	return len;
}

int recv_file(int newfd){
//int recv_file(int newfd,char *filename,int len){
	int ret;
	Train t;
	char filename[1024]={0};
	bzero(&t,sizeof(Train));

	recvn(newfd,(char*)&t,4);
	recvn(newfd,t.buf,t.len);
	memcpy(filename,t.buf,t.len);
	puts(filename);
//	printf("t.len:%d\n",t.len);
//	printf("filename:%s\n",filename);
	int fd=open(filename,O_WRONLY|O_CREAT);
	assert(-1!=fd);
	while(1){
		recvn(newfd,(char*)&t,4);
//		ret=recvn(newfd,(char*)&t,4+sizeof(t.buf));
//		printf("t.len:%d\n",t.len);
		if(0==t.len)
			break;
		recvn(newfd,t.buf,t.len);
		ret=write(fd,t.buf,t.len);
		assert(-1!=ret);
	}
	return 0;
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

	struct sockaddr_in addr;
	addr.sin_family=AF_INET;

	struct in_addr h_addr;	
	h_addr.s_addr=inet_addr(argv[1]);//想要连接的server的地址
	addr.sin_addr=h_addr;

	short int h_port=atoi(argv[2]);
	addr.sin_port=htons(h_port);

	socklen_t len;//传入参数？？ NO
	len=sizeof(struct sockaddr_in);
	len=sizeof(struct sockaddr);//??
//2.int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	ret=connect(sfd,(struct sockaddr*)&addr,len);
	PERROR(-1,ret,"connect()");
#if 0 
	ret=send(sfd,"hello",5,0);
	PERROR(-1,ret,"send()");
	char buf[1024]={0};

	ret=recv(sfd,buf,sizeof(buf),0);
	PERROR(-1,ret,"recv()");
	puts(buf);

	//select 内部实现机制
	int select(int maxfd,fd_set* p,,,,)
	{
		fd_set tmpset;

		memcpy(&tmpset,p,sizeof(fd_set));
		FD_ZERO(p);
		FD_SET(0,p);//若0可读
		FD_SET(fdr,p);//若fdr可读
	}
#endif 
	char buf[1024]={0};
	int maxfd=sfd+1;
//	int maxfd=max(sfd,sfd)+1;
	fd_set fdSet;//传入传出参数
	struct timeval timeout;
	while(1){
		FD_ZERO(&fdSet);
		FD_SET(0,&fdSet);
		FD_SET(sfd,&fdSet);
		timeout.tv_sec=6;
//		ret=select(maxfd,&fdSet,NULL,NULL,NULL);//目前用来监控可写，但其也可以监控可读
		ret=select(maxfd,&fdSet,NULL,NULL,&timeout);//目前用来监控可写，但其也可以监控可读
		if(ret>0){
			if(FD_ISSET(0,&fdSet)){
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				PERROR(-1,ret,"read()");

				//退出机制 本端ctrl+d退出 ; ctrl+c进程退出,本段bye不打印
				if(ret==0){ 
					printf("bye\n");
					break;
				}

				ret=send(sfd,buf, strlen(buf)-1,0);
				PERROR(-1,ret,"send()");
			}
			if(FD_ISSET(sfd,&fdSet)){
				memset(buf,0,sizeof(buf));
				ret=recv_file(sfd);
//				ret=recv(sfd,buf, sizeof(buf),0);
				PERROR(-1,ret,"recv()");

				//退出机制 对端ctrl+c退出，或ctrl+d退出
				if(ret==0){
					printf("bye\n");
					break;
				}
				printf("from server:%s\n",buf);
			}
		}
		else {
			printf("do other job\n");
		}
	}
	close(sfd);

	return 0;
}
