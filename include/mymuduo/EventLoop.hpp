 ///
 /// @file    EventLoop.hpp
 /// @author  ChengWANG(cheng.wang.801@gmail.com)
 /// @date    2020-04-08 05:47:48
 ///
 
#ifndef __Event_Loop_HPP__
#define __Event_Loop_HPP__
#include <vector>
#include <unistd.h>
#include <sys/epoll.h>
#include <string>
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>
#include "TcpConnection.hpp"
#include "EventLoopUtilities.hpp"
#include "Acceptor.hpp"
#include "MutexLock.h"
using std::string;
using std::cout;
using std::vector;
using std::function;
using std::shared_ptr;
class TcpConnection;//vital
class EventLoop{
	public:
		typedef std::function<void()> Functor;
		typedef std::vector<struct epoll_event> EventList;
		typedef std::shared_ptr<TcpConnection> TcpConnectionSharedPtr;
		typedef std::function<void(TcpConnectionSharedPtr)> epollCallback;
//	typedef TcpConnection::TcpConnectionCallback epollCallback;
		EventLoop(Acceptor&);
		~EventLoop();
		void loop();
		void unloop();
		void setEpoll_onMessageEventCb(epollCallback cb){_onMessageEventCb=cb;}
		void setEpoll_onCloseEventCb(epollCallback cb){_onCloseEventCb=cb;}
		void setEpoll_onConnectEventCb(epollCallback cb){_onConnectEventCb=cb;}

		void handleEpoll_onMessageEvent(int);
		void handleEpoll_onCloseEvent(int);
		void handleEpoll_onConnectEvent();
		void handleEpoll_onWakeUpEvent();
		void runInLoop(Functor);
		void doPendingFunctors();
		void wakeup();
	private:
		epollCallback _onMessageEventCb;
		epollCallback _onCloseEventCb;
		epollCallback _onConnectEventCb;

	private:
		void waitEpollFd();
	private:
		int _epollFd;
		Acceptor & _acceptor;
		int _listenFd;
		int _eventfd;
		bool _isLooping;
		std::vector<struct epoll_event> _eventsList;
		std::unordered_map<int,TcpConnectionSharedPtr> _connMap;
		std::vector<epollCallback> _pendingFunctors;		
		wd::MutexLock _mutex;//vital namespace 
};
#endif
