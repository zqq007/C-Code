#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void commandError()
{
    std::cout << "Has two argument,first is ip,second is port" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        commandError();
        exit(-1);
    }

    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        std::cerr << "create socket fail" << std::endl;
        exit(-1);
    }

    struct sockaddr_in host;
    memset(&host, 0, sizeof(host));
    host.sin_addr.s_addr = inet_addr(ip.c_str());
    host.sin_family = AF_INET;
    host.sin_port = htons(port);
    socklen_t len = sizeof(host);

    // 开始执行主要逻辑
    while (true)
    {
        std::string message;
        std::cout << "please enter your message: ";
        getline(std::cin, message);

        // 发送
        int send_len = sendto(fd, message.c_str(), message.size(), 0, (struct sockaddr *)&host, sizeof(host));
        if (send_len < 0)
        {
            std::cerr << "sendto fail" << std::endl;
            exit(-1);
        }

        // 接收
        struct sockaddr_in opposite;
        memset(&opposite, 0, sizeof(opposite));
        socklen_t sz = sizeof(opposite);
        char response[1024] = {0};
        int receive_len = recvfrom(fd, response, sizeof(response) - 1, 0, (struct sockaddr *)&opposite, &sz);
        if (receive_len > 0)
        {
            response[receive_len] = 0;
            std::cout << "server: " << response << std::endl;
        }
    }

    // std::cout << "ip:" << ip << " port: " << port << std::endl;
}