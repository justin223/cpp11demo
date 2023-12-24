
void func(void) {}

struct Foo
{
    void operator()(void) {}
};

struct Bar
{
    using fr_t = void (*)(void);
    static void func(void) {}

    operator fr_t(void)
    {
        return func;
    }
};

struct A
{
    int a_;

    void mem_func(void) {}
};

int main()
{
    void (*func_ptr)(void) = &func; // function pointer
    func_ptr();

    Foo foo; // functor
    foo();

    Bar bar; // class object
    bar();

    void (A::*mem_func_ptr)(void) = &A::mem_func; // pointer to class member function
    int A::*mem_obj_ptr = &A::a_;                 // pointer to class member variable

    A aa;
    (aa.*mem_func_ptr)();
    aa.*mem_obj_ptr = 123;

    return 0;
}
