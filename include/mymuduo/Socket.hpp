 ///
 /// @file    Socket.hpp
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-08 04:00:17
 ///
#ifndef __Socket_HPP__ 
#define __Socket_HPP__ 
#include  "InetAddress.hpp"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <cassert>
class Socket{
	public:
		Socket();
		Socket(int);
		~Socket();
		int fd();
		void setNonblock();
		void shutDownWrite();
		static InetAddress getPeerAddrBySockFd(int);
		static InetAddress getLocalAddrBySockFd(int);
	private:
		int _sockfd;
};
#endif
