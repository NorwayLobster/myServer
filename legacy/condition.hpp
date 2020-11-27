//
//  condition.hpp
//  mutex condition 互斥锁 条件变量的封装
//
//  Created by ChengWang on 3/9/19.
//  Copyright © 2019 ChengWangMacPro15.4. All rights reserved.
//

#ifndef condition_hpp
#define condition_hpp

#include <stdio.h>
#include <pthread.h>
#include "Noncopyable.h"
class MutexLock;
class Condition:Noncopyable{
public:
    Condition();
    ~Condition();
    void wait(MutexLock & mutex);
    void notify();
    void notify_all();
private:
    pthread_cond_t __cond;
    // 有对方的引用，聚合？组合？依赖？ 耦合的太重了 MutexLock & __mutex;
};
#endif /* condition_hpp */
