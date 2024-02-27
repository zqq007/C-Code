#include <iostream>
#include <unistd.h>

// int main()
// {
//     int fd[2];
//     if (pipe(fd) == -1)
//     {
//         perror("pipe fail");
//         exit(-1);
//     }
//     int n = 0;
//     while (true)
//     {
//         if (write(fd[1], "6666", 4) == -1)
//         {
//             perror("write fail");
//             exit(-1);
//         }
//         n++;
//         std::cout << "n:" << n << std::endl;
//     }
//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>

// #define SIZE 64 * 1024 // 64KB

// int main()
// {
//     char A[SIZE];
//     char B[SIZE];

//     memset(A, 'A', sizeof(A));
//     memset(B, 'B', sizeof(B));

//     int pipefd[2];
//     if (pipe(pipefd) < 0)
//     {
//         perror("pipe error");
//         return -1;
//     }

//     int ret = 0;

//     pid_t pid = fork();
//     if (pid < 0)
//     {
//         perror("fork error");
//         return -1;
//     }
//     else if (pid == 0)
//     { // 子进程1写入A
//         close(pipefd[0]);
//         ret = write(pipefd[1], A, sizeof(A)); // 阻塞写入，直到64kB的数据全部写完才返回
//         printf("Child process [%d] wrote %d bytes of character A to the pipeline.\n", getpid(), ret);
//         exit(0);
//     }

//     pid = fork();
//     if (pid < 0)
//     {
//         perror("fork error");
//         return -1;
//     }
//     else if (pid == 0)
//     { // 子进程2写入B
//         close(pipefd[0]);
//         ret = write(pipefd[1], B, sizeof(B)); // 阻塞写入，直到64kB的数据全部写完才返回
//         printf("Child process [%d] wrote %d bytes of character B to the pipeline.\n", getpid(), ret);
//         exit(0);
//     }

//     close(pipefd[1]);
//     sleep(1); // 休眠1s，确保父子进程的写端都已关闭
//     int n = 0;
//     while (1)
//     {
//         char buf[4 * 1024] = {0};
//         ret = read(pipefd[0], buf, sizeof(buf)); // 每次读取4KB数据
//         if (ret == 0)
//         { // 若读完数据，则不再读取
//             printf("Pipeline data has been read out.\n");
//             break;
//         }
//         printf("%2d: Parent process [%d] read %d bytes from the pipeline, buf[4095] = %c\n", ++n, getpid(), ret, buf[4095]);
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>

// #define SIZE 70 * 1024 // 68KB

// int main()
// {
//     char A[SIZE];
//     char B[SIZE];

//     memset(A, 'A', sizeof(A));
//     memset(B, 'B', sizeof(B));

//     int pipefd[2];
//     if (pipe(pipefd) < 0)
//     {
//         perror("pipe error");
//         return -1;
//     }

//     int ret = 0;

//     pid_t pid = fork();
//     if (pid < 0)
//     {
//         perror("fork error");
//         return -1;
//     }
//     else if (pid == 0)
//     { // 子进程1写入A
//         close(pipefd[0]);
//         ret = write(pipefd[1], A, sizeof(A)); // 阻塞写入，直到68kB的数据全部写完才返回
//         printf("Child process [%d] wrote %d bytes of character A to the pipeline.\n", getpid(), ret);
//         exit(0);
//     }

//     pid = fork();
//     if (pid < 0)
//     {
//         perror("fork error");
//         return -1;
//     }
//     else if (pid == 0)
//     { // 子进程2写入B
//         close(pipefd[0]);
//         ret = write(pipefd[1], B, sizeof(B)); // 阻塞写入，直到68kB的数据全部写完才返回
//         printf("Child process [%d] wrote %d bytes of character B to the pipeline.\n", getpid(), ret);
//         exit(0);
//     }

//     close(pipefd[1]);
//     sleep(1); // 休眠1s，确保父子进程的写端都已关闭
//     int n = 0;
//     while (1)
//     {
//         char buf[4 * 1024] = {0};
//         ret = read(pipefd[0], buf, sizeof(buf)); // 每次读取4KB数据
//         if (ret == 0)
//         { // 若读完数据，则不再读取
//             printf("Pipeline data has been read out.\n");
//             break;
//         }
//         printf("%2d: Parent process [%d] read %d bytes from the pipeline, buf[4095] = %c\n", ++n, getpid(), ret, buf[4095]);
//     }

//     return 0;
// }
