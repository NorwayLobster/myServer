//
//  MutexLockGuard.cpp
//  mutex condition 互斥锁 条件变量的封装
//
//  Created by ChengWang on 3/10/19.
//  Copyright © 2019 ChengWangMacPro15.4. All rights reserved.
//


#include "MutexLockGuard.hpp"
#include "mutex.h"
#include <iostream>
using std::cout;
using std::endl;
MutexLockGuard::MutexLockGuard(MutexLock& mutex):
__mutex(mutex)
{
    cout<<"MutexLockGuard()"<<endl;
    __mutex.lock();
}

MutexLockGuard::~MutexLockGuard(){
    cout<<"~MutexLockGuard()"<<endl;
    __mutex.unlock();
}
