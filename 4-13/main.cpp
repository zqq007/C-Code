#include <iostream>
#include <vector>
#include <algorithm>
#include <pthread.h>
#include <unistd.h>

// using namespace std;

// template <class T1, class T2>
// class Data
// {
// public:
//     Data() : _pair.first = (T1)0, _pair.second = (T2)0 {}
//     Data(std::piar<T1, T2> pair) : _pair = pair {}

// private:
//     std::pair<T1, T2> _pair;
// };

// // template <>
// // class Less<Date *>
// // {
// // };

// template <typename T>
// class Less
// {
//     bool operator()(const T &x, const T &y) const
//     {
//         return x.first < y.first;
//     }
// };

// int main()
// {
//     // Data d1(std::make_pair<int, double>(1, 1.1));
//     // std::vector<Data> v;

//     std::pair<int, double> d(std::make_pair<int, double>(1, 1.1));
//     double res = d.first * d.second;
//     std::cout << res << std::endl;
//     return 0;
// }

// void *func(void *arg)
// {
//     pthread_detach(pthread_self());
//     std::cout << "func pthread exit" << std::endl;
//     return nullptr;
// }

// int main()
// {
//     pthread_t tid;
//     int res = pthread_create(&tid, nullptr, func, nullptr);

//     sleep(1); // 先等线程分离
//     if (pthread_join(tid, nullptr) == 0)
//         std::cout << "pthread wait sucess" << std::endl;
//     else
//         std::cout << "pthread wait fail" << std::endl;
//     return 0;
// }

int ticket = 100;
pthread_mutex_t mutex;

// 模拟抢票
void *route(void *arg)
{
    const char *name = static_cast<const char *>(arg);
    // std::cout << name << "pthread running..." << std::endl;
    while (true)
    {
        pthread_mutex_lock(&mutex);
        if (ticket > 0)
        {
            usleep(1000);
            std::cout << name << " sells ticket: " << ticket-- << std::endl;
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
    return nullptr;
}

int main()
{
    pthread_t t1, t2, t3, t4;

    // 初始化互斥锁
    pthread_mutex_init(&mutex, nullptr);

    // 线程运行
    pthread_create(&t1, nullptr, route, (void *)"pthread t1");
    pthread_create(&t2, nullptr, route, (void *)"pthread t2");
    pthread_create(&t3, nullptr, route, (void *)"pthread t3");
    pthread_create(&t4, nullptr, route, (void *)"pthread t4");

    // 等待线程
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);
    pthread_join(t4, nullptr);

    // 销毁互斥锁
    pthread_mutex_destroy(&mutex);

    return 0;
}