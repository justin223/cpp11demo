
class A
{
private:
    int m = 0;

public:
    void func(int x, int y)
    {
        // auto x1 = []{return m;};                 // error, not capturing
        auto x2 = [=]{ return m; };                 // capturing all external variables by value
        auto x3 = [&]{ return m++; };               // capturing all external variables by reference
        auto x4 = [this] { return m; };             // capturing [this] pointer
        // auto x5 = [this] { return m + x + y; };     // error, not capturing x and y
        auto x6 = [&, x, y] { return (++m) + x + y; }; // capturing x and y by value, and others by referenece
    }
};
