#include <iostream>
#include <signal.h>

void handler(int sig)
{
    std::cerr << "catch a sig:" << sig << std::endl;
}

int main()
{
    signal(2, handler);
    while (true)
        ;
    return 0;
}