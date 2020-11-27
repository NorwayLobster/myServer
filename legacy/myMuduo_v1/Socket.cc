 ///
 /// @file    Socket.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-08 04:02:46
 ///
 
#include <iostream>
#include "Socket.hpp"
#include "SocketUtilities.hpp"
using std::cout;
using std::endl;
Socket::Socket()
	:_sockfd(createSocketFd())
{
	cout<<"Socket()"<<endl;
}

Socket::~Socket(){
	cout<<"~Socket()"<<endl;
}
Socket::Socket(int fd)
	:_sockfd(fd)
{
	cout<<"Socket(int fd)"<<endl;
}

int Socket::fd(){
	return _sockfd;
}
void Socket::shutDownWrite(){
	shutdown(_sockfd,SHUT_RD);
}
void Socket::setNonblock(){
//int fcntl(int fd, int cmd, ... /* arg */ );
//先get 后set
	setNonblocking(_sockfd);
}

InetAddress Socket::getPeerAddrBySockFd(int fd){
	struct sockaddr_in n_addr;
//note: struct sockaddr v.s. struct sockaddr_in
	socklen_t addrlen=sizeof(n_addr);
//	size_t addrlen=sizeof(n_addr);
//	 int getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	int ret=getpeername(fd,(struct sockaddr*)(&n_addr),&addrlen);
	assert(-1!=ret);
	return InetAddress(n_addr);
}
InetAddress Socket::getLocalAddrBySockFd(int fd){
	struct sockaddr_in n_addr;
	socklen_t addrlen=sizeof(n_addr);
//	socklen_t addrlen=sizeof(struct sockaddr_in);
//	 int getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	int ret=getsockname(fd,(struct sockaddr*)(&n_addr),&addrlen);
	assert(-1!=ret);
	return InetAddress(n_addr);
//	return InetAddress(n_addr);
}
