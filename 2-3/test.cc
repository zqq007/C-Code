#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int g_val = 0;

// int main()
// {
//     // pid_t id = fork();
//     // if (id < 0)
//     // {
//     //     perror("fork fail");
//     //     exit(-1);
//     // }
//     // else if (id == 0)
//     // {
//     //     std::cout << "I am child,id:" << getpid() << std::endl;
//     //     // sleep(10);
//     // }
//     // else
//     // {
//     //     std::cout << "I am parent, id:" << getpid() << std::endl;
//     //     // sleep(3);
//     // }

//     // while (true)
//     // {
//     //     sleep(1);
//     // }

//     // for (int i = 0; env[i]; ++i)
//     // {
//     //     printf("%s\n", env[i]);
//     // }

//     // extern char **environ;
//     // for (int i = 0; environ[i]; ++i)
//     // {
//     //     printf("%s\n", environ[i]);
//     // }

//     // printf("%s\n", getenv("PATH"));

//     // char *env = getenv("MYENV");
//     // if (env)
//     //     printf("%s\n", env);

//     // pid_t id = fork();
//     // if (id < 0)
//     // {
//     //     perror("fork fail");
//     //     exit(-1);
//     // }
//     // else if (id == 0)
//     // {
//     //     g_val = 100;
//     //     printf("我是子进程,我的进程id是:%d,g_val=%d,&g_val=%p\n", getpid(), g_val, &g_val);
//     // }
//     // else
//     // {
//     //     sleep(3);
//     //     printf("我是父进程,我的进程id是:%d,g_val=%d,&g_val=%p\n", getpid(), g_val, &g_val);
//     // }

//     // printf("hello world");
//     // _exit(-1);

//     pid_t id = fork();
//     if (id < 0)
//     {
//         perror("fork fail");
//         // printf("%s fork error\n", __FUNCTION__);
//         exit(-1);
//     }
//     else if (id == 0)
//     {
//         printf("我是子进程,我的进程id是:%d\n", getpid());
//         sleep(5);
//         exit(10);
//     }
//     else
//     {
//         // int st = 0;
//         // pid_t ret = wait(&st);
//         // if (ret > 0 && (st & 0x7F) == 0) // 正常退出
//         // {
//         //     printf("child exit code:%d\n", (st >> 8));
//         // }
//         // else if (ret > 0)
//         // {
//         //     printf("sig code:%d\n", st & 0x3F);
//         // }

//         int status = 0;
//         pid_t ret = 0;
//         do
//         {
//             /* code */
//             ret = waitpid(-1, &status, WNOHANG);
//             if (ret == 0)
//                 printf("child running...\n");
//             sleep(1);
//         } while (ret == 0);

//         if (WIFEXITED(status) && ret == id)
//             printf("wait child 5s success, child return code is :%d.\n", WEXITSTATUS(status));
//         else
//         {
//             printf("child exit error\n");
//             return -1;
//         }
//     }
//     return 0;
// }

// int main()
// {
//     // std::cout << "test execute exec_1" << std::endl;
//     // if (execl("./exec_1", "", nullptr) == -1)
//     // {
//     //     perror("execl fail");
//     //     exit(-1);
//     // }
//     // std::cout << "exec_1 execute sucess..." << std::endl;

//     std::cout << ('\0' == ' ') << std::endl;
//     return 0;
// }

// execv_2.c
// #include <stdio.h>
// #include <unistd.h>
// int main()
// {
//     char str1[] = "hello";
//     char str2[] = "Good moring";
//     char str3[] = "-l";
//     char *buf[] = {str3, NULL};

//     // char *buf[] = {"Hello", "Good moring", "Bye", NULL};
//     printf("execv_2执行test_2程序:\n");
//     if (execv("ls", buf) == -1)
//         perror("execv error");
//     printf("若exec成功，我不会被执行\n");
//     return 0;
// }

// execlp_1.c
#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("execlp_1执行 ls 指令:\n");
    if (execlp("ls", "", NULL) == -1)
        // 执行shell指令ls
        // 第一个参数应该是PATH中的可执行文件名
        // 不需要单独指明路径
        // 后面的参数与execl相同
        perror("execlp error\n");
    printf("如果exec成功，此句不会执行\n");
    return 0;
}