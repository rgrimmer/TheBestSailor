/*
 * Gzzzt, a Bomberman clone with robots and lightnings!
 * Copyright (C) 2014 Gzzzt team (see AUTHORS)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SYNCHRONIZED_QUEUE_H
#define SYNCHRONIZED_QUEUE_H

#include <mutex>
#include <queue>
#include <condition_variable>
#include <chrono>

#include <SFML/System/Time.hpp>

template<class T>
class SynchronizedQueue {
public:

    bool empty() {
        std::unique_lock<std::mutex> lock(m_qMutex);
        bool isEmpty = m_queue.empty();
        return isEmpty;
    }

    T pop() {
        std::unique_lock<std::mutex> lock(m_qMutex);
        T value = m_queue.front();
        m_queue.pop();
        return value;
    }

    T& peek() {
        std::unique_lock<std::mutex> lock(m_qMutex);
        T& value = m_queue.front();
        return value;
    }

    void push(const T& value) {
        std::unique_lock<std::mutex> lock(m_qMutex);
        m_queue.push(value);
        m_cond.notify_one();
    }

    bool waitEvent(sf::Time timeout) {
        std::unique_lock<std::mutex> lock(m_qMutex);
        if (timeout == sf::Time::Zero)
            m_cond.wait(lock);
        else
            return (m_cond.wait_for(lock, std::chrono::milliseconds(timeout.asMilliseconds())) == std::cv_status::no_timeout);
        return true;
    }

protected:
    std::queue<T> m_queue;
    std::mutex m_qMutex;
    std::condition_variable m_cond;
};


#endif // SYNCHRONIZED_QUEUE_H
