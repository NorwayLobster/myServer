 ///
 /// @file    MutexLock.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-02-27 15:26:01
 ///
 
#include <MutexLock.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

MutexLock::MutexLock()
: _isLocking(false)
{
	pthread_mutex_init(&_mutex, NULL);
}

MutexLock::~MutexLock()
{
	pthread_mutex_destroy(&_mutex);
}

pthread_mutex_t * MutexLock::getMutexLockPtr()
{
	return &_mutex;
}
void MutexLock::lock()
{
	pthread_mutex_lock(&_mutex);
	_isLocking = true;
}

void MutexLock::unlock()
{
	pthread_mutex_unlock(&_mutex);
	_isLocking = false;
}

}
