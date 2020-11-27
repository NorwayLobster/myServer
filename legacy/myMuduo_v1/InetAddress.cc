 ///
 /// @file    InetAddress.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-08 02:36:49
 ///
 
#include <iostream>
#include "InetAddress.hpp"
using std::cout;
using std::endl;

InetAddress::InetAddress(const struct sockaddr_in& addr)
	:_addr(addr)
{
	cout<<"InetAddress(const struct sockaddr_in& addr) ctor"<<endl;
}
InetAddress::InetAddress(unsigned int n_port){
	cout<<"InetAddress(unsigned int n_port) ctor"<<endl;
	::memset(&_addr,0,sizeof(_addr));
	_addr.sin_family=AF_INET;
//	struct in_addr h_addr;
//	h_addr.s_addr=inet_addr("127.0.0.1");
//	_addr.sin_addr=h_addr;
	_addr.sin_addr.s_addr=INADDR_ANY;
	_addr.sin_port=htons(n_port);
}

InetAddress::InetAddress(const string &n_ip,unsigned int n_port){
	cout<<"InetAddress(const string &n_ip,unsigned int n_port) ctor"<<endl;
	::memset(&_addr,0,sizeof(_addr));
	_addr.sin_family=AF_INET;
//	struct in_addr n_addr;
//	n_addr.s_addr=inet_addr(n_ip.c_str());
//	_addr.sin_addr=n_addr;
	_addr.sin_addr.s_addr=inet_addr(n_ip.c_str());
	_addr.sin_port=htons(n_port);
}
#if 0
InetAddress::InetAddress(const InetAddress&inetAddress){
	cout<<"InetAddress(const InetAddress&inetAddress)"<<endl;
	_addr=inetAddress;
}
#endif
struct sockaddr_in * InetAddress::getSockAddrPtr(){
	return &_addr;
}
InetAddress::~InetAddress(){
	cout<<"~InetAddress()"<<endl;
}
string InetAddress::ip()const{
	return string(inet_ntoa(_addr.sin_addr));
}
unsigned int InetAddress::h_port()const{
	return ntohs(_addr.sin_port);
}
