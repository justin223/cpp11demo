
#include <iostream>
#include <string>
#include <mutex>
#include <stdexcept>

template <typename T>
class Singleton
{
private:
    static T *m_pInstance;

public:
    Singleton() = delete;
    virtual ~Singleton() = delete;
    Singleton &operator=(const Singleton &) = delete;
    Singleton &operator=(Singleton &&) = delete;

    template <typename... Args>
    static T *Instance(Args &&...args)
    {
        if (m_pInstance == nullptr)
        {
            std::mutex mtx;
            std::lock_guard<std::mutex> lock(mtx);
            if (m_pInstance == nullptr)
                m_pInstance = new T(std::forward<Args>(args)...);
        }

        return m_pInstance;
    }

    static T *getInstance()
    {
        if (m_pInstance == nullptr)
            throw std::logic_error("Please initialize the instance first.");

        return m_pInstance;
    }

    static void destroyInstance()
    {
        if (m_pInstance)
            delete m_pInstance;
        m_pInstance = nullptr;
    }
};

template <typename T>
T *Singleton<T>::m_pInstance = nullptr;

struct A
{
    A(const std::string &) { std::cout << "lvalue in A" << std::endl; }
    A(std::string &&) { std::cout << "rvalue in A" << std::endl; }
};

struct B
{
    B(const std::string &) { std::cout << "lvalue in B" << std::endl; }
    B(std::string &&) { std::cout << "rvalue in B" << std::endl; }
};

struct C
{
    C(int x, int y) {}
    void Func() { std::cout << __FUNCTION__ << std::endl; }
};

int main()
{
    std::string s = "xx";
    Singleton<A>::Instance(s);
    Singleton<B>::Instance(std::move(s));
    Singleton<C>::Instance(1, 2);
    Singleton<C>::getInstance()->Func();

    Singleton<A>::destroyInstance();
    Singleton<B>::destroyInstance();
    Singleton<C>::destroyInstance();

    return 0;
}

/**
lvalue in A
rvalue in B
Func
*/
