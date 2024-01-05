#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>
#include <vector>
#include <functional>

using func_t = std::function<void(void)>;

std::vector<func_t> funcs;

void Task1()
{
    // 待定
    std::cout << "Task1" << std::endl;
}

void Task2()
{
    std::cout << "Task2" << std::endl;
}

void Task3()
{
    std::cout << "Task3" << std::endl;
}

void LoadTask()
{
    funcs.push_back(Task1);
    funcs.push_back(Task2);
    funcs.push_back(Task3);
}

void RunTask()
{
    for (const auto &func : funcs)
        func();
}

void NonBlock(int fd)
{
    int f1 = fcntl(fd, F_GETFL);
    if (f1 < 0)
    {
        std::cerr << "fcntl fail:" << strerror(errno) << std::endl;
    }
    fcntl(fd, F_SETFL, f1 | O_NONBLOCK);
}

int main()
{
    char buffer[64] = {0};
    NonBlock(0);
    int flag = 1; // 表示只执行一次
    LoadTask();
    while (true)
    {
        std::cout << ">>";
        fflush(stdout);
        ssize_t n = read(0, buffer, sizeof(buffer) - 1);
        if (n > 0)
        {
            buffer[n - 1] = 0;
            std::cout << "echo# " << buffer << std::endl;
        }
        else if (n == 0)
        {
            std::cout << "read file end" << std::endl;
            break;
        }
        else
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                sleep(1);

                // 执行别的任务
                if (flag == 1)
                {
                    RunTask();
                    flag = 0;
                }

                // 这是是表示数据没有准备好
                std::cout << "data not ready" << std::endl;
                continue;
            }
            else if (errno == EINTR)
            {
                // 这是是表示被信号中断
                continue;
            }
            else
            {
                std::cerr << "errno sting: " << strerror(errno) << "errno code:" << errno << std::endl;
            }
            break;
        }
    }
    return 0;
}