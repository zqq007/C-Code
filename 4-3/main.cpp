#include <iostream>
#include <signal.h>
#include <unistd.h>

void showPending(const sigset_t &sig)
{
    // 信号集是1-31
    for (int i = 31; i >= 1; --i)
    {
        if (sigismember(&sig, i))
            std::cout << 1;
        else
            std::cout << 0;
    }
    std::cout << std::endl;
}

int main()
{
    sigset_t block, oblock, pending;

    // 初始化
    sigemptyset(&block);
    sigemptyset(&oblock);
    sigemptyset(&pending);

    // 将SIGINT信号阻塞
    sigaddset(&block, SIGINT);

    // 修改BLOCK表
    sigprocmask(SIG_SETMASK, &block, &oblock);

    // 打印，获取pending
    int cnt = 8;
    while (true)
    {
        sigpending(&pending);
        showPending(pending);
        sleep(1);
        if (--cnt == 0)
        {
            // 恢复对信号的屏蔽
            sigprocmask(SIG_SETMASK, &oblock, &block);
            std::cout << "恢复对信号的屏蔽" << std::endl;
        }
    }
    return 0;
}

void handler(int signo)
{
    std::cout << "cath signo is " << signo << std::endl;
}

// int main()
// {
//     signal(6, handler);

//     while (true)
//     {
//         sleep(1);
//         abort();
//     }
//     return 0;
// }

// int main()
// {
//     signal(SIGINT, handler);

//     sigset_t block;
//     sigemptyset(&block);
//     sigaddset(&block, SIGINT);
//     sigprocmask(SIG_BLOCK, &block, NULL); // 阻塞SIGINT信号

//     printf("Press Ctrl+C (SIGINT)\n");
//     std::cout << "休眠5秒，期间对SIGINT信号阻塞，按CTRL+C试试" << std::endl;
//     sleep(5);

//     std::cout << std::endl;
//     std::cout << "5秒结束，取消对SIGINT的阻塞" << std::endl;
//     sigdelset(&block, SIGINT);
//     sigprocmask(SIG_SETMASK, &block, nullptr);

//     return 0;
// }
