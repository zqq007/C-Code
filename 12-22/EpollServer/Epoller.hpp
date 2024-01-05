#pragma once

#include <iostream>
#include <sys/epoll.h>
#include <stdlib.h>
#include <cstring>
#include "log.hpp"
#include "err.hpp"

const static int defaultepfd = -1;
const static int gsize = 128;

class Epoller
{
public:
    Epoller(int epfd = defaultepfd) : epfd_(epfd) {}

    void Create()
    {
        epfd_ = epoll_create(gsize);
        if (epfd_ == -1)
        {
            logMessage(Fatal, "create epoll err,err:%s", strerror(errno));
            exit(CREATE_EPOLL_ERR);
        }
    }

    bool AddModEvent(int fd, uint32_t event,int op)
    {
        struct epoll_event ep;
        ep.events = event;
        ep.data.fd = fd;
        int res = epoll_ctl(epfd_, op, fd, &ep);
        if (res == -1)
            logMessage(Warning, "epoll_ctl error,err:%s", strerror(errno));
        return res == -1 ? false : true;
    }

    bool DelEvent(int fd)
    {
        return epoll_ctl(epfd_, EPOLL_CTL_DEL, fd, nullptr) == 0;
    }

    int Wait(struct epoll_event *events, int num, int timeout)
    {
        return epoll_wait(epfd_, events, num, timeout);
    }

    ~Epoller()
    {
        if (epfd_ != defaultepfd)
            close(epfd_);
    }

private:
    int epfd_;
};