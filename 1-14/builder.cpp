#include <iostream>
#include <string>
#include <memory>

class Computer
{
public:
    void set_board(const std::string board)
    {
        board_ = board;
    }

    void set_display(const std::string display)
    {
        display_ = display;
    }

    virtual void set_os() = 0;

    void showparmeters()
    {
        std::string para = "Computer Parameters:{\n";
        para += "\tBoard: " + board_ + "\n";
        para += "\tDisplay: " + display_ + "\n";
        para += "\tOs: " + os_ + "\n";
        para += "}\n";

        std::cout << para << std::endl;
    }

protected:
    std::string board_;
    std::string display_;
    std::string os_;
};

class MacBook : public Computer
{
public:
    void set_os() override
    {
        os_ = "MacOS";
    }
};

class Builder
{
public:
    virtual void buildboard(const std::string &board) = 0;
    virtual void builddisplay(const std::string &display) = 0;
    virtual void buildos() = 0;
    virtual std::shared_ptr<Computer> build() = 0;
};

class MacBookBuilder : public Builder
{
public:
    MacBookBuilder() : MacBookBuilder_(new MacBook()) {}
    void buildboard(const std::string &board) override
    {
        MacBookBuilder_->set_board(board);
    }
    void builddisplay(const std::string &display) override
    {
        MacBookBuilder_->set_display(display);
    }
    void buildos() override
    {
        MacBookBuilder_->set_os();
    }

    std::shared_ptr<Computer> build() override
    {
        return MacBookBuilder_;
    }

private:
    std::shared_ptr<Computer> MacBookBuilder_;
};

class Director
{
public:
    Director(Builder *builder) : builder_(builder) {}
    void construct(const std::string &board, const std::string &display)
    {
        builder_->buildboard(board);
        builder_->builddisplay(display);
        builder_->buildos();
    }

private:
    std::shared_ptr<Builder> builder_;
};

int main()
{
    Builder *dir = new MacBookBuilder();
    std::unique_ptr<Director> director(new Director(dir));
    director->construct("华硕主板", "三星显示器");
    std::shared_ptr<Computer> computer = dir->build();

    computer->showparmeters();

    // delete dir;//MacBookBuilder里面的成员是std::shared_ptr，所以不需要自己delete
    return 0;
}