 ///
 /// @file    Threadpool.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-03-19 11:29:25
 ///
 
#ifndef __WD_THREADPOOL_H__
#define __WD_THREADPOOL_H__

#include <TaskQueue.h>

#include <memory>
#include <vector>
#include <functional>

using std::vector;
using std::unique_ptr;
 
namespace wd
{

class Thread;//类的前向声明， 并不需要知道Thread的实现

class Threadpool
{
	using Task = std::function<void()>;
public:
	Threadpool(size_t threadNum, size_t queSize);
	~Threadpool();

	void start();
	void stop();

	void addTask(Task );
private:
	
	Task getTask();

	void threadFunc(void);//这是每一个子线程要完成的任务

private:
	size_t _threadNum;
	size_t _queSize;
	vector<unique_ptr<Thread>> _threads;
	TaskQueue _taskque;
	bool _isExit;
};


}//end of namespace wd


#endif
