#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    mkfifo("tp", 0644);

    // 打开一个文件
    std::string filename = "abc";
    int infd = open("abc", O_RDONLY);
    if (infd == -1)
    {
        perror("open fail");
        exit(-1);
    }

    // 写文件
    int outfd = open("tp", O_RDWR | O_TRUNC);
    if (outfd == -1)
    {
        perror("open fail");
        exit(-1);
    }

    // 读文件并写到outfd中
    char buf[1024];
    int n = 0;
    while ((n = read(infd, buf, 1024)) > 0)
    {
        write(outfd, buf, n);
        std::cout << "n:" << n << std::endl;
    }

    // Debug
    std::cout << "写入完毕" << std::endl;

    // 关闭文件
    close(infd);
    close(outfd);
    return 0;
}