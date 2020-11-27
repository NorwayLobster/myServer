 ///
 /// @file    Acceptor.hpp
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-08 05:14:07
 ///
 
#ifndef __Acceptor__HPP__
#define __Acceptor__HPP__
#include "mymuduo/Socket.hpp"
#include "mymuduo/SocketIO.hpp"
#include "mymuduo/InetAddress.hpp"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

class Acceptor{
	public:
		Acceptor(const InetAddress&,const Socket&);
		~Acceptor();
		void ready();//bind listen
//		bool ready();//bind listen
		int accept();	
		void setReuseAddr(int on);
		void setReusePort(int on);
		int fd(){return _listenSock.fd();}
	private:
		void listen();
		void bind();
	private:
		Socket _listenSock;
		InetAddress _inetAddr;
};
#endif

