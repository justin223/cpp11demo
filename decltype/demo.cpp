
#include <iostream>
using namespace std;

int func(int a, int b) {
    return a + b;
}

template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u)
{
    return t + u;
}

int main()
{
    struct Foo { int x; };
    const Foo foo = Foo();

    decltype(foo.x) a = 0;
    decltype((foo.x)) b = 0;

    int n = 0, m = 0;
    decltype(n + m) c = 0;
    decltype(n += m) d = c;

    // using func_t = int (*)(int a, int b);

    int arr[2][3] = { 1,2,3,4,5,6 };
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            cout << &arr[i][j] << endl;

    cout << add(1, 2.2f) << endl;
}