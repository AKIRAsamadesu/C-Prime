#include <iostream>
using namespace std;
void Demo1();
void Demo2();
void Demo3();
void Demo4();

void fr_func();
class eg_class3; //如果这里没有eg_class5中就会报错，因为eg_class5中要用到eg_class3

class eg_class1
{
public:
    static void func()
    {
        // int func_param=abc;//静态成员函数只能访问静态成员变量
        int func_param = st_param + 1;
        st_param++;
        cout << func_param << endl;
        cout << "func output" << endl;
    }
    int abc = 0;
    static int st_param; //静态成员变量只能放在定义在全局作用域下的类中
};
int eg_class1::st_param = 0; //初始化静态成员变量也在全局作用域下，不能在类中初始化！！！

class eg_class2
{
public:
    int param1 = 100;
    eg_class2(int param1)
    {
        this->param1 = param1 + 2;
    }
    eg_class2 &func1(int param1) //如果是返回引用的话用的一直都是同一个对象，如果是值的话在链式编程中每一次返回的都是一个新的对象
    {
        this->param1 = param1; //这里要注意用->而不是.来引用变量
        return *this;
    }
};

class eg_class5
{
public:
    void func1(eg_class3 *obj); //注意！！！！！！成员函数作为友元时，访问私有参数的类必须定义在被访问类之前
    void func2(eg_class3 *obj);
};

class eg_class3
{
    friend void fr_func(eg_class3 *obj);          //函数作友元
    friend class eg_class4;                       //类作友元
    friend void eg_class5::func1(eg_class3 *obj); //类中的方法作为友元
private:
    string param1;

public:
    string param2;
    eg_class3(string a, string b)
    {
        this->param1 = a;
        this->param2 = b;
    }
    void external_func();
};

class eg_class4
{
public:
    eg_class4(eg_class3 *obj)
    {
        cout << "class eg4 is visiting:" << obj->param1 << endl;
    }
    ~eg_class4()
    {
        cout << "deleting eg_class4 obj!" << endl;
    }
};

void eg_class5::func1(eg_class3 *obj) //注意！！！！！！成员函数作友元时成员函数必须定义在类的外面
{
    cout << "eg_class5 func1 is visiting:" << obj->param1 << endl;
}

void eg_class5::func2(eg_class3 *obj) //类中有一个成员函数在类外定义，则所有的都要在类外定义
{
    cout << "func2 is visiting:" << obj->param2 << endl;
}

class eg_class6
{

public:
    int param1;
    int *param2;
    eg_class6(int a)
    {
        this->param1 = a;
        this->param2 = new int(a);
    }
    int operator+(eg_class6 obj2)
    {
        int sum = obj2.param1 + this->param1;
        return sum;
    }
    eg_class6& operator++()
    {
        this->param1 = this->param1 + 1;
        return *this;
    }
    eg_class6 operator++(int)
    {
        eg_class6 temp=*this;
        this->param1=this->param1+1;
        return temp;
    }
    eg_class6& operator= (const eg_class6 &obj)
    {
        this->param2=new int(*(obj.param2));
        cout<<"deep copy value:"<<*this->param2<<endl;
        cout<<"origin value:"<<*(obj.param2)<<endl;
        cout<<"deep copy addr:"<<this->param2<<endl;
        cout<<"origin addr:"<<obj.param2<<endl;
        return *this;
    }
    bool operator== (const eg_class6 &obj)
    {
        if(obj.param1==this->param1 && obj.param2==this->param2)
            return 1;
        else
            cout<<"not eq!"<<endl;
        return 0;
    }
    void operator()(int a, int b)
    {
        cout<<"call reload!"<<endl;
        cout<<"param1 is:"<<this->param1<<endl;
        cout<<"inputs are"<<a<<"and"<<b<<endl;
    }
    ~eg_class6()
    {
        delete param2;
        cout<<"eg_class6 deconstructor:"<<this->param1<<endl;
    }
};

ostream &operator<<(ostream &cout, eg_class6 &param)
{
    cout << "reload <<:" << param.param1 << endl;
    return cout;
}

int main(void)
{
    Demo1();
    Demo2();
    Demo3();
    Demo4();

    return 0;
}

void Demo1()
{
    /* 静态成员变量和静态成员函数 */
    cout << "++++++static member variable and function++++++" << endl;
    eg_class1 obj;
    obj.func();        //通过对象访问
    eg_class1::func(); //通过类访问（这两个访问的都是同一个函数）
    cout << eg_class1::st_param << endl;
    obj.st_param = 20;
    cout << eg_class1::st_param << endl;
    cout << endl;
}
void Demo2()
{
    /* this指针的用处 */
    cout << "++++++this pointer++++++" << endl;
    eg_class2 obj(123);
    cout << obj.param1 << endl;
    eg_class2 obj2 = obj.func1(0).func1(100).func1(54); //链式编程，func1中返回了*this即对象本身
    cout << obj2.param1 << endl;
    cout << endl;
}
void Demo3()
{
    /* 友元 */
    cout << "++++++friend element++++++" << endl;
    eg_class3 obj("argument 1", "argument 2");
    eg_class3 *ptr = &obj;    //指针
    eg_class3 &ref_ptr = obj; //引用
    eg_class4 *obj2 = new eg_class4(ptr);
    fr_func(ptr);
    eg_class5 obj3;
    obj3.func1(&obj);
    ptr->external_func();
    cout << ptr << endl;
    cout << &ptr << endl;
    cout << &obj << endl;
    ref_ptr.external_func();
    delete obj2;

    
    cout << endl;
}
void Demo4()
{
    /* 运算符重载 */
    cout << "++++++calculator reload++++++" << endl;
    eg_class6 obj1(2);
    eg_class6 obj2(3);
    cout << obj1 + obj2 << endl;//这里出现deconstructor说明创建了一个临时对象用于存储结果
    cout << obj1 << obj2;
    cout << ++(++(++obj1));
    cout << (obj1++).param1 << endl;
    cout<<obj1.param1<<endl;

    eg_class6 obj3(20);
    eg_class6 cp_obj3(10);
    eg_class6 cpcp_obj3(5);
    cpcp_obj3=cp_obj3=obj3;//这样才是调用重载的=,在初始化时候的=是原先的版本
    cout <<"obj3 addr:"<<obj3.param2<<endl;    
    cout <<"cp_obj3 addr:"<<cp_obj3.param2<<endl;
    cout <<"cpcp_obj3 addr:"<<cpcp_obj3.param2<<endl;
    cout <<"cp_obj3 point to:"<<*(cp_obj3.param2)<<endl;   
    cout <<"cpcp_obj3 point to:"<<*(cpcp_obj3.param2)<<endl;   

    if (obj3==cp_obj3)
    {
        cout<<"obj3==cpo_bj3"<<endl;
    }
    else
    {
        cout<<"something not eq!"<<endl;
    }

    if (obj3==obj3)
    {
        cout<<"obj3==cpo_bj3"<<endl;
    }
    else
    {
        cout<<"something not eq!"<<endl;
    }
    obj3(12,22);
}

void fr_func(eg_class3 *obj)
{
    cout << "friend function is visiting:" << obj->param1 << endl;
}

void eg_class3::external_func() //类外写成员函数
{
    cout << "this is an external func in eg_example3." << endl;
}