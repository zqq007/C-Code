#pragma once

#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <cstring>
#include <unistd.h>

static const std::string default_ip = "192.168.211.128";
static const uint16_t default_port = 8082;
static const int default_backlog = 5;

class tcp_server
{
public:
    tcp_server(const std::string &ip = default_ip, const uint16_t &port = default_port) : ip_(ip), port_(port), listensock_(-1)
    {
    }

    void Socket()
    {
        sock_ = socket(AF_INET, SOCK_STREAM, 0);
        if (-1 == sock_)
        {
            perror("create socket fail");
            exit(-1);
        }
    }

    void Bind()
    {
        struct sockaddr_in host;
        memset(&host, 0, sizeof(host));
        host.sin_family = AF_INET;
        inet_pton(AF_INET, ip_.c_str(), &host.sin_addr);
        host.sin_port = htons(port_);
        int res = bind(sock_, (struct sockaddr *)&host, sizeof(host));
        if (-1 == res)
        {
            perror("bind socket fail");
            exit(-1);
        }
    }

    void Listen(int backlog = default_backlog)
    {
        if (-1 == listen(sock_, backlog))
        {
            perror("listen sock fail");
            exit(-1);
        }
    }

    void Accept(struct sockaddr_in *opposite)
    {
        socklen_t len = sizeof(*opposite);
        listensock_ = accept(sock_, (struct sockaddr *)opposite, &len);
        // if (-1 == listensock_)
        // {
        //     perror("accept sock fail");
        // }
    }

    void Init()
    {
        Socket();
        Bind();
        Listen();
    }

    void Run()
    {

        struct sockaddr_in opposite;
        memset(&opposite, 0, sizeof(opposite));
        Accept(&opposite);
        while (true)
        {
            char buf[1024] = {0};

            if (listensock_ != -1)
            {
                int n = read(listensock_, buf, sizeof(buf) - 1);
                if (n > 0)
                {
                    buf[n] = 0;
                    std::cout << "client: " << buf << std::endl;

                    send(listensock_, buf, sizeof(buf), 0);
                }
                else if (n == 0)
                {
                    std::cout << "client quit..." << std::endl;
                    close(listensock_);
                }
                else
                {
                    std::cerr << "read fail" << std::endl;
                    close(listensock_);
                    exit(-1);
                }
            }
        }
    }

    ~tcp_server() { close(sock_); }

private:
    int sock_;
    std::string ip_;
    uint16_t port_;
    int listensock_;
};