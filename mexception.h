#ifndef MEXCEPTION
#define MEXCEPTION
#include <stdexcept>
#include  <exception>

class MyExcept:public std::exception
{
    std::string name;
public:
    MyExcept();
    MyExcept(std::string _name);
    std::string message();
};


MyExcept::MyExcept()
    :name ("no except")
{

}

MyExcept::MyExcept(std::string _name)
    :name(_name)
{

}

std::string MyExcept::message()
{
    return name;
}
#endif // MEXCEPTION

