#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <sys/poll.h>
#include "Sock.hpp"
#include "Log.hpp"

const static int gport = 8888;
const static int N = 4096;
const static short defaultevent = 0;
typedef struct pollfd type_t;

class PollServer
{

public:
    PollServer(uint16_t port = gport) : port_(port), fdarray_(nullptr)
    {
    }
    void InitServer()
    {
        listensock_.Socket();
        listensock_.Bind(port_);
        listensock_.Listen();
        fdarray_ = new type_t[N]; 
        for (int i = 0; i < N; i++)
        {
            fdarray_[i].fd = defaultfd;
            fdarray_[i].events = defaultevent;
            fdarray_[i].revents = defaultevent;
        }
    }
    void Accepter()
    {
        // std::cout << "有一个新连接到来了" << std::endl;
        // Accept, 这里在进行Accept会不会被阻塞？？不会的！
        std::string clientip;
        uint16_t clientport;
        int sock = listensock_.Accept(&clientip, &clientport);
        if (sock < 0)
            return;
        // 得到了对应的sock, 我们可不可以进行read/recv，读取sock？不能
        // 你怎么知道sock上有数据就绪了？不知道，所以我们需要将sock交给select，让select进行管理！
        logMessage(Debug, "[%s:%d], sock: %d", clientip.c_str(), clientport, sock);
        // 要让select 帮我们进行关心，只要把sock添加到fdarray_[]里面即可！
        int pos = 1;
        for (; pos < N; pos++)
        {
            if (fdarray_[pos].fd == defaultfd)
                break;
        }
        if (pos >= N)
        {
            close(sock); // poll -> 动态扩容，扩容失败
            logMessage(Warning, "sockfd array[] full");
        }
        else
        {
            fdarray_[pos].fd = sock;
            fdarray_[pos].events = POLLIN; // (POLLIN|POLLOUT)
            fdarray_[pos].revents = defaultevent;
        }
    }
    // echo server
    void HandlerEvent()
    {
        for (int i = 0; i < N; i++)
        {
            int fd = fdarray_[i].fd;
            short revent = fdarray_[i].revents;

            if (fd == defaultfd)
                continue;

            if ((fd == listensock_.Fd()) && (revent & POLLIN))
            {
                Accepter();
            }
            else if ((fd != listensock_.Fd()) && (revent & POLLIN))
            {
                // ServiceIO();
                // BUG
                char buffer[1024];
                ssize_t s = recv(fd, buffer, sizeof(buffer) - 1, 0); // 读取会被阻塞吗？不会
                if (s > 0)
                {
                    buffer[s-1] = 0;
                    std::cout << "client# " << buffer << std::endl;
                    // fdarray_[i].events |= POLLOUT;

                    // 发送回去也要被select管理的,TODO
                    std::string echo = buffer;
                    echo += " [select server echo]";
                    send(fd, echo.c_str(), echo.size(), 0);
                }
                else
                {
                    if (s == 0)
                        logMessage(Info, "client quit ..., fdarray_[i] -> defaultfd: %d->%d", fd, defaultfd);
                    else
                        logMessage(Warning, "recv error, client quit ..., fdarray_[i] -> defaultfd: %d->%d", fd, defaultfd);
                    close(fd);
                    fdarray_[i].fd = defaultfd;
                    fdarray_[i].events = defaultevent;
                    fdarray_[i].revents = defaultevent;
                }
            }
        }
    }
    void Start()
    {
        // 1. 这里我们能够直接获取新的链接吗？
        // 2. 最开始的时候，我们的服务器是没有太多的sock的，甚至只有一个sock！listensock
        // 3. 在网络中， 新连接到来被当做 读事件就绪！
        // listensock_.Accept(); 不能！
        // demo1
        fdarray_[0].fd = listensock_.Fd();
        fdarray_[0].events = POLLIN;
        while (true)
        {
            int timeout = -1;
            int n = poll(fdarray_, N, timeout); // fdarray_内容管理，合法fd，event全部放入到fdarray_最左侧
            switch (n)
            {
            case 0:
                logMessage(Debug, "timeout, %d: %s", errno, strerror(errno));
                break;
            case -1:
                logMessage(Warning, "%d: %s", errno, strerror(errno));
                break;
            default:
                // 成功了
                logMessage(Debug, "有一个就绪事件发生了: %d", n);
                HandlerEvent();
                DebugPrint();
                break;
            }

            // sleep(1);
        }
    }
    void DebugPrint()
    {
        std::cout << "fdarray[]: ";
        for (int i = 0; i < N; i++)
        {
            if (fdarray_[i].fd == defaultfd)
                continue;
            std::cout << fdarray_[i].fd << " ";
        }
        std::cout << "\n";
    }
    ~PollServer()
    {
        listensock_.Close();
        if(fdarray_) delete []fdarray_;
    }

private:
    uint16_t port_;
    Sock listensock_;
    type_t *fdarray_; // 管理所有的fd
};