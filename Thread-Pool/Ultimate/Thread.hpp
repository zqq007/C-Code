#pragma once

#include <iostream>
#include <functional>

// Debug
#define MY_THREAD
// #define T_THREAD

#ifdef MY_THREAD

// typedef std::function<void *(void *)> func_t;
typedef void (*func_t)(void *);

class Thread
{
public:
    typedef enum
    {
        NEW,
        STOP,
        RUNNING
    } ThreadStatus;

public:
    Thread(int num, func_t handlers, void *args) : _id(num), _handlers(handlers), _args(args), _threadStatus(NEW) {}

    static void *threadRoutinue(void *args)
    {
        Thread *thread = static_cast<Thread *>(args);
        (*thread)();
        return nullptr;
    }

    void operator()()
    {
        if (_handlers)
        {
            // std::cout << "run handlers" << std::endl;
            _handlers(_args);
        }
    }

    void run()
    {
        int n = pthread_create(&_id, nullptr, threadRoutinue, this);
        if (n != 0)
        {
            std::cerr << "create thread error" << std::endl;
            exit(-1);
        }
        _threadStatus = RUNNING;
    }

    void join()
    {
        pthread_join(_id, nullptr);
        _threadStatus = STOP;
    }

    ~Thread() {}

private:
    pthread_t _id;
    func_t _handlers;
    void *_args;
    ThreadStatus _threadStatus;
};

#endif

#ifdef T_THREAD

class Thread
{
public:
    typedef enum
    {
        NEW = 0,
        RUNNING,
        EXITED
    } ThreadStatus;
    typedef void (*func_t)(void *);

public:
    Thread(int num, func_t func, void *args) : _tid(0), _status(NEW), _func(func), _args(args)
    {
        char name[128];
        snprintf(name, sizeof(name), "thread-%d", num);
        _name = name;
    }
    int status() { return _status; }
    std::string threadname() { return _name; }
    pthread_t threadid()
    {
        if (_status == RUNNING)
            return _tid;
        else
        {
            return 0;
        }
    }
    // 是不是类的成员函数，而类的成员函数，具有默认参数this,需要static
    // 但是会有新的问题：static成员函数，无法直接访问类属性和其他成员函数
    static void *runHelper(void *args)
    {
        Thread *ts = (Thread *)args; // 就拿到了当前对象
        // _func(_args);
        (*ts)();
        return nullptr;
    }
    void operator()() // 仿函数
    {
        if (_func != nullptr)
            _func(_args);
    }
    void run()
    {
        int n = pthread_create(&_tid, nullptr, runHelper, this);
        if (n != 0)
            exit(1);
        _status = RUNNING;
    }
    void join()
    {
        int n = pthread_join(_tid, nullptr);
        if (n != 0)
        {
            std::cerr << "main thread join thread " << _name << " error" << std::endl;
            return;
        }
        _status = EXITED;
    }
    ~Thread()
    {
    }

private:
    pthread_t _tid;
    std::string _name;
    func_t _func; // 线程未来要执行的回调
    void *_args;
    ThreadStatus _status;
};

#endif