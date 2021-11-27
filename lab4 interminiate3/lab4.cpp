#include <iostream>
using namespace std;

void Demo1();
void Demo2();
void Demo3();

class eg_class1;
class eg_class2;

class eg_class1
{
    friend class eg_class2;
    friend class eg_class3;
    friend class eg_class4;

public:
    eg_class1(int a = 0, int b = 1) : i(a), j(b)
    {
        cout << "class1 param:" << a << "and" << b << endl;
    }
    int i, j;
};
class eg_class2 : virtual public eg_class1
{
public:
    eg_class2(int a, int b) : k(a + 5), l(b + 6), eg_class1(a, b)
    {
        cout << "class2 param:" << a << "and" << b << endl;
        cout << "predecessor param:" << eg_class1::i << "and" << eg_class1::j << endl;
    }
    int k, l;
};
class eg_class3 : virtual public eg_class1 //virtual解决构建eg_class4时分别从eg_class2和eg_class3构建两次eg_class1的问题
{
public:
    eg_class3(int a, int b) : eg_class1(a, b)
    {
        cout << "class3 param:" << a << "and" << b << endl;
        cout << "predecessor param:" << eg_class1::i << "and" << eg_class1::j << endl;
    }
};
class eg_class4 : public eg_class2, public eg_class3
{
public:
    eg_class4(int a, int b) : eg_class2(a, b), eg_class3(a + 1, b + 2)
    {
        cout << "class4 param:" << a << "and" << b << endl;
        //问题在这里
        cout << "class2 param i:" << eg_class2::i << endl;
        cout << "class2 param j:" << eg_class2::j << endl;
        cout << "class2 param k:" << eg_class2::k << endl;
        cout << "class2 param l:" << eg_class2::l << endl;
    }
};
class eg_class5
{
    public:
    int param=1;
    virtual void func1(int a) 
    {
        cout<<"this is func1 in eg_class5!"<<endl;
        cout<<"a="<<a<<endl;
    };
    virtual void func3(int a)=0;
};

class eg_class6: public eg_class5
{
    public:
    // void func1()
    // {
    //     cout<<"this is eg_class6 func1!"<<endl;
    // }
    void func2() 
    {
        cout<<"this is eg_class6 func2!"<<endl;
        cout<<"predecessor param is:"<<param<<endl;
    }
    void func3(int a) 
    {
        cout<<"this is eg_class6 func3!"<<endl;
        cout<<"a="<<a<<endl;
    }
};

int main()
{
    Demo1();
    Demo2();
    Demo3();
    return 0;
}

void Demo1()
{
    /* 1. 有参数继承 */
    cout << "+++++++++ Demo1 +++++++++" << endl;
    eg_class2 obj(1, 2); //子类也可以是友元
}
void Demo2()
{
    /* 2. 多继承菱形继承 */
    cout << "+++++++++ Demo2 +++++++++" << endl;
    eg_class4 obj(5, 6);
    cout << "class2 i:" << obj.eg_class2::i << endl; //当父类和父类的父类有相同成员变量时候，父类的变量会覆盖掉父类的父类分变量，即子类没法访问爷类中和父类相同的成员变量
    cout << "class2 j:" << obj.eg_class2::j << endl;
    cout << "class3 i:" << obj.eg_class3::i << endl;
    cout << "class3 j:" << obj.eg_class3::j << endl;
    obj.eg_class3::i = 44;                           
    obj.eg_class2::j = 55;
    cout << "class2 i:" << obj.eg_class2::i << endl;
    cout << "class2 j:" << obj.eg_class2::j << endl;
    cout << "class3 i:" << obj.eg_class3::i << endl;
    cout << "class3 j:" << obj.eg_class3::j << endl;
    //在多带参数的菱形虚继承情况下，base类在最下层的衍生类声明时不会将这个类的值赋过去，而是要在随后的obj.param中指明其值，这是为了防止初始化时的第二层对base的同一个成员同时赋两个不同的值造成冲突
}
void Demo3()
{
    /* 3. 多态 */
    cout << "+++++++++ Demo3 +++++++++" << endl;
    eg_class6 obj;
    obj.func2();
    obj.func1(123);
    obj.func3(423);
}

