 ///
 /// @file    htons.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-02-08 23:55:52
 ///
 
#include "func.hpp"
//字节序转化: 大段字节序和小端字节序转化
int main(){
	short int a=4660;
	printf("a:%x\n",a);
//htons: 转port, 16bit
	short int n_port=htons(a);
	PERROR(-1,n_port,"htons");
	printf("n_port:%x\n",n_port);

//ntohs
	short int h_port=ntohs(n_port);
	PERROR(-1,h_port,"ntohs");
	printf("h_port:%x\n",h_port);


	long int ip=192168196204;
//htonl: 转ip, 32bit
	long int n_ip=htonl(ip);
	PERROR(-1,n_ip,"htonl");
	printf("n_ip:%lx\n",n_ip);

//ntohl
	long int h_ip=ntohl(n_ip);
	PERROR(-1,h_ip,"ntohl");
	printf("h_ip:%lx\n",h_ip);



	return 0;
}
