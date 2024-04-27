#pragma once

#define _NO_ENCAPSULATION_

#ifdef _ENCAPSULATION

#include "udp_socket.hpp"

static const std::string default_ip = "";
static const uint16_t default_port = 8081;

class udp_server
{
public:
    udp_server(const std::string &ip = default_ip, const uint16_t &port = default_port) : _ip(ip), _port(port)
    {
        _socket.Socket();
        _socket.Bind(_ip, _port);
    }

    void start()
    {
        std::string buf;
        struct sockaddr_in host;
        memset(&host, 0, sizeof(host));
        // while (true)
        // {
        //     // 接收数据
        //     _socket.Recvfrom(&buf);

        //     // 发送
        //     struct sockaddr_in opposite;

        //     _socket.Sendto()
        // }
    }

    ~udp_server() {}

private:
    std::string _ip;
    uint16_t _port;
    udp_socket _socket;
};

#endif

#ifdef _NO_ENCAPSULATION_

#include <iostream>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

static const std::string default_ip = "192.168.211.128";
static const uint16_t default_port = 8080;

class udp_server
{
public:
    udp_server(const std::string ip = default_ip, const uint16_t &port = default_port) : _ip(ip), _port(port)
    {
        _fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_fd == -1)
        {
            std::cerr << "create socket fail" << std::endl;
            exit(-1);
        }

        struct sockaddr_in host;
        memset(&host, 0, sizeof(host));
        host.sin_family = AF_INET;
        // host.sin_addr.s_addr = INADDR_ANY;
        inet_aton(_ip.c_str(), &host.sin_addr);
        host.sin_port = htons(_port);

        int n = bind(_fd, (struct sockaddr *)&host, sizeof(host));
        if (n == -1)
        {
            std::cerr << "bind socket fail" << std::endl;
            exit(-1);
        }
    }

    void Recv(struct sockaddr_in *opposite, std::string *message)
    {
        char buf[1024] = {0};
        socklen_t len = sizeof(opposite);
        int n = recvfrom(_fd, buf, sizeof(buf) - 1, 0, (struct sockaddr *)opposite, &len);
        if (n > 0)
        {
            buf[n] = 0;
            *message = buf;
            std::string opposite_ip = inet_ntoa(opposite->sin_addr);
            uint16_t opposite_port = ntohs(opposite->sin_port);
            std::cout << "client ip:" << opposite_ip << " port: " << opposite_port << " : " << buf << std::endl;
        }
    }

    void Sendto(const struct sockaddr_in &opposite, const std::string &message)
    {
        int n = sendto(_fd, message.c_str(), message.size(), 0, (struct sockaddr *)&opposite, sizeof(opposite));
        if (n < 0)
        {
            perror("sendto fail");
        }
        // std::cout << "sendto success" << std::endl;
    }

    void Run()
    {
        std::string message;
        while (true)
        {
            struct sockaddr_in opposite;
            socklen_t len = sizeof(opposite);
            // 接收数据
            Recv(&opposite, &message);

            // std::cout << "message: " << message << " len: " << message.length() << std::endl;

            // 发送
            if (message.size()) // 有数据才发
                Sendto(opposite, message);
        }
    }

    ~udp_server() {}

private:
    int _fd;
    std::string _ip;
    uint16_t _port;
};

#endif