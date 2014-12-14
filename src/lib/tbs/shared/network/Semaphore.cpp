/* 
 * File:   Semaphore.cpp
 * Author: maxence
 * 
 * Created on 14 décembre 2014, 11:41
 */

#include "shared/network/Semaphore.h"

Semaphore::Semaphore(int count)
: m_count(count) {

}

Semaphore::~Semaphore() {
}

void Semaphore::aquire(int permits) {
    std::unique_lock<std::mutex> lock(m_mutex);

    if (m_count < 0 && m_count + permits >= 0) {
        m_count += permits;
        m_cv.notify_all();
    } else {
        m_count += permits;
    }
}

void Semaphore::release(int permits) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_count -= permits;
    if (m_count < 0)
        m_cv.wait(lock);
}
