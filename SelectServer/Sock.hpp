#pragma once

#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include "log.hpp"
#include "err.hpp"

const int defaultsock = -1;
const int gbacklog = 32;

class Sock
{
public:
    Sock() : _listensock(defaultsock)
    {
    }

    void Socket()
    {
        _listensock = socket(AF_INET, SOCK_STREAM, 0);
        if (_listensock < 0)
        {
            logMessage(Fatal, "create sock error:%s", strerror(errno));
            exit(SOCK_ERR);
        }
        int opt = 1;
        setsockopt(_listensock,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt));
    }

    void Bind(uint16_t &port)
    {
        struct sockaddr_in local;
        memset(&local, 0, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_addr.s_addr = INADDR_ANY;
        local.sin_port = htons(port);

        if (bind(_listensock, (struct sockaddr *)&local, sizeof(local)) < 0)
        {
            logMessage(Fatal, "bind sock error:%s", strerror(errno));
            exit(BIND_ERR);
        }
    }
    void Listen()
    {
        if (listen(_listensock, gbacklog) < 0)
        {
            logMessage(Fatal, "listen sock error:%s", strerror(errno));
            exit(LISTEN_ERR);
        }
    }

    int Accept(std::string *ip, uint16_t *port)
    {
        struct sockaddr_in temp;
        socklen_t sz = sizeof(temp);

        int sock = accept(_listensock, (struct sockaddr *)&temp, &sz);
        if (sock < 0)
        {
            logMessage(Warning, "accept error:%s", strerror(errno));
        }
        else
        {
            *ip = inet_ntoa(temp.sin_addr);
            *port = ntohs(temp.sin_port);
        }
        return sock;
    }

    int Connect(const std::string &ip, const uint16_t &port)
    {
        struct sockaddr_in server;
        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(ip.c_str());
        server.sin_port = htons(port);

        return connect(_listensock, (struct sockaddr *)&server, sizeof(server));
    }

    int getsock()
    {
        return _listensock;
    }

    ~Sock()
    {
        if (_listensock != defaultsock)
            close(_listensock);
    }

private:
    int _listensock;
};
