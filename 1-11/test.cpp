#include <iostream>
#include <string>
#include <memory>

/*饿汉模式，以空间换时间*/
// class Singleton
// {
// public:
//     static Singleton &getton()
//     {
//         return ton_;
//     }

//     int getdata()
//     {
//         return data_;
//     }

// private:
//     static Singleton ton_;
//     Singleton(int data) : data_(data) { std::cout << "调用构造函数" << std::endl; }
//     Singleton(const Singleton &) = delete;
//     Singleton &operator=(const Singleton &ton) = delete;
//     ~Singleton() {}

// private:
//     int data_;
// };

// Singleton Singleton::ton_(123);

/*懒汉模式*/
// class Singleton
// {
// public:
//     static Singleton &getton()
//     {
//         static Singleton ton_(1234);
//         return ton_;
//     }

//     int getdata()
//     {
//         return data_;
//     }

// private:
//     Singleton(int data) : data_(data) { std::cout << "调用构造函数" << std::endl; }
//     Singleton(const Singleton &) = delete;
//     Singleton &operator=(const Singleton &ton) = delete;
//     ~Singleton() {}

// private:
//     int data_;
// };

class Fruit
{
public:
    virtual void name() = 0;
};

class Apple : public Fruit
{
public:
    void name() override
    {
        std::cout << "I'm an apple" << std::endl;
    }
};

class Banana : public Fruit
{
public:
    void name() override
    {
        std::cout << "I'm a Banana" << std::endl;
    }
};

/*简单工厂模式*/
class FruitFactory
{
public:
    static std::shared_ptr<Fruit> create(const std::string &name)
    {
        if (name == "苹果")
        {
            return std::make_shared<Apple>();
        }
        else if (name == "香蕉")
        {
            return std::make_shared<Banana>();
        }
        else
            return nullptr;
    }
};

int main()
{
    // std::cout << Singleton::getton().getdata() << std::endl;

    // std::shared_ptr<FruitFactory> pf(new FruitFactory("苹果"));
    std::shared_ptr<Fruit> pf = FruitFactory::create("苹果");
    pf->name();

    pf = FruitFactory::create("香蕉");
    pf->name();
    return 0;
}