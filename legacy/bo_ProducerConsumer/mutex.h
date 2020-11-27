//
//  mutex.h
//  spellCorrection用户输入助手
//
//  Created by ChengWang on 3/9/19.
//  Copyright © 2019 ChengWangMacPro15.4. All rights reserved.
//

#include <pthread.h>
//#include "Noncopyable.h"
#include <boost/noncopyable.hpp>
#ifndef mutex_h
#define mutex_h

class MutexLock:boost::noncopyable {
public:
    MutexLock();
    ~MutexLock();
    void lock();
    void unlock();
    void state();
    pthread_mutex_t * getPtr();
private:
    pthread_mutex_t __mutex;
     bool __locked;
};

#endif /* mutex_h */
