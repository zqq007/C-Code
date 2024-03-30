#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sys/types.h>

/*计算计算机1秒能数多少个数*/
// int main()
// {
//     int i = 0;
//     alarm(1);
//     while (i++ > -1)
//         std::cout << i << std::endl;
//     // for (int i = 0;; ++i)
//     //     printf("%d\n", i);//164033
//     // std::cout << i << std::endl;//153045
//     return 0;
// }

int main()
{
    int fds[2];
    if (pipe(fds) == -1)
    {
        perror("pipe fail");
        exit(-1);
    }
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork fail");
        exit(-1);
    }
    else if (pid == 0)
    {
        /*子进程*/
        close(fds[0]);
        std::string message = "hello world";
        write(fds[1], message.c_str(), message.size());
        close(fds[1]);
    }
    else
    {
        /*父进程*/
        close(fds[1]);
        std::string message;
        read(fds[0], &message[0], 12);
        std::cout << message.c_str() << std::endl;
        close(fds[0]);
    }
    return 0;
}