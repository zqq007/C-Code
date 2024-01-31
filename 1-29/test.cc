#include <iostream>
#include <sys/poll.h>
#include <unistd.h>
#include <sys/epoll.h>

int main()
{
    struct pollfd poll_fd;
    poll_fd.fd = 0;
    poll_fd.events = POLLIN;

    while (true)
    {
        int ret = poll(&poll_fd, 1, 1000);
        if (ret < 0)
        {
            perror("poll fail");
            continue;
        }
        else if (ret == 0)
        {
            std::cout << "poll timeout\n";
            continue;
        }
        else
        {
            if (poll_fd.revents == POLLIN)
            {
                char buf[1024] = {0};
                int n = read(poll_fd.fd, buf, sizeof(buf) - 1);
                if (n > 0)
                {
                    buf[n] = 0;
                    printf("stdout:%s", buf);
                }
            }
        }
    }
    return 0;
}

