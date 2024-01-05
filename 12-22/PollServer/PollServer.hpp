#pragma once

#include <iostream>
#include <string>
#include <sys/poll.h>
#include "Sock.hpp"
#include "log.hpp"

// #define READ_EVENT (0x1)
// #define WRITER_EVENT (0x1 << 1)
// #define EXCEPT_EVENT (0x1 << 2)

typedef struct pollfd type_t;

const static uint16_t default_port = 8888;
// const static int N = sizeof(fd_set) * 8 * 5; /*4096*/
const static int N = 1024;
const static short defaultevent = 0;

class PollServer
{
    const static int defaultfd = -1;

public:
    PollServer(uint16_t port = default_port) : port_(port), fdarray_(nullptr)
    {
    }

    void InitServer()
    {
        listensock_.Socket();
        listensock_.Bind(port_);
        listensock_.Listen();

        fdarray_ = new type_t[N];

        for (int i = 0; i < N; ++i)
        {
            fdarray_[i].fd = defaultfd;
            fdarray_[i].events = defaultevent;
            fdarray_[i].revents = defaultevent;
        }
    }

    void Accepter()
    {
        // if (FD_ISSET(listensock_.getsock(), &rfds))
        // {
        // std::cout << "有一个新连接到来了" << std::endl;
        std::string clientip;
        uint16_t clientport;
        int sock = listensock_.Accept(&clientip, &clientport);
        if (sock < 0)
            return;
        logMessage(Debug, "%s:%d,sock:%d", clientip.c_str(), clientport, sock);
        int pos = 1;
        for (; pos < N; ++pos)
        {
            if (fdarray_[pos].fd == defaultfd)
                break;
        }
        if (pos >= N) // 这里表示数组已经满了
        {
            close(sock); /*可以使用realooc扩容，由于用户量少并且开辟的空间足够用，这里就不扩容了*/
            logMessage(Warning, "fdarray full");
        }
        else
        {
            fdarray_[pos].fd = sock;
            fdarray_[pos].events = POLLIN;
            fdarray_[pos].revents = defaultevent;
        }
        // }
    }

    void Recver(int index)
    {
        int fd = fdarray_[index].fd;
        char buffer[1024];
        ssize_t n = recv(fd, buffer, sizeof(buffer) - 1, 0);
        if (n > 0)
        {
            // 读取成功
            buffer[n - 1] = 0;
            std::cout << "client: " << buffer << std::endl;

            // 发送
            std::string response = buffer;
            response += "[from selectserver]";
            send(fd, response.c_str(), response.size(), 0);
        }
        else
        {
            if (n == 0)
                logMessage(Info, "client quit...,%d -> %d", fd, defaultfd);
            else
                logMessage(Warning, "recv error,client quit...,%d -> %d", fd, defaultfd);
            close(fdarray_[index].fd);
            fdarray_[index].fd = defaultfd;
            fdarray_[index].events = defaultevent;
        }
    }

    void HandlerEvent()
    {
        for (int i = 0; i < N; ++i)
        {
            int fd = fdarray_[i].fd;
            short revent = fdarray_[i].revents;
            if (fd == defaultfd)
                continue;

            if (revent & POLLIN)
            {
                if (fd == listensock_.getsock())
                {
                    Accepter();
                }
                else
                {
                    Recver(i);
                }
            }
        }
    }

    void Start()
    {
        fdarray_[0].fd = listensock_.getsock();
        fdarray_[0].events = POLLIN;
        // struct timeval timeout = {2, 0};
        // fd_set rfds;
        // FD_ZERO(&rfds);
        // FD_SET(listensock_.getsock(), &rfds);

        while (true)
        {
            int timeout = -1;
            int n = poll(fdarray_, N, timeout);
            switch (n)
            {
            case 0:
                // 表示超时
                logMessage(Debug, "timeout,%d,%s", errno, strerror(errno));
                break;
            case -1:
                logMessage(Warning, "%d,%s", errno, strerror(errno));
                break;
            default:
                logMessage(Debug, "有一个事件就绪了，%d", n);
                HandlerEvent();
                DebugFdarray();
                break;
            }

            sleep(1);
        }
    }

    void DebugFdarray()
    {
        for (int i = 0; i < N; ++i)
        {
            if (fdarray_[i].fd != defaultfd)
                printf("fdarray_[%d]:%d\n", i, fdarray_[i].fd);
        }
    }

    ~PollServer()
    {
        if (fdarray_)
            delete[] fdarray_;
    }

private:
    uint16_t port_;
    Sock listensock_;
    type_t *fdarray_;
};
