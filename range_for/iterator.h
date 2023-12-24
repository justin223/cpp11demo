
#include <cstddef>

namespace justin
{
    template <typename T>
    class iterator
    {
    public:
        using value_type = T;
        using size_type = std::size_t;

        iterator(size_type cur_start, value_type begin_val, value_type step_val)
            : _cursor(cur_start),
              _step(step_val),
              _value(begin_val)
        {
            _value += (_step * _cursor);
        }

        value_type operator*() const { return _value; }

        bool operator!=(const iterator &rhs) const
        {
            return (_cursor != rhs._cursor);
        }

        iterator &operator++() // prefix
        {
            _value += _step;
            ++_cursor;
            return (*this);
        }

    private:
        size_type _cursor;
        const value_type _step;
        value_type _value;
    };
}
