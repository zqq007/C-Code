#include <iostream>
#include <memory>
#include <string>

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

// class FruitFactory
// {
// public:
//     virtual std::shared_ptr<Fruit> create() = 0;
// };

// class AppleFactory : public FruitFactory
// {
// public:
//     std::shared_ptr<Fruit> create() override
//     {
//         return std::make_shared<Apple>();
//     }
// };

// class BananaFactory : public FruitFactory
// {
// public:
//     std::shared_ptr<Fruit> create() override
//     {
//         return std::make_shared<Banana>();
//     }
// };

class Animal
{
public:
    virtual void name() = 0;
};

class Lamp : public Animal
{
public:
    void name() override
    {
        std::cout << "我是一只羊" << std::endl;
    }
};

class Dog : public Animal
{
public:
    void name() override
    {
        std::cout << "我是一只狗" << std::endl;
    }
};

class Factory
{
public:
    virtual std::shared_ptr<Animal> create_animal(const std::string &name) = 0;
    virtual std::shared_ptr<Fruit> create_fruit(const std::string &name) = 0;
};

class FruitFactory : public Factory
{
    std::shared_ptr<Animal> create_animal(const std::string &name) override
    {
        return std::shared_ptr<Animal>();
    }
    std::shared_ptr<Fruit> create_fruit(const std::string &name) override
    {
        if (name == "苹果")
            return std::make_shared<Apple>();
        else if (name == "香蕉")
            return std::make_shared<Banana>();
        else
            return nullptr;
    }
};

class AnimalFactory : public Factory
{
public:
    std::shared_ptr<Fruit> create_fruit(const std::string &name) override
    {
        return std::shared_ptr<Fruit>();
    }
    std::shared_ptr<Animal> create_animal(const std::string &name) override
    {
        if (name == "狗")
            return std::make_shared<Dog>();
        else if (name == "羊")
            return std::make_shared<Lamp>();
        else
            return nullptr;
    }
};

class FactoryProducer
{
public:
    static std::shared_ptr<Factory> create(const std::string &name)
    {
        if (name == "水果")
            return std::make_shared<FruitFactory>();
        else if (name == "动物")
            return std::make_shared<AnimalFactory>();
        else
            return nullptr;
    }
};

int main()
{
    // std::shared_ptr<FruitFactory> factory(new AppleFactory());
    // std::shared_ptr<Fruit> ff = factory->create();
    // ff->name();

    // factory.reset(new BananaFactory());
    // ff = factory->create();
    // ff->name();

    std::shared_ptr<Factory> ff = FactoryProducer::create("水果");
    if (!ff)
        std::cout << "ff is nullptr" << std::endl;

    std::shared_ptr<Fruit> fruit = ff->create_fruit("苹果");
    fruit->name();
    fruit = ff->create_fruit("香蕉");
    fruit->name();

    std::shared_ptr<Factory> ft = FactoryProducer::create("动物");
    std::shared_ptr<Animal> am = ft->create_animal("羊");
    am->name();
    am = ft->create_animal("狗");
    am->name();

    return 0;
}