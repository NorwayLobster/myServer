 ///
 /// @file    SocketUtilities.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-08 04:22:20
 ///
#include "SocketUtilities.hpp" 

int createSocketFd(){
	int fd=socket(AF_INET,SOCK_STREAM,0);
	assert(fd!=-1);
	return fd;
}

void setNonblocking(int _fd){
//int fcntl(int fd, int cmd, ... /* arg */ );
//先get 后set
		int old_option=fcntl(_fd,F_GETFL);
		assert(-1!=old_option);
		int new_option=old_option|O_NONBLOCK;

		int ret=fcntl(_fd,F_SETFL,new_option);
		assert(-1!=ret);
}

