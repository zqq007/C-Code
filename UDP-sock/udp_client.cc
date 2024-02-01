#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define N 1024

static void usage(std::string process)
{
    std::cout << "Usage:\t" << process << " ip port\n";
}

int main(int argc, char *argv[])
{
    // std::cout << argc << std::endl;
    // for (int i = 0; i < argc; ++i)
    // {
    //     std::cout << argv[i] << " ";
    // }
    // std::cout << std::endl;

    if (argc != 3)
    {
        usage(argv[0]);
    }

    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip.c_str());
    server.sin_port = htons(port);

    while (true)
    {
        std::cout << "please enter your message:";
        std::string message;
        getline(std::cin, message);

        sendto(sock, message.c_str(), message.size(), 0, (struct sockaddr *)&server, sizeof(server));

        char buf[N] = {0};
        struct sockaddr_in opposite;
        socklen_t len = sizeof(opposite);
        int n = recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&opposite, &len);
        if (n > 0)
        {
            buf[n] = 0;
            std::cout << "server#" << buf << std::endl;
        }
    }
    return 0;
}