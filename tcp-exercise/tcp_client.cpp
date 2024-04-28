#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <cstring>
#include <unistd.h>

void argumentError()
{
    std::cout << "It take two parameters,first is ip,secound is port" << std::endl;
    exit(-1);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        argumentError();

    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock)
    {
        perror("create sock fail");
        exit(-1);
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    inet_pton(AF_INET, ip.c_str(), &server.sin_addr);
    server.sin_port = htons(port);
    connect(sock, (struct sockaddr *)&server, sizeof(server));

    while (true)
    {
        std::string message;
        std::cout << "please enter your message: ";
        getline(std::cin, message);

        int n = write(sock, message.c_str(), message.size());
        if (n < 0)
        {
            perror("write fail");
            exit(-1);
        }
        std::cout << "n:" << n << std::endl;

        // send
        char buf[1024] = {0};
        int len = read(sock, buf, n);
        if (len > 0)
        {
            buf[len] = 0;
            std::cout << "server: " << buf << std::endl;
        }
    }

    close(sock);
    return 0;
}