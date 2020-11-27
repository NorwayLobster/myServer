///
/// @file    htons.cc
/// @author  ChengWANG(cheng.wang.801@gmail.com)
/// @date    2020-02-08 23:55:52
///

#include "func.hpp"

//ip地址的 点分十进制 和 网络字节序整数 之间的转化
int main(int argc, char**argv){
	if(2!=argc){
		perror("argc");
		_exit(1);
	}
	int ret;

//1.inet_addr  点分十进制 --> 网络字节序整数ipv4
//	typedef uint32_t in_addr_t;

	long int a=inet_addr(argv[1]);
	printf("a:%lx\n",a);
	//	The inet_addr() function converts the Internet host address cp from IPv4 numbers-and-dots notation into binary data in network byte order.  
	//	If  the input  is  invalid,  INADDR_NONE  (usually  -1)  is returned.  Use of this function is problematic
	//	because -1 is a valid address (255.255.255.255).
	//  Avoid its use in favor of inet_aton(), inet_pton(3), or getaddrinfo(3), which provide a cleaner way to indicate error return.
	
//2.inet_aton() 点分十进制 --> 网络字节序整数ipv4, 与inet_adrr区别, 存储的地方不同
	struct in_addr  n_addr;
//	struct in_addr {
//		in_addr_t s_addr;
//	};
	ret=inet_aton(argv[1],&n_addr);
	if(0==ret){
		perror("inet_aton()");
		_exit(-1);
	}
	printf("n_addr:%x\n",n_addr.s_addr);


//3.inet_ntoa() 网络字节序整数ipv4 --> 点分十进制
	char * buf;	
	buf=inet_ntoa(n_addr);
	//The  inet_ntoa()  function  converts  the  Internet host address in, given in network byte order, to a string in IPv4 dotted-decimal notation.  
	//The string is returned in a statically allocated buffer, which subsequent calls will overwrite.
	printf("h_addr:%s\n",buf);

//4.	inet_pton();
//5.	inet_ntop();
	return 0;
}
