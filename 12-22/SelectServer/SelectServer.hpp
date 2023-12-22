#pragma once

#include <iostream>
#include <sys/select.h>
#include "Sock.hpp"
#include "log.hpp"

const static uint16_t default_port = 8888;

class SelectServer
{
public:
    SelectServer(uint16_t port = default_port) : port_(port)
    {
    }

    void InitServer()
    {
        listensock_.Socket();
        listensock_.Bind(port_);
        listensock_.Listen();
    }

    void HandlerEvent(fd_set &rfds)
    {
        if(FD_ISSET(listensock_.getsock(),&rfds))
        {
            std::cout << "有一个新连接到来了" << std::endl;
        }
    }

    void Start()
    {
        struct timeval timeout = {2, 0};
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(listensock_.getsock(), &rfds);
        while (true)
        {
            int n = select(listensock_.getsock() + 1, &rfds, nullptr, nullptr, nullptr);
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
                HandlerEvent(rfds);
                break;
            }

            sleep(1);
        }
    }

    ~SelectServer()
    {
    }

private:
    uint16_t port_;
    Sock listensock_;
};