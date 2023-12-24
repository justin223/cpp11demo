
#include "iterator.h"

#include <stdexcept>
#include <iostream>

namespace justin
{
    template <typename T>
    class range
    {
    public:
        using value_type = T;
        using reference = const value_type &;
        using const_reference = const value_type &;
        using iterator = const justin::iterator<value_type>;
        using const_iterator = const justin::iterator<value_type>;
        using size_type = typename iterator::size_type;

        range(value_type begin_val, value_type end_val, value_type step_val)
            : _begin(begin_val),
              _end(end_val),
              _step(step_val),
              _max_count(get_adjusted_count()) {}

        size_type size() const { return _max_count; }
        const_iterator begin() const
        {
            return {0, _begin, _step};
        }

        const_iterator end() const
        {
            return {_max_count, _begin, _step};
        }

    private:
        const value_type _begin;
        const value_type _end;
        const value_type _step;
        const size_type _max_count;

        size_type get_adjusted_count() const
        {
            if (_step > 0 && _begin >= _end)
                throw std::logic_error("End value must be greater than begin value.");
            else if (_step < 0 && _begin <= _end)
                throw std::logic_error("End value must be less than begin value.");

            size_type x = static_cast<size_type>((_end - _begin) / _step);
            if (_begin + (_step * x) != _end)
                ++x;

            return x;
        }
    };
}

template <typename T>
justin::range<T> range(T end)
{
    return {{}, end, 1};
}

template <typename T>
justin::range<T> range(T begin, T end)
{
    return {begin, end, 1};
}

template <typename T, typename U>
auto range(T begin, T end, U step) -> justin::range<decltype(begin + step)>
{
    using r_t = justin::range<decltype(begin + step)>;
    return r_t(begin, end, step);
}

void test_range()
{
    std::cout << "range(15):";
    for (int i : range(15))
        std::cout << " " << i;
    std::cout << std::endl;

    std::cout << "range(2,6):";
    for (auto i : range(2, 6))
        std::cout << " " << i;
    std::cout << std::endl;

    const int x = 2, y = 6, z = 3;
    std::cout << "range(2,6,3):";
    for (auto i : range(x, y, z))
        std::cout << " " << i;
    std::cout << std::endl;

    std::cout << "range(-2, -6, -3):";
    for (auto i : range(-2, -6, -3))
        std::cout << " " << i;
    std::cout << std::endl;

    std::cout << "range(10.5, 15.5):";
    for (auto i : range(10.5, 15.5))
        std::cout << " " << i;
    std::cout << std::endl;

    std::cout << "range(35, 27, -1):";
    for (auto i : range(35, 27, -1))
        std::cout << " " << i;
    std::cout << std::endl;

    std::cout << "range(2, 8, 0.5):";
    for (auto i : range(2, 8, 0.5))
        std::cout << " " << i;
    std::cout << std::endl;

    std::cout << "range(8, 7, -0.1):";
    for (auto i : range(8, 7, -0.1))
        std::cout << " " << i;
    std::cout << std::endl;

    std::cout << "range('a', 'z'):";
    for (auto i : range('a', 'z'))
        std::cout << " " << i;
    std::cout << std::endl;
}

int main()
{
    test_range();

    return 0;
}

/**
range(15): 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
range(2,6): 2 3 4 5
range(2,6,3): 2 5
range(-2, -6, -3): -2 -5
range(10.5, 15.5): 10.5 11.5 12.5 13.5 14.5
range(35, 27, -1): 35 34 33 32 31 30 29 28
range(2, 8, 0.5): 2 2.5 3 3.5 4 4.5 5 5.5 6 6.5 7 7.5
range(8, 7, -0.1): 8 7.9 7.8 7.7 7.6 7.5 7.4 7.3 7.2 7.1
range('a', 'z'): a b c d e f g h i j k l m n o p q r s t u v w x y
*/