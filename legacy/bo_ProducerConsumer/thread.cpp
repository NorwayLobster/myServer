//
//  thread.cpp
//  pthread线程
//
//  Created by ChengWang on 3/10/19.
//  Copyright © 2019 ChengWangMacPro15.4. All rights reserved.
//

#include "thread.hpp"
#include "pthread.h"
#include <iostream>
using std::cout;
using std::endl;

Thread::Thread(ThreadCallback cb):
__isRunning(false),
__cb(cb)
{
    cout<<"Thread()"<<endl;
}

Thread::~Thread(){
    cout<<"~Thread()"<<endl;
    if(__isRunning){
        pthread_detach(__pthId);
        __isRunning=false;
    }
}

void * Thread::threadFunc(void * arg){
    cout<<"threadFunc()"<<endl;
    Thread * p = static_cast<Thread *>(arg);
    if(p!=nullptr)
        p->__cb();
    return nullptr;//very important
}

void Thread::start(){
    cout<<"start()"<<endl;
    pthread_create(&__pthId,NULL,threadFunc,this);
    __isRunning=true;
}

void Thread::join(){
    cout<<"join()"<<endl;
    pthread_join(__pthId,NULL);
    __isRunning=false;
//    pthread_join(&__pthId,NULL);
}
