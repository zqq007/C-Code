#include <iostream>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

// int main()
// {
//     struct sockaddr_in host;
//     host.sin_addr.s_addr = inet_addr("127.0.0.1");
//     // uint32_t *ptr = static_cast<uint32_t *>(&host.sin_addr);
//     uint32_t *ptr = (uint32_t *)(&host.sin_addr);

//     std::cout << "*ptr:" << *ptr << std::endl;
//     std::cout << "host.sin_addr" << inet_ntoa(host.sin_addr);
//     return 0;
// }

// 检测inet_ntoa函数是否线程安全
void *threadRoutinue1(void *args)
{
    struct sockaddr_in *host = static_cast<struct sockaddr_in *>(args);
    while (true)
    {
        char *ptr = inet_ntoa(host->sin_addr);
        std::cout << "host1:" << *ptr << std::endl;
        sleep(1);
    }
}

void *threadRoutinue2(void *args)
{
    struct sockaddr_in *host = static_cast<struct sockaddr_in *>(args);
    while (true)
    {
        char *ptr = inet_ntoa(host->sin_addr);
        std::cout << "host2:" << *ptr << std::endl;
        sleep(1);
    }
}

int main()
{
    pthread_t t1, t2;
    struct sockaddr_in host1;
    host1.sin_addr.s_addr = 0;
    struct sockaddr_in host2;
    host2.sin_addr.s_addr = 0xffffffff;

    // 创建线程
    pthread_create(&t1, nullptr, threadRoutinue1, &host1);
    pthread_create(&t2, nullptr, threadRoutinue2, &host2);

    // 释放
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    return 0;
}