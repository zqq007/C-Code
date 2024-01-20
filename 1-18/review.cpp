#include <iostream>
extern "C"//用C的方式对函数重命名
{
    void func1(int a, int b);
    void func2();
}

void func1(int a, int b)
{
    std::cout << "void func(int a,int b)" << std::endl;
}

void func2()
{
    std::cout << "void func()" << std::endl;
}

int main()
{
    func1(1,2);
    return 0;
}