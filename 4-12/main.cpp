#include <iostream>
#include <unistd.h>
#include <pthread.h>

void my_exit()
{
    exit(0);
}

void *func(void *arg)
{
    // int i = *(int *)arg;

    // if (i == 2)
    // {
    //     my_exit();
    // }

    // printf("I'm %dth thread, Thread_ID = %lu\n", i + 1, pthread_self());

    // pthread_exit(NULL);
    return (void *)111;
}

// int main()
// {
//     int n = 5;
//     pthread_t tid[n];

//     for (int i = 0; i < n; ++i)
//         tid[i] = -1;

//     for (int i = 0; i < n; ++i)
//     {
//         pthread_create(&tid[i], nullptr, func, (void *)&i);
//     }

//     printf("I am main, and I am not a process, I'm a thread!\n"
//            "main_thread_ID = %lu\n",
//            pthread_self());

//     void *ret = nullptr;
//     for (int i = 0; i < n; ++i)
//     {
//         pthread_join(tid[i], &ret);
//         std::cout << "main thread join sucess , *ret:" << (long long)ret << std::endl;
//     }
//     return 0;
// }

// int main()
// {
//     pthread_t tid = 0;
//     int res = pthread_create(&tid, nullptr, func, (void *)0);

//     void *ret = nullptr;
//     pthread_join(tid, &ret);
//     std::cout << "main thread join success, *ret: " << (long long)ret << std::endl;
//     return 0;
// }

auto multiply(double x, int y) -> decltype(x * y)
{
    return x * y;
}

template <class T>
auto multiply(T x, T y)
{
    return x * y;
}

int main()
{
    std::cout << multiply(2, 3) << std::endl;
    std::cout << multiply(2.5, 3) << std::endl;
    return 0;
}