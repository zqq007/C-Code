#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>

#define FIBER_STACK 8192

// int global_a;
// void *stack;

// int doSomething(void *arg)
// {
//     std::cout << "This is child process,the id is " << getpid() << ",global is " << ++global_a << std::endl;
//     exit(1);
// }

// int main()
// {
//     global_a = 1;
//     stack = malloc(FIBER_STACK);
//     if (!stack)
//     {
//         perror("malloc fail");
//         exit(-1);
//     }

//     clone(&doSomething, (char *)stack + FIBER_STACK, CLONE_VM | CLONE_VFORK, nullptr);

//     std::cout << "This is parent process,the id is " << getpid() << ",global is " << global_a << std::endl;
//     free(stack);
//     stack = nullptr;
//     return 0;
// }

// int main()
// {
//     pid_t pid = fork();
//     if (pid < 0)
//     {
//         perror("fork fail");
//         exit(-1);
//     }
//     else if (pid == 0)
//     {
//         // child process
//         std::cout << "I am child process" << std::endl;
//         sleep(5);
//         exit(0);
//     }
//     // parent process
//     int status = 0;

//     // wait version
//     // wait(&status);
//     // if (WIFEXITED(status))
//     // {
//     //     std::cout << "The process exited normally" << std::endl;
//     // }
//     // else
//     //     std::cout << "The process exited exception" << std::endl;
//     // std::cout << WEXITSTATUS(status) << std::endl;

//     // waitpid version
//     while (waitpid(-1, &status, WNOHANG) == 0)
//     {
//         std::cout << "wait child process exit..." << std::endl;
//         sleep(1);
//     }

//     if (WIFEXITED(status))
//     {
//         std::cout << "The process exited normally" << std::endl;
//     }
//     else
//         std::cout << "The process exited exception" << std::endl;
//     std::cout << WEXITSTATUS(status) << std::endl;

//     return 0;
// }

int main()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork fail");
        exit(-1);
    }
    else if (pid == 0)
    {
        // chile process
        execlp("ls", "ls", "-l", "-a", nullptr);
    }
    // parent process
    else
        wait(nullptr);
    return 0;
}