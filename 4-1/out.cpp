#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// 从命名管道中读取数据
int main()
{
    // 创建一个文件，从命名管道读出来的数据写到该文件中
    int outfd = open("def", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (outfd == -1)
    {
        perror("open def fail");
        exit(-1);
    }

    // 打开命名管道
    int infd = open("tp", O_RDONLY);
    if (infd == -1)
    {
        perror("open tp fail");
        exit(-1);
    }

    // 从管道中读取数据放到新创建的文件中
    int n = 0;
    char buf[1024];
    while ((n = read(infd, buf, 1024)) > 0)
    {
        write(outfd, buf, n);
    }

    // 关闭文件描述符
    close(infd);
    close(outfd);
    unlink("tp");
    return 0;
}