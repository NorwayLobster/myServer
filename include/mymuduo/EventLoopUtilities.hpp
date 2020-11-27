 ///
 /// @file    EventLoopUtilities.hpp
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-08 13:52:56
 ///
 
#include <iostream>
#include <cassert>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include "SocketUtilities.hpp" 
using std::cout;
using std::endl;
int createEpollFd();
int createEventfd();
void addFdRead(int epfd,int fd,bool enableET);
void addFdWrite(int epfd,int fd,bool enableET);
void addFd(int epfd, int fd);
void delFd();
