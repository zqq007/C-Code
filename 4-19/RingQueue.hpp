#pragma once

#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <vector>
#include <semaphore.h>

static const size_t len = 5;

template <class T>
class RingQueue
{
private:
    void P(sem_t &sem)
    {
        sem_wait(&sem);
    }

    void V(sem_t &sem)
    {
        sem_post(&sem);
    }

    void Lock(pthread_mutex_t &mutex)
    {
        pthread_mutex_lock(&mutex);
    }

    void Unlock(pthread_mutex_t &mutex)
    {
        pthread_mutex_unlock(&mutex);
    }

public:
    RingQueue(const size_t num = len) : _rq(num), _cap(num) //, _con_index(0), _pro_index(0)
    {
        // 初始化信号量
        sem_init(&_data_sem, 0, 0);
        sem_init(&_space_sem, 0, num);
        _con_index = _pro_index = 0;

        pthread_mutex_init(&_con_mutex, nullptr);
        pthread_mutex_init(&_pro_mutex, nullptr);
    }

    void push(const T &data)
    {
        // 生产
        P(_space_sem);
        Lock(_pro_mutex);
        // 走到这里说明一定能放数据
        _rq[_pro_index++] = data;
        _pro_index %= _cap;
        // Debug
        // std::cout << _pro_index << std::endl;
        Unlock(_pro_mutex);
        V(_data_sem);
    }

    void pop(T *data)
    {
        // 消费
        P(_data_sem);
        Lock(_con_mutex);
        // 这里同理，一定有数据
        *data = _rq[_con_index++];
        _con_index %= _cap;
        Unlock(_con_mutex);
        V(_space_sem);
    }

    ~RingQueue()
    {
        // 释放信号量
        sem_destroy(&_data_sem);
        sem_destroy(&_space_sem);

        pthread_mutex_destroy(&_con_mutex);
        pthread_mutex_destroy(&_pro_mutex);
    }

private:
    std::vector<T> _rq;
    size_t _cap;       // 容量
    sem_t _data_sem;   // 消费者关心队列里是否还有数据
    sem_t _space_sem;  // 生产者关心队列里是否还是空间可放数据
    size_t _con_index; // 消费者下一次消费所对应的下标
    size_t _pro_index; // 生产者下一次生产所对应的下标

    pthread_mutex_t _con_mutex; // 多生产多消费版本需要两个锁
    pthread_mutex_t _pro_mutex;
};
