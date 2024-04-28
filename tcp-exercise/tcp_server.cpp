#include "tcp_server.hpp"
#include <memory>

int main()
{
    std::unique_ptr<tcp_server> tsr(new tcp_server());
    tsr->Init();
    tsr->Run();
    return 0;
}