#include "thread_pool.hpp"

bool handlers(int data)
{
    srand(time(nullptr));
    int n = rand() % 5;
    std::cout << "thread id:" << pthread_self() << " data: " << data << " sleep:" << n << " second" << std::endl;
    sleep(n);
    return true;
}

int main()
{
    threadPool pool;

    for (int i = 0; i < 5; ++i)
    {
        threadTask *task = new threadTask(i, handlers);
        pool.push(task);
    }

    // sleep(5);
    // pool.init();

    // pool.quit();
    return 0;
}