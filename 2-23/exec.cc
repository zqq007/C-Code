#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <cstring>

// #define N 2

int main(int argc, char *argv[])
{
    // const char *str = "hello";

    // int fd = open("./file1.txt", O_RDWR);
    // // close(fileno(stdout));
    // dup2(fd, fileno(stdout));
    // ssize_t n = write(fileno(stdout), str, strlen(str));
    // close(fd);
    if (argc != 3)
    {
        std::cerr << "参数过少" << std::endl;
        exit(-1);
    }

    const char *str1 = argv[1];
    const char *str2 = argv[2];
    const char *str[] = {str1, str2};
    const char *file_array[] = {"./file1.txt", "./file2.txt"};
    // str1 = strtok(argv[1]," ");
    // std::cout << "*str1:" << str1 << " *str2:" << str2 << std::endl;

    pid_t pid = fork();
    if (pid == -1)
        perror("fork fail");
    else if (pid == 0)
    {
        /*child process*/
        /*创建两个子进程，每个进程算出一个文件的md5的值*/
        // if(fd == -1) perror("open fail");//这里就不判断了
        int cnt = 0;
        while (cnt < argc - 1)
        {
            int fd = open(file_array[cnt], O_CREAT | O_RDWR, 0644);
            pid_t id = fork();
            if (id < 0)
                perror("fork fail");
            else if (id == 0)
            {
                dup2(fd, fileno(stdout));
                close(fd);
                int ret = execlp("md5sum", "md5sum", str[cnt], nullptr);
                if (ret == -1)
                    perror("execlp fail");
            }
            else
            {
                // wait(NULL);
                wait(nullptr);
                cnt++;
                close(fd);
            }
        }
    }
    else
    {
        /*parent process*/
        /*目前只知道用C函数读取一行*/
        int fd1 = open(file_array[0], O_RDONLY);
        int fd2 = open(file_array[1], O_RDONLY);

        char buf1[64] = {0};
        char buf2[64] = {0};

        read(fd1, buf1, 32);
        read(fd2, buf2, 32);
        if (strcmp(buf1, buf2) == 0)
            std::cout << str[0] << "和" << str[1] << "相同" << std::endl;
        else
            std::cout << str[0] << "和" << str[1] << "不相同" << std::endl;
        ftruncate(fd1, 0);
        ftruncate(fd2, 0);
        close(fd1);
        close(fd2);
        int res1 = unlink("./file1.txt");
        int res2 = unlink("./file2.txt");
        if (res1 == -1)
            perror("unlink res1 fail");
        if (res2 == -1)
            perror("unlink res2 fail");
    }
    return 0;
}