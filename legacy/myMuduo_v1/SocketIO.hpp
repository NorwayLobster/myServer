 ///
 /// @file    SocketIO.hpp
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-08 05:05:06
 ///
#ifndef __Socket_IO_HPP__ 
#define __Socket_IO_HPP__ 
#include <iostream>
#include <unistd.h>
using std::cout;
using std::endl;
class SocketIO{
	public:
		SocketIO(int fd);
		~SocketIO();
		size_t readn(char*,size_t);
		size_t writen(char*,size_t);
	private:
		int _sockfd;
};
#endif
