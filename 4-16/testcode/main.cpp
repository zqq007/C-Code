#include <iostream>
#include <string>
#include <unistd.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

const int num = 5;

void *active(void *args)
{
    std::string name = static_cast<const char *>(args);

    while (true)
    {
        pthread_mutex_lock(&mutex);

        pthread_cond_wait(&cond, &mutex);
        std::cout << name << " activity" << std::endl;
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t tids[num];

    // 创建线程
    for (int i = 0; i < num; ++i)
    {
        char *name = new char[32];
        snprintf(name, 32, "thread-%d", i + 1);
        pthread_create(tids + i, nullptr, active, name);
    }

    sleep(3); // 保证每个线程都进入等待队列

    while (true)
    {
        std::cout << "main thread wakeup thread..." << std::endl;
        pthread_cond_signal(&cond);
        sleep(1);
    }

    for (int i = 0; i < num; ++i)
    {
        pthread_join(tids[i], nullptr);
    }
    return 0;
}