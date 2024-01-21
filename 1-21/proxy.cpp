#include <iostream>
#include <string>

/*代理模式*/
class IrentHouse
{
public:
    virtual void renthouse() = 0;
};

class Landlord : public IrentHouse
{
public:
    void renthouse() override
    {
        std::cout << "将房子租出去\n";
    }
};

class Intermediary : public Landlord
{
public:
    void renthouse()
    {
        std::cout << "发布招租启示\n";
        std::cout << "带人看房\n";
        _landlord.renthouse();
        std::cout << "负责租后维修\n";
    }

private:
    Landlord _landlord;
};

int main()
{
    Intermediary intermediary;
    intermediary.renthouse();
    return 0;
}