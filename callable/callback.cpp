
#include <iostream>
#include <functional>

class A
{
    std::function<void()> _callback;

public:
    A(const std::function<void()> &f) : _callback(f) {}

    void notify()
    {
        _callback();
    }
};

class Foo
{
public:
    void operator()()
    {
        std::cout << __FUNCTION__ << std::endl;
    }
};

int main()
{
    Foo foo;
    A aa(foo);
    aa.notify();

    return 0;
}
