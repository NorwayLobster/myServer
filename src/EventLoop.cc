 ///
 /// @file    EventLoop.cc
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-08 13:43:01
 ///
 
#include "EventLoop.hpp"

EventLoop::EventLoop(Acceptor &acceptor)
:_epollFd(createEpollFd())
,_acceptor(acceptor)
,_listenFd(acceptor.fd())
,_eventfd(createEventfd())
,_isLooping(false)
,_eventsList(1024)
,_mutex()
{
	addFdRead(_epollFd,_listenFd,false);
	addFdRead(_epollFd,_eventfd,false);
	cout<<"EventLoop()"<<endl;
}
EventLoop::~EventLoop(){
	cout<<"~EventLoop()"<<endl;
}
void EventLoop::loop(){

	_isLooping=true;
	printf("loop starting\n");
	waitEpollFd();
}
void EventLoop::unloop(){
	if(_isLooping)
		_isLooping=false;
}
void EventLoop::waitEpollFd(){
 //int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
// int retval=epoll_wait(_epollFd,epollEvents,maxEvents,0);

	while(_isLooping){
		int timeOut=4000;	
		int retval;
		do{
			retval=epoll_wait(_epollFd,&(*_eventsList.begin()),_eventsList.size(),timeOut);//超时，ret=0，for进不去
		}while(-1!=retval&&errno==EINTR);
		printf("retval=%d\n",retval);
		if((int)_eventsList.size()==retval){
			_eventsList.resize(_eventsList.size()*2);
		}
		if(0==retval){
			printf("timeout, retval=%d\n",retval);
		}else if(-1==retval){
			perror("epoll_wait()");
			exit(EXIT_FAILURE);
		}

		for(int i=0;i<retval;++i){
			int sockfd=_eventsList[i].data.fd;
			if(_listenFd==sockfd){
				handleEpoll_onConnectEvent();
			}else if(_eventfd==sockfd){
				handleEpoll_onWakeUpEvent();
			}else if(EPOLLIN&_eventsList[i].events){
				handleEpoll_onMessageEvent(sockfd);
			}
		}//for
	}//while

}
void runInLoop(Functor cb){
	{
		MutexLockGuard mlg(_mutex);
		_pendingFunctors.push_back(cb);
	}
	wakeup();
}
void EventLoop::wakeup(){
	int one=1;
	int ret=write(_eventfd,one,sizeof(int));
	assert(-1!=ret);
}
void doPendingFunctors(){
	std::vector<Functor> tmp;
	
	{
		MutexLockGuard mlg(_mutex);
		tmp.swap(_pendingFunctors);
	}
	for(auto f:tmp)
		f();
}
void EventLoop::handleEpoll_onMessageEvent(int fd){
	auto ite=_connMap.find(fd);	
	if(_connMap.end()!=ite)
		ite->second->handleTcpConnection_onMessageEvent();
//	connMap[fd]->handleTcpConnection_onMessageEvent();
}
void EventLoop::handleEpoll_onWakeUpEvent(){
	int one;
	int ret=read(_eventfd,&one,sizeof(int));
	assert(-1!=ret);
	doPendingFunctors();
}
void EventLoop::handleEpoll_onCloseEvent(int fd){
	auto ite=_connMap.find(fd);	
	if(_connMap.end()!=ite)
		ite->second->handleTcpConnection_onCloseEvent();
}
			
#if 0
			}else if(0==sockfd){
				
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				PERROR(-1,ret,"read()");

				//退出机制 本端ctrl+d退出 ; ctrl+c进程退出,本段bye不打印
				if(ret==0){ //目前不适用ctrl+d退出,除非使用goto
					printf("bye\n");
					break;
				}

				for(int e:fdset){
					ret=send(e,buf,ret,0);//读了ret，就send ret个字符
//					ret=send(e,buf, strlen(buf)-1,0);
					PERROR(-1,ret,"send()");
				}

			}

}
#endif

void EventLoop::handleEpoll_onConnectEvent(){
				int newfd=_acceptor.accept();
				assert(-1!=newfd);
				addFdRead(_epollFd,newfd,true);

				TcpConnectionSharedPtr conn(new TcpConnection(newfd,this));

				conn->setTcpConnection_onConnectEventCb(_onConnectEventCb);
				conn->setTcpConnection_onMessageEventCb(_onMessageEventCb);
				conn->setTcpConnection_onCloseEventCb(_onCloseEventCb);
				printf("client ip:%s,port:%d\n",Socket::getPeerAddrBySockFd(newfd).ip().c_str(),Socket::getPeerAddrBySockFd(newfd).h_port());

				std::pair<std::unordered_map<int,TcpConnectionSharedPtr>::iterator,bool> ret;
				ret=connMap.insert(std::make_pair(newfd,conn));
				assert(true==ret.second);
				//connMap[newfd]=conn;

				conn->handleTcpConnection_onConnectEvent();
}
