 ///
 /// @file    open.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-02-12 00:10:25
 ///
 
#include  "func.hpp"

int main(){
	int ret;
	int fd=open("file",O_WRONLY|O_CREAT);
	assert(-1!=fd);
	ret=write(fd,"hell",4);
	assert(-1!=ret);
	return 0;
}
