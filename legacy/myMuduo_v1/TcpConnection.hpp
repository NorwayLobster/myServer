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
#include <memory>
#include <climits>
class TcpConnection{
	public:
		typedef std::shared_ptr<TcpConnection> TcpConnectionSharedPtr;
		typedef std::function<void (TcpConnectionSharedPtr&)> TcpConnectionCallback;
		TcpConnection(int);
		~TcpConnection();
		void sendInLoop();	
		void send(char*,int);
		string receive();
		void shutDownWrite();

		string info();
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
};
#endif
