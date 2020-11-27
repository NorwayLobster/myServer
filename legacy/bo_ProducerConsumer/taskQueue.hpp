//
//  taskQueue.hpp
//  bo_ProducerConsumer
//
//  Created by ChengWang on 3/10/19.
//  Copyright © 2019 ChengWangMacPro15.4. All rights reserved.
//

#ifndef taskQueue_hpp
#define taskQueue_hpp
#include "mutex.h"
#include "condition.hpp"
#include <iostream>
#include <queue>
#include <memory>
using std::cout;
using std::endl;
using std::queue;
using std::shared_ptr;

//using Task = std::function<void()>;
using Task = int;

class taskQueue{
public:
    taskQueue(size_t queSize);
    ~taskQueue();
    bool empty();
    bool full();
    void push(Task );
    Task pop();
    void wakeUp();

private:
    MutexLock __mutex;
    Condition __notEmpty;
    Condition __notFull;
    queue<Task> __que;
//    queue<shared_ptr<Task>> __que;
    size_t __queSize;
};

#endif /* taskQueue_hpp */
