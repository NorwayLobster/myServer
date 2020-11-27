 ///
 /// @file    InetAddress.hpp
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-08 02:24:27
 ///
#ifndef __Inet__Address_HPP__ 
#define __Inet__Address_HPP__ 
#include <string>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using std::cout;
using std::endl;
using std::string;
class InetAddress{
	public:
	InetAddress(unsigned int port);	
	InetAddress(const string&ip,unsigned int port);	
//	InetAddress(const InetAddress& inetAddress);
	InetAddress(const struct sockaddr_in& addr);
	~InetAddress();	
	string ip() const;	
	unsigned int h_port() const;	
	struct sockaddr_in * getSockAddrPtr();
	private:
		struct sockaddr_in _addr;
};
#endif
