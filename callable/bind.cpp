
#include <iostream>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <vector>
#include <initializer_list>
#include <random>
#include <numeric>

int main()
{
    std::vector<int> v1(100);
    std::iota(v1.begin(), v1.end(), 0);
    std::for_each(v1.begin(), v1.end(), [](int &x) -> void
                  { std::cout << x << " "; });
    std::cout << "\n";

    using std::placeholders::_1;
    using std::placeholders::_2;
    auto f = std::bind(std::logical_and<bool>(),
                       std::bind(std::greater_equal<int>(), _1, 25),
                       std::bind(std::less<int>(), _1, 80));
    std::cout << std::count_if(v1.begin(), v1.end(), f);
    std::cout << "\n";
}
