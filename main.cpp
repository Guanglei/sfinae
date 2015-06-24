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
    
    template<typename T>
    void invoke_foo(T& t, int i)
    {
        invoke_foo_util<T>(t, i, 0);
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

    return 0;
}   
