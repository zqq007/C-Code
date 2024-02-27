#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>

void Exit(const std::string &str)
{
    perror(str.c_str());
    exit(errno);
}

int main()
{
    int fd = open("mypipe", O_RDONLY);
    if (fd == -1)
        Exit("open fail");
    while (true)
    {
        int n = 0;
        char buf[1024] = {0};
        n = read(fd, buf, 1024);
        if (n < 0)
        {
            Exit("read fail");
        }
        else if (n == 0)
        {
            std::cout << "client quit..." << std::endl;
            break;
        }
        else
            std::cout << "client# " << buf << std::endl;
    }
    close(fd);
    return 0;
}