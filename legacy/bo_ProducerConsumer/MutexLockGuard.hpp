//
//  MutexLockGuard.hpp
//  mutex condition 互斥锁 条件变量的封装
//
//  Created by ChengWang on 3/10/19.
//  Copyright © 2019 ChengWangMacPro15.4. All rights reserved.
//

#ifndef MutexLockGuard_hpp
#define MutexLockGuard_hpp
#include <boost/noncopyable.hpp>

#include <stdio.h>
class MutexLock;
class MutexLockGuard{
public:
    MutexLockGuard(MutexLock &);
    ~MutexLockGuard();
private:
    MutexLock & __mutex;
};

#endif /* MutexLockGuard_hpp */
