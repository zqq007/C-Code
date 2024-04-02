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

    // 打开命名管道
    int wdfd = open(filename.c_str(), O_WRONLY);
    if (wdfd == -1)
        myPrintError("open tp error");

    // 开始循环写
    while (true)
    {
        std::cout << "please enter your message:";
        fflush(stdout);
        char buf[1024];
        int n = read(0, buf, sizeof(buf));
        if (n > 0)
        {
            write(wdfd, buf, n);
        }
    }
    return 0;
}