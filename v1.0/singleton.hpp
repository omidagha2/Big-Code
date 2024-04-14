// creates  a static instance of any class 
template <class X>
X& singleton()
{
    static X x;
    return x;
}