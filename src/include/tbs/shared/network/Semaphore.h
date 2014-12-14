/* 
 * File:   Semaphore.h
 * Author: maxence
 *
 * Created on 14 décembre 2014, 11:41
 */

#ifndef SEMAPHORE_H
#define	SEMAPHORE_H

#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore(int count = 0);
    virtual ~Semaphore();
    
    void aquire(int permits = 1);
    void release(int permits = 1);
    
private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
    int m_count;
    

};

#endif	/* SEMAPHORE_H */

