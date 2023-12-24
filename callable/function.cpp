
#include <iostream>
#include <functional>

void func(void)
{
    std::cout << __FUNCTION__ << std::endl;
}

class Foo
{
public:
    static int foo_func(int a)
    {
        std::cout << __FUNCTION__ << "(" << a << ") ->: ";
        return a;
    }
};

class Bar
{
public:
    int operator()(int a)
    {
        std::cout << __FUNCTION__ << "(" << a << ") ->: ";
        return a;
    }
};

void call_when_even(int x, const std::function<void(int)> &f)
{
    if (!(x & 1))
        f(x);
}

void output(int x)
{
    std::cout << x << " ";
}

int main()
{
    std::function<void(void)> fr1 = func;
    fr1();

    std::function<int(int)> fr2 = Foo::foo_func;
    std::cout << fr2(123) << std::endl;

    Bar bar;
    fr2 = bar;
    std::cout << fr2(123) << std::endl;

    for (int i = 0; i < 10; ++i)
        call_when_even(i, output);
    std::cout << std::endl;

    return 0;
}
