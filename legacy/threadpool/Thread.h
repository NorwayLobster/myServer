 ///
 /// @file    Thread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-03-17 09:51:49
 ///
 
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__

#include <Noncopyable.h>
#include <pthread.h>
#include <functional>

namespace wd
{

class Thread
: Noncopyable
{
	//typedef std::function<void()> ThreadCallback;
	using ThreadCallback = std::function<void()>;
public:
	Thread(ThreadCallback);
	~Thread();

	void start();
	void join();

private:
	static void * threadFunc(void * arg);
private:
	pthread_t _pthId;
	bool _isRunning;
	ThreadCallback _cb;//回调函数
};

}//end of namespace wd

#endif
