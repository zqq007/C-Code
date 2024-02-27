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
    mkfifo("mypipe", 0644);
    int fd = open("mypipe", O_WRONLY | O_TRUNC);
    if (fd == -1)
        Exit("open fail");
    while (true)
    {
        std::string message;
        std::cout << "please enter#";
        fflush(stdout);
        getline(std::cin, message);
        int n = write(fd, message.c_str(), message.size());
        if (n <= 0)
            Exit("write fail");
    }
    close(fd);
    return 0;
}