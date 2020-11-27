//
//  main.cpp
//  bo_ProducerConsumer
//
//  Created by ChengWang on 3/10/19.
//  Copyright © 2019 ChengWangMacPro15.4. All rights reserved.
//

#include "taskQueue.hpp"
#include  "condition.hpp"
#include  "MutexLockGuard.hpp"
#include  "thread.hpp"
#include  "mutex.h"
#include  "unistd.h"
#include <pthread.h>
#include <iostream>
#include <memory>
using std::shared_ptr;
using std::function;
using std::bind;
using std::cout;
using std::endl;
using Task = int;
int cnt=20;
class Producer{
public:
    void produce(taskQueue& tq){
        while(--cnt){
        Task number = ::rand() % 100;
        cout<<"produce:"<<number<<" in pid:"<<pthread_self()<<endl;
//        shared_ptr<Task> ptask(new Task);
//        Task task;
        tq.push(number);
        sleep(2);
        }
    }
};

class Consumer{
public:
    void consume(taskQueue& tq){
        ::srand(::time(NULL));
        while(--cnt){
        Task number=tq.pop();
        cout<<"consume:"<<number<<" in pid:"<<pthread_self()<<endl;
//        shared_pthr<Task> ptask=tq.pop();
        sleep(3);
        }
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n"<<endl;
    taskQueue tq(20);
    Consumer consumer;
    Producer producer;
    Thread producerThread(bind(&Producer::produce, &producer,std::ref(tq)));
    Thread consumerThread(bind(&Consumer::consume, &consumer,std::ref(tq)));
    producerThread.start();
    consumerThread.start();
    
    producerThread.join();
    consumerThread.join();
	return 0;
}

