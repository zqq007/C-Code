#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <pthread.h>
#include <unistd.h>
#include "Thread.hpp"
#include "LockGuard.hpp"

// Debug
#define MY_CODE
// #define T_CODE

#ifdef MY_CODE

static const int N = 5;

template <class T>
class ThreadPool
{
private:
    void Wait() { pthread_cond_wait(&_cond, &_mutex); } // 进入线程等待

    void Wakeup() { pthread_cond_signal(&_cond); } // 唤醒一个线程

    ThreadPool(const int num = N) : _threadCnt(num) //, _pool(num)
    {
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_cond, nullptr);

        init();
        start();
    }

    ThreadPool(const ThreadPool &self) = delete;
    ThreadPool<T> operator=(const ThreadPool<T> &) = delete;

public:
    static ThreadPool<T> *getInstace()
    {
        if (nullptr == instance)
        {
            LockGuard lock(&instance_mutex);
            if (nullptr == instance)
            {
                instance = new ThreadPool();
            }
        }
        return instance;
    }

    pthread_mutex_t *getlock() { return &_mutex; }

    bool isEmpty() { return _queue.empty(); }

    static void threadRoutinue(void *args)
    {
        ThreadPool<T> *pool = static_cast<ThreadPool<T> *>(args);
        while (true)
        {
            // 先判断有没有数据
            T data;
            {
                LockGuard lock(pool->getlock());
                while (pool->isEmpty())
                {
                    // std::cout << "not data..." << std::endl;
                    // sleep(1);
                    pool->Wait();
                }

                // std::cout << "已取出一个数据" << std::endl;

                // 走到这里表示一定有数据
                data = pool->pop();
            }

            std::cout << data << std::endl;
        }
    }

    void init()
    {
        for (int i = 0; i < _threadCnt; ++i)
        {
            _pool.push_back(Thread(i, threadRoutinue, this));
        }
    }

    void start()
    {
        for (auto &t : _pool)
            t.run();
    }

    void push(const T &data)
    {
        LockGuard lock(&_mutex);
        // std::cout << "已放入一个数据" << std::endl;
        _queue.push(data);
        Wakeup();
    }

    T pop()
    {
        // LockGuard lock(&_mutex);
        T data;
        data = _queue.front();
        _queue.pop();
        return data;
    }

    ~ThreadPool()
    {
        for (auto &t : _pool)
            t.join();
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond);
    }

private:
    int _threadCnt;            // 创建线程的个数
    std::vector<Thread> _pool; // 线程池
    std::queue<T> _queue;      // 里面是任务队列
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;

    // 单例模式--饿汉模式
    static ThreadPool<T> *instance;
    static pthread_mutex_t instance_mutex;
};

template <class T>
ThreadPool<T> *ThreadPool<T>::instance = nullptr;

template <class T>
pthread_mutex_t ThreadPool<T>::instance_mutex = PTHREAD_MUTEX_INITIALIZER;

#endif

#ifdef T_CODE

#include "Task.hpp"

const static int N = 5;

template <class T>
class ThreadPool
{
private:
    ThreadPool(int num = N) : _num(num)
    {
        pthread_mutex_init(&_lock, nullptr);
        pthread_cond_init(&_cond, nullptr);
    }
    ThreadPool(const ThreadPool<T> &tp) = delete;
    void operator=(const ThreadPool<T> &tp) = delete;

public:
    static ThreadPool<T> *getinstance()
    {
        if (nullptr == instance) // 为什么要这样？提高效率，减少加锁的次数！
        {
            LockGuard lockguard(&instance_lock);
            if (nullptr == instance)
            {
                instance = new ThreadPool<T>();
                instance->init();
                instance->start();
            }
        }

        return instance;
    }

    pthread_mutex_t *getlock()
    {
        return &_lock;
    }
    void threadWait()
    {
        pthread_cond_wait(&_cond, &_lock);
    }
    void threadWakeup()
    {
        pthread_cond_signal(&_cond);
    }
    bool isEmpty()
    {
        return _tasks.empty();
    }
    T popTask()
    {
        T t = _tasks.front();
        _tasks.pop();
        return t;
    }
    static void threadRoutine(void *args)
    {
        // pthread_detach(pthread_self());
        ThreadPool<T> *tp = static_cast<ThreadPool<T> *>(args);
        while (true)
        {
            // 1. 检测有没有任务
            // 2. 有：处理
            // 3. 无：等待
            // 细节：必定加锁
            T t;
            {
                LockGuard lockguard(tp->getlock());
                while (tp->isEmpty())
                {
                    tp->threadWait();
                }
                t = tp->popTask(); // 从公共区域拿到私有区域
            }
            // for test
            t();
            std::cout << "thread handler done, result: " << t.formatRes() << std::endl;
            // t.run(); // 处理任务，应不应该在临界区中处理？1,0
        }
    }
    void init()
    {
        for (int i = 0; i < _num; i++)
        {
            _threads.push_back(Thread(i, threadRoutine, this));
        }
    }
    void start()
    {
        for (auto &t : _threads)
        {
            t.run();
        }
    }
    void check()
    {
        for (auto &t : _threads)
        {
            std::cout << t.threadname() << " running..." << std::endl;
        }
    }
    void pushTask(const T &t)
    {
        LockGuard lockgrard(&_lock);
        _tasks.push(t);
        threadWakeup();
    }
    ~ThreadPool()
    {
        for (auto &t : _threads)
        {
            t.join();
        }
        pthread_mutex_destroy(&_lock);
        pthread_cond_destroy(&_cond);
    }

private:
    std::vector<Thread> _threads;
    int _num;

    std::queue<T> _tasks; // 使用stl的自动扩容的特性

    pthread_mutex_t _lock;
    pthread_cond_t _cond;

    static ThreadPool<T> *instance;
    static pthread_mutex_t instance_lock;
};

template <class T>
ThreadPool<T> *ThreadPool<T>::instance = nullptr;

template <class T>
pthread_mutex_t ThreadPool<T>::instance_lock = PTHREAD_MUTEX_INITIALIZER;

#endif