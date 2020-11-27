 ///
 /// @file    testInetAddress.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-08 02:55:34
 ///
 
#include "InetAddress.hpp"
#include <iostream>
using std::cout;
using std::endl;
int main(){
	InetAddress inetAddress(9090);
//	InetAddress inetAddress("192.168.54.218",9090);
	cout<<"port:"<<inetAddress.h_port()<<endl;
	cout<<"ip:"<<inetAddress.ip()<<endl;
	return 0;
}
