#pragma once

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define N 1024

const static int default_fd = -1;
const static uint16_t default_port = 8085;

class udp_socket
{
public:
    udp_socket(int fd = default_fd) : fd_(fd) {}

    void Socket()
    {
        fd_ = socket(AF_INET, SOCK_DGRAM, 0);
        if (fd_ == -1)
        {
            perror("socket create fail");
            exit(-1);
        }
    }

    void Bind(const uint16_t &port)
    {
        struct sockaddr_in host;
        memset(&host, 0, sizeof(host));
        host.sin_family = AF_INET;
#ifdef __UDP_SERVER__
        host.sin_addr.s_addr = INADDR_ANY;
// #elif __UDP_CLIENT__
//         host.sin_addr.s_addr = inet_addr(ip.c_str());
#endif
        host.sin_port = htons(port);

        int res = bind(fd_, (struct sockaddr *)&host, sizeof(host));
        if (res == -1)
        {
            perror("bind fail");
            exit(-1);
        }
    }

    // void Recvfrom(std::string *str, std::string *ip, uint16_t *port)
    bool Recvfrom(struct sockaddr_in *host, std::string *str)
    {
        char buf[N] = {0};
        socklen_t len = sizeof(*host);
        ssize_t res = recvfrom(fd_, buf, sizeof(buf) - 1, 0, (struct sockaddr *)host, &len);
        if (res > 0)
        {
            buf[res] = 0;
            std::cout << "client# " << buf << std::endl;
            *str = buf;
            return true;
        }
        else if (res == 0)
        {
            std::cout << "client quit..." << std::endl;
        }
        else
        {
            std::cout << "recvfrom fail" << std::endl;
        }
        return false;
    }

    void Sendto(struct sockaddr_in *host, const std::string &buf)
    {
        ssize_t res = sendto(fd_, buf.c_str(), buf.size(), 0, (struct sockaddr *)host, sizeof(*host));
        if (res == -1)
        {
            perror("sendto fail");
        }
    }

    int getFd()
    {
        return fd_;
    }

    ~udp_socket()
    {
        if (fd_ != -1)
            close(fd_);
    }

private:
    int fd_;
};