#include <vector>
#include <iostream>

struct InvokeUtil
{
    template<typename U, void (U::*)(int)>
    struct invoke_foo_checker;

    template<typename U>
    void invoke_foo_util(U& u, int i, invoke_foo_checker<U, &U::foo>*)
    {
        u.foo(i);
    }

    template<typename U>
    void invoke_foo_util(...)
    {
    }

    template<typename U>
    bool has_foo_util(U& u, invoke_foo_checker<U, &U::foo>*)
    {
        return true;
    }

    template<typename U>
    bool has_foo_util(...)
    {
        return false;
    }

    template<typename T>
    void invoke_foo(T& t, int i)
    {
        invoke_foo_util<T>(t, i, 0);
    }

    template<typename T>
    bool has_foo(T& t)
    {
        return has_foo_util<T>(t, 0);
    }
    
};
 
struct Foo1
{
    void foo(int i)
    {
        std::cout << "Foo1::foo " << i << std::endl;
    }
};  

struct Foo2
{
}; 

int main() 
{
    Foo1 f1;
    Foo2 f2;
    InvokeUtil iu;
    
    iu.invoke_foo(f1, 42);
    iu.invoke_foo(f2, 42);
    
    if(iu.has_foo(f1))
    {
        std::cout << "Foo1 has foo" << std::endl;
    }
    
    if(iu.has_foo(f2))
    {
        std::cout << "Foo2 has foo" << std::endl;
    }

    return 0;
}   
