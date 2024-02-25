#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>

// int execl(const char *path, const char *arg, ...);
// int execlp(const char *file, const char *arg, ...);
// int execle(const char *path, const char *arg, ..., char *const envp[]);
// int execv(const char *path, char *const argv[]);
// int execvp(const char *file, char *const argv[]);

// int main()
// {
//     pid_t id = fork();
//     if (id == 0)
//     {
//         std::cout << "我是子进程，我的进程id是：" << getpid() << std::endl;
//         exit(101);

//         char filepath1[] = "./log1.txt";
//         // char filepath2[] = "./log2.txt";

//         // execlp("md5sum", "md5sum", "./log1.txt", nullptr);
//         // execlp("ls", "ls", "-l", nullptr);
//     }
//     else if (id > 0)
//     {
//         std::cout << "我是父进程，我的进程id是：" << getpid() << std::endl;

//         int status;
//         int ret = waitpid(-1, &status, 0);
//         if (ret == -1)
//             perror("child fail");
//         else
//             std::cout << "child run out" << std::endl;

//         if (WIFEXITED(status) && ret == id)
//             std::cout << "child exit code:" << WEXITSTATUS(status) << std::endl;
//     }
//     else
//         perror("fork fail");
//     return 0;
// }

int main()
{
    const char *str = "hello linux";
    size_t len = strlen(str);

    // close(fileno(stdout));
    // dup2(fd, fileno(stdout));

    // const char *buf = "fd;laihfa";
    // ssize_t n = write(fileno(stdout), buf, strlen(buf));
    // if (n == -1)
    //     perror("write fail");

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork fail");
        exit(-1);
    }
    else if (pid == 0)
    {
        /*child process*/
        int fd = open("file1.txt", O_RDWR);
        if (fd == -1)
            perror("open fail");

        dup2(fd, fileno(stdout));
        ssize_t n = write(fileno(stdout), str, len);
        close(fd);
        // if (n == -1)
        //     perror("write fail");
        exit(n);
    }
    else if (pid > 0)
    {
        /*parent process*/

        int fd = open("./file1.txt", O_RDONLY);

        int status = 0;
        int ret = waitpid(-1, &status, 0);
        if (ret == -1)
            perror("waitpid fail");
        else
            std::cout << "child process run..." << std::endl;

        if (WIFEXITED(status) && ret == pid)
            std::cout << "child exit code:" << WEXITSTATUS(status) << std::endl;

        char buf[64];
        memset(&buf, 0, sizeof(buf));
        read(fd, &buf, status);

        std::cout << buf << std::endl;

        close(fd);

        // debug
        // std::cout << "I'm parent process" << std::endl;
        // wait(NULL);
    }
    return 0;
}