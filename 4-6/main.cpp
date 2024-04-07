#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <vector>

// void handler(int signo)
// {
//     int id = 0;
//     while ((id = waitpid(-1, nullptr, WNOHANG) > 0))
//     {
//         std::cout << "wait child success :" << id << std::endl;
//     }
//     std::cout << "child process quit,id :" << getpid() << std::endl;
// }

// int main()
// {
//     signal(SIGCHLD, handler);
//     pid_t pid = fork();
//     if (pid < 0)
//     {
//         perror("fork fail");
//         exit(-1);
//     }
//     else if (pid == 0) // child process
//     {
//         std::cout << "child id:" << getpid() << std::endl;
//         // sleep(3);
//         exit(2);
//     }
//     else
//     {
//         while (true)
//         {
//             std::cout << "parent process doing some thing" << std::endl;
//             sleep(1);
//         }
//     }
//     return 0;
// }

// void *process(void *p)
// {
//     while (true)
//     {
//         std::cout << "I'm process 1" << std::endl;
//         sleep(1);
//     }
// }

// int main()
// {
//     pthread_t tid;
//     int ret;
//     if ((ret = pthread_create(&tid, nullptr, process, nullptr)) != 0)
//     {
//         fprintf(stderr, "pthread_create : %s\n", strerror(ret));
//         exit(EXIT_FAILURE);
//     }
//     else
//     {
//         while (true)
//         {
//             std::cout << "I'm main process" << std::endl;
//             sleep(1);
//         }
//     }
//     return 0;
// }

void *threadWork(void *arg)
{
    std::cout << "I'm thread id : " << pthread_self() << " data is : " << *(int *)arg << std::endl;
    pthread_exit(nullptr);
}

int main()
{
    int i = 1;
    pthread_t tid;
    int ret = 0;
    ret = pthread_create(&tid, nullptr, threadWork, (void *)&i); // 不要传临时变量
    if (ret != 0)
    {
        perror("pthread_create fail");
        exit(-1);
    }
    while (true)
    {
        std::cout << "I'm main thread" << std::endl;
        sleep(1);
    }
    return 0;
}

class Solution
{
public:
    void duplicateZeros(std::vector<int> &arr)
    {
        int sz = arr.size();
        int top = 0;
        int index = -1;

        // 找到最后一个复写数
        while (top < sz)
        {
            if (arr[++index] != 0)
                top++;
            else
                top += 2;
        }

        int cur = sz - 1;
        if (top == sz + 1) // 如果最后一个复写数为0
        {
            arr[cur] = 0;
            cur--;
            index--;
        }

        while (cur >= 0)
        {
            arr[cur] = arr[index];
            cur--;
            if (arr[index] == 0)
            {
                arr[cur] = 0;
                cur--;
            }
            index--;
        }
    }
};