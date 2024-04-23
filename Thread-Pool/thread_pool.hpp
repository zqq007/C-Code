#pragma once

#include <iostream>
#include <functional>
#include <queue>
#include <unistd.h>
#include <pthread.h>

#define MAX_THREAD 5

typedef std::function<bool(int)> func_t;

class threadTask
{
public:
    threadTask() : _data(0), _handlers(nullptr) {}
    threadTask(const int &data, const func_t &handlers) : _data(data), _handlers(handlers) {}

    void setThreadTask(const int &data, const func_t &handlers) { _data = data, _handlers = handlers; }

    int getData() { return _data; } // Debug

    void run() { _handlers(_data); }

    ~threadTask() {}

private:
    int _data;
    func_t _handlers;
};

class threadPool
{

private:
    void Lock() { pthread_mutex_lock(&_mutex); }

    void Unlock() { pthread_mutex_unlock(&_mutex); }

public:
    threadPool(const int &cnt = MAX_THREAD) : _max_thread_cnt(cnt)
    {
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_cond, nullptr);

        for (int i = 0; i < _max_thread_cnt; ++i)
        {
            pthread_t tid;
            int res = pthread_create(&tid, nullptr, threadRoutine, this);
            if (res == -1)
            {
                std::cerr << "create thread error" << std::endl;
                exit(-1);
            }
        }
    }

    // void init()
    // {
    //     for (int i = 0; i < _max_thread_cnt; ++i)
    //     {
    //         pthread_t tid;
    //         int res = pthread_create(&tid, nullptr, threadRoutine, this);
    //         if (res == -1)
    //         {
    //             std::cerr << "create thread error" << std::endl;
    //             exit(-1);
    //         }
    //     }
    // }

    static void *threadRoutine(void *args)
    {
        pthread_detach(pthread_self()); // 首先线程分离
        threadPool *pool = static_cast<threadPool *>(args);
        while (true)
        {
            pool->Lock();
            while (pool->_queue.empty())
            {
                pthread_cond_wait(&pool->_cond, &pool->_mutex);
            }
            threadTask *task = nullptr;

            task = pool->_queue.front();
            pool->_queue.pop();

            pool->Unlock();
            std::cout << task->getData() << std::endl;
            task->run();
            delete task;

            pthread_exit(nullptr);
        }
    }

    void push(threadTask *&task)
    {
        Lock();
        _queue.push(task);
        Unlock();
        pthread_cond_signal(&_cond);
    }

    void quit() {}

    ~threadPool()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond);
    }

private:
    int _max_thread_cnt;             // 最大线程数
    std::queue<threadTask *> _queue; // 线程池
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;
};