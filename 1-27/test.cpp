#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>

void setNoBlock(int fd)
{
    int f1 = fcntl(fd, F_GETFL);
    if (f1 < 0)
    {
        perror("fcntl");
        exit(-1);
    }
    fcntl(fd, F_SETFL, f1 | O_NONBLOCK);
}

// int main()
// {
//     // setNoBlock(0);
//     // while (true)
//     // {
//     //     char buffer[1024] = {0};
//     //     ssize_t read_size = read(0, buffer, sizeof(buffer) - 1);
//     //     if (read_size < 0)
//     //     {
//     //         // perror("read");
//     //         sleep(1);
//     //         continue;
//     //     }
//     //     // std::cout << buffer << std::endl;
//     //     printf("output:%s\n", buffer);
//     // }

//     printf("%ld\n", sizeof(fd_set));
//     return 0;
// }

int main()
{
    // struct timeval *timeout = nullptr;
    fd_set read_fd;
    FD_ZERO(&read_fd);
    FD_SET(0, &read_fd);
    while (true)
    {
        printf(">");
        fflush(stdout);
        int res = select(1, &read_fd, nullptr, nullptr, nullptr); // 设置为阻塞
        if (res < 0)
        {
            perror("select");
            continue;
        }
        if (FD_ISSET(0, &read_fd))
        {
            char buf[1024] = {0};
            int n = read(0, buf, sizeof(buf) - 1);
            buf[n - 1] = 0;
            printf("output:%s\n", buf);
        }
        FD_ZERO(&read_fd);
        FD_SET(0, &read_fd);
    }
    return 0;
}