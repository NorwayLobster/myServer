/*
 * @Author: your name
 * @Date: 2020-04-16 03:52:08
 * @LastEditTime: 2020-11-27 10:47:12
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /mymuduo/example/main.cc
 */
 ///
 /// @file    main.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-10 22:30:46
 ///
 
#include "mymuduo/Socket.hpp"
#include "mymuduo/InetAddress.hpp"
#include "mymuduo/SocketUtilities.hpp"
#include "mymuduo/TcpConnection.hpp"
#include "mymuduo/SocketIO.hpp"
#include "mymuduo/Acceptor.hpp"
#include "mymuduo/EventLoop.hpp"
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
