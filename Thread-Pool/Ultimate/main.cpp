#include "ThreadPool.hpp"

#ifdef MY_CODE

int main()
{
    ThreadPool<std::string> *pool = ThreadPool<std::string>::getInstace();
    // pool.init();
    // pool.start();

    while (true)
    {
        std::string message;
        std::getline(std::cin, message);

        pool->push(message);
    }
    return 0;
}

#endif

#ifdef T_CODE

int main()
{
    // std::unique_ptr<ThreadPool<Task>> tp(new ThreadPool<Task>(20));
    // tp->init();
    // tp->start();
    // tp->check();
    printf("0X%p\n", ThreadPool<Task>::getinstance());
    printf("0X%p\n", ThreadPool<Task>::getinstance());
    // printf("0X%x\n", ThreadPool<Task>::getinstance());
    // printf("0X%x\n", ThreadPool<Task>::getinstance());
    // printf("0X%x\n", ThreadPool<Task>::getinstance());
    // printf("0X%x\n", ThreadPool<Task>::getinstance());

    while (true)
    {
        int x, y;
        char op;
        std::cout << "please Enter x> ";
        std::cin >> x;
        std::cout << "please Enter y> ";
        std::cin >> y;
        std::cout << "please Enter op(+-*/%)> ";
        std::cin >> op;

        Task t(x, y, op);
        ThreadPool<Task>::getinstance()->pushTask(t); // 单例对象也有可能在多线程场景中使用！
        // tp->pushTask(t);

        // 充当生产者, 从网络中读取数据，构建成为任务，推送给线程池
        // sleep(1);
        // tp->pushTask();
    }
}

#endif