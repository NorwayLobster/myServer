 ///
 /// @file    SocketIO.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-08 05:09:09
 ///
 
#include "SocketIO.hpp"
SocketIO::SocketIO(int fd)
	:_sockfd(fd)
{
	cout<<"SocketIO(int fd)"<<endl;
}
SocketIO::~SocketIO(){
	cout<<"~SocketIO()"<<endl;
}
size_t SocketIO::writen(char * buf,size_t num){
	int nLeftToWrite=num;
	int sum=0;
	while(nLeftToWrite>0){
		int ret=write(_sockfd,buf+sum,nLeftToWrite);
		if(-1==ret&&errno==EAGAIN){
			continue;
		}else if(-1==ret){
			perror("write() error");
//		}else if(0==ret){ 
		}
		sum+=ret;
		nLeftToWrite-=ret;
	}
	return sum;
}
size_t SocketIO::readn(char * buf,size_t num){
	int nLeftToRead=num;
	int sum=0;
	while(nLeftToRead>0){
		int ret=read(_sockfd,buf+sum,nLeftToRead);
		if(-1==ret&&errno==EAGAIN){
			continue;
		}else if(-1==ret){
			perror("read() error\n");
//		}else{
		}

		sum+=ret;
		nLeftToRead-=ret;
	}
}

