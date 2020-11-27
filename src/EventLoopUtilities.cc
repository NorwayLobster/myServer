 ///
 /// @file    EventLoopUtilities.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-08 13:50:10
 ///
#include "EventLoopUtilities.hpp" 
int createEventfd(){
		int fd=eventfd(0,EFD_NONBLOCK|EFD_CLOEXEC);
		assert(fd!=-1);
		return fd;
}
int createEpollFd(){
	size_t sz=100;
	int epfd=epoll_create(sz);
	assert(-1!=epfd);
	return epfd;
}

void addFdRead(int epfd, int fd, bool enableET){
	struct epoll_event event;
	event.events=EPOLLIN;
	if(enableET){
		setNonblocking(fd);
		event.events|=EPOLLET;
	}
	event.data.fd=fd;
	int ret=epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event);
	assert(-1!=ret);
}
void addFdWrite(int epfd, int fd, bool enableET){
	struct epoll_event event;
	event.events=EPOLLOUT;
	if(enableET){
		setNonblocking(fd);
		event.events|=EPOLLET;
	}
	event.data.fd=fd;
	int ret=epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event);
	assert(-1!=ret);
}
void delFd(int epfd, int fd){
	struct epoll_event event;
	event.events=EPOLLOUT;
	event.data.fd=fd;
	int ret=epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);//kernel 2.6.9 and latter
//	int ret=epoll_ctl(epfd,EPOLL_CTL_DEL,fd,&event);
	assert(-1!=ret);
}
