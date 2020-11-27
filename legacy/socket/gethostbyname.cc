///
/// @file    htons.cc
/// @author  ChengWANG(cheng.wang.801@gmail.com)
/// @date    2020-02-08 23:55:52
///

#include "func.hpp"

int main(int argc, char**argv){
	if(2!=argc){
		perror("argc");
		_exit(1);
	}
	int ret;

//1.gethostbyname()
//2.gethostbyaddr()
//3.getservbyname()
//4.getservbyport()
//
//5.getaddrinfo(): gethostbyname()和getservbyname()  主机名/服务名----> ip/port号
//6.getnameinfo(): gethostbyaddr()和getservbyport()  ip/port号----> 主机名/服务名

	return 0;
}
