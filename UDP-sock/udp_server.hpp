#pragma once

#include "udp-socket.hpp"

#define __UDP_SERVER__

class udp_server
{
public:
    udp_server(const uint16_t &port = default_port) : port_(port)
    {
        sock_.Socket();
        sock_.Bind(port_);
    }

    void Run()
    {
        struct sockaddr_in client;
        memset(&client, 0, sizeof(client));
        socklen_t len = sizeof(client);
        while (true)
        {
            // 接收数据
            std::string buf;
            if (sock_.Recvfrom(&client, &buf))
            {
                // 发送数据
                sock_.Sendto(&client, buf);
                // ssize_t res = sendto(sock_.getFd(), buf.c_str(), buf.size(), 0, (struct sockaddr *)&client, sizeof(client));
                // if (res == -1)
                // {
                //     perror("sendto fail");
                // }
            }
        }
    }

    ~udp_server() {}

private:
    udp_socket sock_;
    uint16_t port_;
};