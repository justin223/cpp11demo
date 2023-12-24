
#include <iostream>
#include <string>
#include <functional>
#include <stdexcept>
#include <memory>
#include <map>

#include "noncopyable.h"

const int MAX_OBJ_NUM = 10;

template <typename T>
class ObjectPool : NonCopyable
{
private:
    std::multimap<std::string, std::shared_ptr<T>> object_map;

public:
    template <typename... Args>
    using Constructor = std::function<std::shared_ptr<T>(Args...)>;

    template <typename... Args>
    void Init(size_t num, Args &&...args)
    {
        if (num <= 0 || num > MAX_OBJ_NUM)
            throw std::logic_error("Object num out of range.");

        auto name = typeid(Constructor<Args...>).name();
        for (size_t i = 0; i < num; i++)
        {
            object_map.emplace(name,
                               std::shared_ptr<T>(new T(std::forward<Args>(args)...),
                                                  [this, name](T *p)
                                                  { object_map.emplace(std::move(name), std::shared_ptr<T>(p)); }));
        }
    }

    template <typename... Args>
    std::shared_ptr<T> Get()
    {
        std::string name = typeid(Constructor<Args...>).name();
        auto range = object_map.equal_range(name);
        for (auto it = range.first; it != range.second; ++it)
        {
            auto ptr = it->second;
            object_map.erase(it);
            return ptr;
        }

        return nullptr;
    }
};

struct BigObject
{
    BigObject() {}
    BigObject(int a) {}
    BigObject(const int &a, const int &b) {}

    void Print(const std::string &str)
    {
        std::cout << str << std::endl;
    }
};

void Print(std::shared_ptr<BigObject> p, const std::string &str)
{
    if (p)
        p->Print(str);
}

void test()
{
    ObjectPool<BigObject> pool;
    pool.Init(2);

    {
        auto p = pool.Get();
        Print(p, "p");
        auto p2 = pool.Get();
        Print(p2, "p2");
    }

    auto p = pool.Get();
    auto p2 = pool.Get();
    Print(p, "p");
    Print(p2, "p2");


    pool.Init(2, 1);
    auto p3 = pool.Get<int>();
    Print(p3, "p3");
    pool.Init(2, 1, 3);
    auto p4 = pool.Get<int, int>();
    Print(p4, "p4");
}

int main()
{
    test();

    return 0;
}

