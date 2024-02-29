#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

// int main()
// {
//     sleep(5);
//     int fd = open("file1.txt", O_CREAT | O_RDWR, 0644);
//     if (fd == -1)
//         exit(errno);
//     return 0;
// }

// int main()
// {
//     int cnt = 14;
//     alarm(1);
//     while (true)
//     {
//         printf("cnt:%d\n", cnt++);
//     }
//     return 0;
// }

// void settime(int signum)
// {
//     printf("begin dingshi\n");
//     printf("signum=%d\n", signum);
// }
// int main()
// {
//     signal(SIGALRM, settime);
//     alarm(2);
//     while (1)
//     {
//         int i = 1;
//         printf("i=%d\n", i);
//     }
//     return 0;
// }

void handler(int signum)
{
    std::cout << "catch a sig:" << signum << std::endl;
}

int main()
{
    // signal(SIGSEGV, handler);
    signal(2, handler);

    // int *p = nullptr;
    // *p = 100;
    // while (true)
    //     ;

    while(true);
    return 0;
}