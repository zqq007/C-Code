#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <unistd.h>
#include <memory>

/*先是单生产单消费，再是多生产多消费*/

const size_t global_cap = 5;

template <class T>
class blockqueue
{
public:
    blockqueue(const size_t &cap = global_cap) : _cap(cap)
    {
        // 初始化条件变量和锁
        pthread_cond_init(&_consumer, nullptr);
        pthread_cond_init(&_producer, nullptr);
        pthread_mutex_init(&_mutex, nullptr);
    }

    void push(const T &val)
    {
        pthread_mutex_lock(&_mutex);
        while (_bq.size() == _cap)
        {
            pthread_cond_wait(&_producer, &_mutex);
        }
        _bq.push(val);
        pthread_cond_signal(&_consumer);
        pthread_mutex_unlock(&_mutex);
    }

    void pop(T *val)
    {
        pthread_mutex_lock(&_mutex);
        while (_bq.empty())
        {
            pthread_cond_wait(&_consumer, &_mutex);
        }
        *val = _bq.front();
        _bq.pop();
        pthread_cond_signal(&_consumer);
        pthread_mutex_unlock(&_mutex);
    }

    ~blockqueue()
    {
        // 释放条件变量和锁
        pthread_cond_destroy(&_consumer);
        pthread_cond_destroy(&_producer);
        pthread_mutex_destroy(&_mutex);
    }

private:
    std::queue<T> _bq;
    pthread_mutex_t _mutex;
    pthread_cond_t _consumer; // 消费者条件变量
    pthread_cond_t _producer; // 生产者条件变量
    size_t _consumer_index;   // 环形队列中消费者当前位置
    size_t _producer_index;   // 环形队列中生产者当前位置

    size_t _cap; // 队列容量
};