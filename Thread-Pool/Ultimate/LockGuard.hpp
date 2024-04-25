#pragma once

#include <iostream>

class Mutex
{
public:
    Mutex(pthread_mutex_t *mutex) : _mutex(mutex) {}

    void Lock() { pthread_mutex_lock(_mutex); }

    void Unlock() { pthread_mutex_unlock(_mutex); }

    ~Mutex() {}

private:
    pthread_mutex_t *_mutex;
};

class LockGuard
{
public:
    LockGuard(pthread_mutex_t *mutex) : _mutex(mutex) { _mutex.Lock(); }

    ~LockGuard() { _mutex.Unlock(); }

private:
    Mutex _mutex;
};