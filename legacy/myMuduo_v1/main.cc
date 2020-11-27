 ///
 /// @file    main.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-10 22:30:46
 ///
 
#include "Socket.hpp"
#include "InetAddress.hpp"
#include "SocketUtilities.hpp"
#include "TcpConnection.hpp"
#include "SocketIO.hpp"
#include "Acceptor.hpp"
#include <iostream>

using namespace std;

int main(){
	InetAddress localAddress(9090);
	cout<<"ip:"<<localAddress.ip()<<endl;
	cout<<"port:"<<localAddress.h_port()<<endl;
	Socket sock;

	cout<<"fd:"<<sock.fd()<<endl;
	Acceptor acce(localAddress,sock);
	acce.ready();
	int sockfd=acce.accept();
	cout<<"sockfd:"<<sockfd<<endl;
	TcpConnection tcpConn(sockfd);
	cout<<Socket::getPeerAddrBySockFd(sockfd).ip()<<endl;
	cout<<Socket::getPeerAddrBySockFd(sockfd).h_port()<<endl;
	cout<<Socket::getLocalAddrBySockFd(sockfd).ip()<<endl;
	cout<<Socket::getLocalAddrBySockFd(sockfd).h_port()<<endl;
	
	cout<<"tcpConn info::"<<tcpConn.info()<<endl;
	return 0;
}
