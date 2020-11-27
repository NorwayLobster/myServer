//
//  condition.cpp
//  mutex condition 互斥锁 条件变量的封装
//
//  Created by ChengWang on 3/9/19.
//  Copyright © 2019 ChengWangMacPro15.4. All rights reserved.
//

#include "condition.hpp"
#include "mutex.h"
//如果没加mutex.h头文件
/* condition.cpp: In member function ‘void Condition::wait(MutexLock&)’:
 condition.cpp:25:32: error: invalid use of incomplete type ‘class MutexLock’
 pthread_cond_wait(&__cond, mutex.getPtr());
 ^~~~~
 In file included from condition.cpp:9:0:
 condition.hpp:14:7: note: forward declaration of ‘class MutexLock’
 class MutexLock;
 ^~~~~~~~~
*/
#include <iostream>
using std::endl;
using std::cout;
class MutexLock;
Condition::Condition()
{
    cout<<"Condition()"<<endl;
    pthread_cond_init(&__cond,NULL);
}
Condition::~Condition(){
    cout<<"~Condition()"<<endl;
    pthread_cond_destroy(&__cond);
}
void Condition::wait(MutexLock & mutex){
    cout<<"~wait()"<<endl;
    pthread_cond_wait(&__cond, mutex.getPtr());
    cout<<"wakeup()"<<endl;
}
void Condition::notify(){
    cout<<"notify()"<<endl;
    pthread_cond_signal(&__cond);
}
void Condition::notify_all(){
    cout<<"notify_all()"<<endl;
    pthread_cond_broadcast(&__cond);
}
