#include "udp_server.hpp"
#include <memory>

int main(int argc, char *argv[])
{
    // std::cout << argc << std::endl;
    // for (int i = 0; i < argc; ++i)
    // {
    //     std::cout << argv[i] << " ";
    // }
    // std::cout << std::endl;

    std::unique_ptr<udp_server> server(new udp_server());
    server->Run();

    return 0;
}