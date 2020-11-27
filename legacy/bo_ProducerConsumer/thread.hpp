//
//  thread.hpp
//  pthread线程
//
//  Created by ChengWang on 3/10/19.
//  Copyright © 2019 ChengWangMacPro15.4. All rights reserved.
//

#ifndef thread_hpp
#define thread_hpp
//#include "Nocopyable"
#include <boost/noncopyable.hpp>
#include <stdio.h>
#include <pthread.h>
#include <functional>
using std::function;
class Thread:public boost::noncopyable{
    using ThreadCallback = std::function<void()>;
public:
    Thread(ThreadCallback);
    ~Thread();
    void start();
    void join();
private:
    static void * threadFunc(void *);
private:
    pthread_t __pthId;
    bool __isRunning;
    ThreadCallback __cb;
};
#endif /* thread_hpp */
