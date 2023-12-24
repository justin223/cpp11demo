
#include <iostream>

void func(int x) {
    std::cout << x << std::endl;
}

int main()
{
    void (*foo)(int);
    foo = func; // or foo = &func;

    foo(2);
    (*foo)(2);

    return 0;
}