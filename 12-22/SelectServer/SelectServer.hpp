#pragma once

#include <iostream>
#include <string>
#include <sys/select.h>
#include "Sock.hpp"
#include "log.hpp"

#define READ_EVENT (0x1)
#define WRITER_EVENT (0x1 << 1)
#define EXCEPT_EVENT (0x1 << 2)

// typedef int type_t;

const static uint16_t default_port = 8888;
const static int N = sizeof(fd_set) * 8;
const static int defaultevent = 0;

typedef struct FdEvent
{
    int fd;
    uint8_t event;
    std::string clientip;
    uint16_t clientport;
} type_t;

class SelectServer
{
    const static int defaultfd = -1;

public:
    SelectServer(uint16_t port = default_port) : port_(port)
    {
    }

    void InitServer()
    {
        listensock_.Socket();
        listensock_.Bind(port_);
        listensock_.Listen();

        for (int i = 0; i < N; ++i)
        {
            fdarray_[i].fd = defaultfd;
            fdarray_[i].event = READ_EVENT;
            fdarray_[i].clientport = 0;
        }
    }

    void Accepter(fd_set &rfds)
    {
        if (FD_ISSET(listensock_.getsock(), &rfds))
        {
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
                close(sock);
                logMessage(Warning, "fdarray full");
            }
            else
            {
                fdarray_[pos].fd = sock;
                fdarray_[pos].event = READ_EVENT;
                fdarray_[pos].clientip = clientip;
                fdarray_[pos].clientport = clientport;
            }
        }
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
            std::cout << "clientip: " << fdarray_[index].clientip << " : " << buffer << std::endl;

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
            fdarray_[index].event = defaultevent;
            fdarray_[index].clientip.clear();
            fdarray_[index].clientport = 0;
        }
    }

    void HandlerEvent(fd_set &rfds, fd_set &wfds)
    {
        for (int i = 0; i < N; ++i)
        {
            int fd = fdarray_[i].fd;
            if (fd == defaultfd)
                continue;

            if ((fdarray_[i].event & READ_EVENT) && FD_ISSET(fd, &rfds))
            {
                if (fd == listensock_.getsock())
                {
                    Accepter(rfds);
                }
                else if (FD_ISSET(fd, &rfds))
                {
                    Recver(i);
                }
                else
                {
                }
            }
            else if ((fdarray_[i].event & WRITER_EVENT) && FD_ISSET(fd, &wfds))
            {
                /*TODO*/
            }
            else
            {
            }
        }
    }

    void Start()
    {
        fdarray_[0].fd = listensock_.getsock();
        struct timeval timeout = {2, 0};
        // fd_set rfds;
        // FD_ZERO(&rfds);
        // FD_SET(listensock_.getsock(), &rfds);

        while (true)
        {
            fd_set rfds;
            fd_set wfds;
            FD_ZERO(&rfds);
            FD_ZERO(&wfds);
            int maxfd = fdarray_[0].fd;
            for (int i = 0; i < N; ++i)
            {
                if (fdarray_[i].fd == defaultfd)
                    continue;
                if (fdarray_[i].event & READ_EVENT)
                    FD_SET(fdarray_[i].fd, &rfds);
                if (fdarray_[i].event & WRITER_EVENT)
                    FD_SET(fdarray_[i].fd, &wfds);

                maxfd = maxfd > fdarray_[i].fd ? maxfd : fdarray_[i].fd;
            }
            int n = select(maxfd + 1, &rfds, &wfds, nullptr, nullptr);
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
                HandlerEvent(rfds, wfds);
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

    ~SelectServer()
    {
    }

private:
    uint16_t port_;
    Sock listensock_;
    type_t fdarray_[N];
};