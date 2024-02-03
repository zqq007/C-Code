#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "I'm exec_2" << std::endl;
    for (int i = 0; i < argc; ++i)
    {
        std::cout << "argv[" << i << "]:" << argv[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}