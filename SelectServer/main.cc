#include <memory>
#include "SelectServer.hpp"

int main()
{
    std::unique_ptr<SelectServer> svr(new SelectServer());
    svr->InitServer();
    svr->Start();
    return 0;
}