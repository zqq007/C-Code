#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>

// int main()
// {
//     int fd[2];
//     if (pipe(fd) == -1)
//     {
//         perror("pipe fail");
//         exit(-1);
//     }

//     char buf[128];
//     int len = 0;

//     while (fgets(buf, 128, stdin))
//     {
//         /* code */
//         len = strlen(buf);
//         if (write(fd[1], buf, len) != len)
//         {
//             perror("write fail");
//             exit(-1);
//         }
//         if (read(fd[0], buf, len) != len)
//         {
//             perror("read fail");
//             exit(-1);
//         }
//         if (write(1, buf, len) != len)
//         {
//             perror("write fail");
//             exit(-1);
//         }
//     }

//     return 0;
// }

int main()
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("pipe fail");
        exit(-1);
    }
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork fail");
        exit(-1);
    }
    else if (pid == 0)
    {
        /*child process*/
        close(fd[0]);
        write(fd[1], "hello", 5);
        close(fd[1]);
    }
    else
    {
        /*parent process*/
        close(fd[1]);
        char buf[10] = {0};
        read(fd[0], buf, 5);

        std::cout << "buf:" << buf << std::endl;
        close(fd[0]);
        wait(nullptr);
    }
    return 0;
}