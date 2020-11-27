 ///
 /// @file    Threadpool.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-03-19 11:37:05
 ///
 
#include <Threadpool.h>
#include <Thread.h>
#include <unistd.h>


namespace wd
{

Threadpool::Threadpool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _taskque(_queSize)
, _isExit(false)
{
	_threads.reserve(_threadNum);
}

Threadpool::~Threadpool()
{
	if(!_isExit)
		stop();
}

void Threadpool::start()
{
	for(size_t idx = 0; idx != _threadNum; ++idx)
	{
		unique_ptr<Thread> up(new Thread(std::bind(&Threadpool::threadFunc, this)));
		_threads.push_back(std::move(up));
	}

	for(auto & subThread : _threads)
	{
		subThread->start();
	}
}

void Threadpool::stop()
{
	if(!_isExit)
	{
		// 要确认所有的任务全部执行完毕
		while(!_taskque.empty())
		{
			::sleep(2);
		}
		_isExit = true;
		// 唤醒所有子线程
		_taskque.wakeup();

		for(auto & subThread : _threads)
		{
			subThread->join();
		}
	}
}
//note: 此Task非彼class Task
//	using Task = std::function<void()>;
void Threadpool::addTask(Task task)
{
	_taskque.push(task);
}

Threadpool::Task Threadpool::getTask()
{
	return _taskque.pop();
}


//每一个子线程要做的事儿
void Threadpool::threadFunc()
{
	while(!_isExit)
	{
		Task task = getTask();
		if(task)
			task();
	}
}



}//end of namespace wd
