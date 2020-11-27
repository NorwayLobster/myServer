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
#include "EventLoop.hpp"
#include <iostream>
#include <functional>

using namespace std;

typedef std::shared_ptr<TcpConnection> TcpConnectionSharedPtr;
typedef std::function<void(TcpConnectionSharedPtr)> epollCallback;

void onConnect(TcpConnectionSharedPtr conn){
	cout<<"connect is coming"<<endl;
}
int main(){
	InetAddress localAddress(9090);
	cout<<"ip:"<<localAddress.ip()<<endl;
	cout<<"port:"<<localAddress.h_port()<<endl;
	Socket sock;

	cout<<"fd:"<<sock.fd()<<endl;
	Acceptor acce(localAddress,sock);
	acce.ready();
//	int sockfd=acce.accept();
//	cout<<"sockfd:"<<sockfd<<endl;
//	TcpConnection tcpConn(sockfd);
//	cout<<"tcpConn info::"<<tcpConn.info()<<endl;
	EventLoop eventLoop(acce);
	eventLoop.setEpoll_onConnectEventCb(onConnect);
	eventLoop.loop();
	return 0;
}
