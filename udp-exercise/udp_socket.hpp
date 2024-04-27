#pragma once

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

class udp_socket
{

public:
    udp_socket() : _fd(-1) {}

    void Socket()
    {
        _fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_fd == -1)
        {
            std::cerr << "create socket fail" << std::endl;
            exit(-1);
        }
    }

    void Bind(const std::string &ip, const uint16_t &port)
    {
        struct sockaddr_in addr;
        // 先清零
        memset(&addr, 0, sizeof(addr));

        // addr.sin_addr.s_addr = INADDR_ANY;
        inet_aton(ip.c_str(), &addr.sin_addr);
        addr.sin_port = htons(port);
        addr.sin_family = AF_INET;

        int n = bind(_fd, (struct sockaddr *)&addr, sizeof(addr));
        if (n == -1)
        {
            std::cerr << "bind socket fail" << std::endl;
            exit(-1);
        }
    }

    void Recvfrom(struct sockaddr_in *host, std::string *message)
    {
        char buf[1024] = {0};
        socklen_t len = sizeof(*host);
        int n = recvfrom(_fd, buf, sizeof(buf) - 1, 0, (struct sockaddr *)host, &len);
        if (n > 0)
        {
            buf[n] = 0;
            *message = buf;
        }
    }

    void Sendto(struct sockaddr_in *host, const std::string &message)
    {
        socklen_t len = sizeof(*host);
        int n = sendto(_fd, message.c_str(), message.size(), 0, (struct sockaddr *)host, len);
        if (n == -1)
        {
            std::cerr << "sendto fail" << std::endl;
            // exit(-1);
        }
    }

    ~udp_socket() { close(_fd); }

private:
    int _fd; // 文件描述符
};