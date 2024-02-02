/*静态库链接*/
// #include "myfunc.hpp"

// int main()
// {
//     func1();
//     func2();
//     return 0;
// }

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>

// #define FRONT '='
// #define NEXT '>'

// #define SIZE 102
// #define PROG '='
// #define END '>'

// void progress()
// {
//     const char *tab = "|/-\\";
//     char str[SIZE];
//     memset(str, '\0', SIZE);
//     int i = 0;
//     while (i <= 100)
//     {
//         printf("[%-100s][%d%%][%c]\r", str, i, tab[i % 4]);
//         str[i++] = PROG;
//         if (i != 100)
//             str[i] = END;
//         fflush(stdout);
//         usleep(100000);
//     }
//     printf("\n");
// }

// int main()
// {
//     // printf("hello world");
//     // sleep(2);

//     char buf[101];
//     memset(&buf, '\0', sizeof(buf));
//     // buf[0] = '[';
//     // buf[10] = ']';
//     int i = 0;
//     while (i <= 100)
//     {
//         printf("[%-100s][%d%%]\r", buf, i);
//         buf[i++] = PROG;
//         if (i != 100)
//             buf[i] = END;
//         fflush(stdout);

//         usleep(10000);
//     }
//     printf("\n");

//     // progress();
//     return 0;
// }

// #include <unistd.h>
// #include <string.h>
// int main()
// {
//     int i = 0;
//     char bar[102];
//     memset(bar, 0, sizeof(bar));
//     const char *lable = "|/-\\";
//     while (i <= 100)
//     {
//         printf("[%-100s][%d%%][%c]\r", bar, i, lable[i % 4]);
//         fflush(stdout);
//         bar[i++] = '#';
//         usleep(10000);
//     }
//     printf("\n");
//     return 0;
// }

// int main()
// {
//     while (true)
//     {
//         sleep(1);
//     }
//     return 0;
// }

// int main()
// {
//     std::cout << "getpid:" << getpid() << std::endl;
//     std::cout << "getppid:" << getppid() << std::endl;
//     return 0;
// }

int main()
{
    pid_t ret = fork();
    if (ret < 0)
    {
        perror("fork fail");
        exit(-1);
    }
    else if (ret == 0) // 子进程
    {
        std::cout << "我是子进程,进程id为:" << getpid() << std::endl;
        sleep(5);
        exit(EXIT_SUCCESS);
    }
    else // 父进程
    {
        std::cout << "我是父进程,进程id为:" << getppid() << std::endl;
        sleep(30);
    }
    return 0;
}