#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <unistd.h>

void myPrintError(const std::string &error)
{
    std::cout << error << std::endl;
    exit(-1);
}

int main()
{
    std::string filename = "tp";

    // 创建命名管道
    if (mkfifo(filename.c_str(), 0644) == -1)
    {
        myPrintError("mkfifo tp error");
    }

    // 打开命名管道
    int rdfd = open(filename.c_str(), O_RDONLY);
    if (rdfd == -1)
    {
        /* code */
        myPrintError("open tp error");
    }

    // 循环从命名管道中读取数据
    while (true)
    {
        char buf[1024];
        int n = read(rdfd, buf, sizeof(buf));
        if (n > 0)
        {
            buf[n - 1] = '\0';
            std::cout << "client #" << buf << std::endl;
        }
        else if (n == 0)
        {
            myPrintError("client exit...");
        }
        else
        {
            myPrintError("read error");
        }
    }

    // 关闭文件描述符
    close(rdfd);

    // 删除命名管道
    // unlink(filename.c_str());
    return 0;
}