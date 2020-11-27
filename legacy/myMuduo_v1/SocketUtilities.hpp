 ///
 /// @file    SocketUtilities.hpp
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-08 04:30:02
 ///
 
#ifndef __Socket_Utilities__HPP__
#define __Socket_Utilities__HPP__

#include <iostream>
#include <cassert>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
void setNonblocking(int _fd);
int createSocketFd();
#endif
