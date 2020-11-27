//
//  taskQueue.cpp
//  bo_ProducerConsumer
//
//  Created by ChengWang on 3/10/19.
//  Copyright © 2019 ChengWangMacPro15.4. All rights reserved.
//

#include "taskQueue.hpp"
#include "MutexLockGuard.hpp"
taskQueue::taskQueue(size_t queSize):
__queSize(queSize),
__mutex(),
__notFull(),
__notEmpty()
{
    cout<<"taskQueue()"<<endl;
}

taskQueue::~taskQueue()
{ cout<<"~taskQueue()"<<endl;};

bool taskQueue::empty(){
    return __que.size()==0;
}

bool taskQueue::full(){
    return __que.size()==__queSize;
}

void taskQueue::push(Task task){
    MutexLockGuard mlg(__mutex);
    while(full()){
        __notFull.wait(__mutex);
    }
    __que.push(task);
    __notEmpty.notify();
}

Task taskQueue::pop(){
    MutexLockGuard mlg(__mutex);
    while(empty()){
        __notEmpty.wait(__mutex);
    }
   Task task = __que.front();
//    shared_ptr<Task> ptask = __que.front();
    __que.pop();
     __notFull.notify();
    return  task;
}

void taskQueue::wakeUp(){};
