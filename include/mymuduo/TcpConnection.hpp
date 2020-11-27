 ///
 /// @file    TcpConnection.hpp
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-08 05:27:02
 ///
 
#ifndef __Tcp_Connection_HPP__
#define __Tcp_Connection_HPP__
#include "InetAddress.hpp"
#include "Socket.hpp"
#include "SocketIO.hpp"
#include "EventLoop.hpp"
#include <memory>
#include <climits>
#include <functional>
class TcpConnection:
public std::enable_shared_from_this<TcpConnection>//public inheritance
{
	public:
		typedef std::shared_ptr<TcpConnection> TcpConnectionSharedPtr;
		typedef std::function<void (TcpConnectionSharedPtr)> TcpConnectionCallback;
		TcpConnection(int,EventLoop*);
		~TcpConnection();
		void sendInLoop(char*,int);	
		void send(char*,int);
		string receive();
		void shutDownWrite();

		string info();
		void handleTcpConnection_onMessageEvent(){if(_onMessageEventCb) _onMessageEventCb(shared_from_this());}
		void handleTcpConnection_onCloseEvent(){if(_onCloseEventCb) _onCloseEventCb(shared_from_this());}
		void handleTcpConnection_onConnectEvent(){if(_onConnectEventCb) _onConnectEventCb(shared_from_this());}
		void setTcpConnection_onMessageEventCb(TcpConnectionCallback cb);
		void setTcpConnection_onCloseEventCb(TcpConnectionCallback cb);
		void setTcpConnection_onConnectEventCb(TcpConnectionCallback cb);
	private:
		TcpConnectionCallback _onMessageEventCb;
		TcpConnectionCallback _onCloseEventCb;
		TcpConnectionCallback _onConnectEventCb;
		const InetAddress _localInetAddr;
		const InetAddress _peerInetAddr;
		Socket _sock;
		SocketIO _sockIO;
		bool _isShutDownWrite;
		EventLoop * _eventLoop;
};
#endif
