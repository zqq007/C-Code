#include "udp_server.hpp"
#include <memory>

int main()
{
    std::unique_ptr<udp_server> usr(new udp_server());
    usr->Run();
    return 0;
}