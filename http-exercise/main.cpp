#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define BACKLOG 5

void argumentError()
{
    std::cerr << "Have two argument,first is ip,second is port" << std::endl;
    exit(-1);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        argumentError();

    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    struct sockaddr_in host;
    memset(&host, 0, sizeof(host));
    host.sin_family = AF_INET;
    inet_pton(AF_INET, ip.c_str(), &host.sin_addr);
    host.sin_port = htons(port);

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        std::cerr << "create socket fail" << std::endl;
        exit(-1);
    }

    if (bind(fd, (struct sockaddr *)&host, sizeof(host)) < 0)
    {
        std::cerr << "bind socket fail" << std::endl;
        exit(-1);
    }

    if (listen(fd, BACKLOG) == -1)
    {
        std::cerr << "listen socket fail" << std::endl;
        exit(-1);
    }

    while (true)
    {
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        int client_fd = accept(fd, (struct sockaddr *)&client, &client_len);
        if (client_fd < 0)
            continue;

        char buf[1024] = {0};
        ssize_t n = read(client_fd, buf, sizeof(buf) - 1);
        if (n < 0)
        {
            perror("read fail");
            continue;
        }
        buf[n] = 0;
        std::cout << buf << std::endl;

        const std::string response = "Hello World";
        sprintf(buf, "HTTP/1.0 404 ok\nContent-Length:%lu\n\n%s", response.size(), response.c_str());
        write(client_fd, buf, strlen(buf));
    }
    return 0;
}