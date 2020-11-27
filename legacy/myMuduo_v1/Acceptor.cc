 ///
 /// @file    Acceptor.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-08 10:07:29
///
 
#include "Acceptor.hpp"
Acceptor::Acceptor(const InetAddress&inetAddr,const Socket&sock)
:_listenSock(sock)
,_inetAddr(inetAddr)
{
	cout<<"Acceptor(const InetAddress&inetAddr,const Socket&sock)"<<endl;
}
Acceptor::~Acceptor(){
	cout<<"~Acceptor()"<<endl;
}
int Acceptor::accept(){
//	int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
//	struct sockaddr n_addr;
	int ret=::accept(_listenSock.fd(),NULL,NULL);
//	int ret=accept(_listenSock,&n_addr,sizeof(struct sockaddr));
	if(-1==ret){
		perror("accept()");
		exit(EXIT_FAILURE);
	}
	return ret;
}
void Acceptor::ready(){
	setReuseAddr(1);
	setReusePort(1);
	bind();
	listen();
}


void Acceptor::bind(){
// int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen); 
	int ret=::bind(_listenSock.fd(),(struct sockaddr*)_inetAddr.getSockAddrPtr(),sizeof(struct sockaddr));
	if(-1==ret){
		perror("bind()");
		exit(EXIT_FAILURE);
	}
}
void Acceptor::listen(){
//	int listen(int sockfd, int backlog);
	int backlog=10;
	int ret=::listen(_listenSock.fd(),backlog);
	if(-1==ret){
		perror("listen()");
		exit(EXIT_FAILURE);
	}
}
void Acceptor::setReuseAddr(int on){
//	  int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
//	  int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
	if(-1==setsockopt(_listenSock.fd(),SOL_SOCKET,SO_REUSEADDR,&on,static_cast<socklen_t>(sizeof(on)))){
		perror("setsockopt ip addr error");
		exit(EXIT_FAILURE);
	}
}
void Acceptor::setReusePort(int on){
	if(-1==setsockopt(_listenSock.fd(),SOL_SOCKET,SO_REUSEPORT,&on,static_cast<socklen_t>(sizeof(on)))){
		perror("setsockopt port error");
		exit(EXIT_FAILURE);
	}
}
