//
//  mutex.cpp
//  mutex condition 互斥锁 条件变量的封装
//
//  Created by ChengWang on 3/9/19.
//  Copyright © 2019 ChengWangMacPro15.4. All rights reserved.
//

#include "mutex.h"
#include <iostream>
using std::endl;
using std::cout;
MutexLock::MutexLock():
__locked(false)
{
    cout<<"MutexLock()"<<endl;
    pthread_mutex_init(&__mutex,nullptr);
}

MutexLock::~MutexLock()
{
    cout<<"~MutexLock()"<<endl;
    pthread_mutex_destroy(&__mutex);
}

void MutexLock::lock(){
    pthread_mutex_lock(&__mutex);
    __locked=true;
    cout<<"lock()"<<endl;
    return ;
}
void MutexLock::unlock(){
    pthread_mutex_unlock(&__mutex);
    __locked = false;
    cout<<"unlock()"<<endl;
    return ;
}

void MutexLock::state(){
    cout<<(__locked? "locked":"not locked")<<endl;
    return;
}

pthread_mutex_t * MutexLock::getPtr(){
    return &__mutex;
}
