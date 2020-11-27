 ///
 /// @file    TaskQueue.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-03-17 11:51:29
 ///
 
#ifndef __WD_TASKQUEUE_H__
#define __WD_TASKQUEUE_H__

#include <MutexLock.h>
#include <Condition.h>

#include <queue>
#include <functional>
namespace wd
{

class  TaskQueue
{
	using Product = std::function<void()>; 
public:
	TaskQueue(int queSize);

	void push(Product );
	Product pop();

	bool full() const;
	bool empty() const;

	void wakeup();

private:
	wd::MutexLock _mutex;
	Condition _notFull;
	Condition _notEmpty;
	size_t _queSize;
	std::queue<Product> _que;
	bool _flag;
};

}//end of namespace wd

#endif
