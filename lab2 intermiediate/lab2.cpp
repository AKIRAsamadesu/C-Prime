#include <iostream>
using namespace std;
int &ref_func(int &a, int &b);
int &ref_func2(const int &a, int &b);
int redef_func(int a, int b);
int redef_func(int a, long long b);
// int redef_func(int a, int b);//顺序不同不能重构，必须不同类型参数的顺序不同

int main(void)
{
    /* 1. 堆区数据操作*/
    //变量
    int *p = new int(10);
    cout << "variable stack is:" << *p << endl;

    //数组
    int *arr = new int[11];
    for (int i = 10; i <= 20; i++)
    {
        arr[i - 10] = i;
        cout << "loop" << arr[i - 10] << endl;
    }
    // delete[] arr;                        //删除之后下面一行后面的所有的行都不会运行
    // cout << arr[0] << "arr var" << endl; //访问权限错误
    // cout << "1234" << endl;

    /* 2. 引用 */
    int a = 10;
    int &ref = a;
    cout << "ref" << ref << endl;
    ref = 20;
    cout << "ori:" << a << endl;

    int b = 300;
    // cout<<ref_func(a,b)<<endl;//不要返回局部变量的引用
    int res2 = ref_func2(a, b);

    cout << res2 << endl; //解决上面的问题，static放入全局区

    /* 3. 函数重载 */
    int j = 1;
    int k = 2;
    cout << redef_func(4, 276447200) << endl;
    long long l = 3;
    cout << redef_func(4, l) << endl;
    cout << redef_func(4, 2764472999) << endl; //重载的函数也是要在前面声明的
    cout << "long:" << sizeof(long) << endl;
    cout << "int:" << sizeof(int) << endl;
    cout << "longlong:" << sizeof(long long) << endl;
    cout << "short" << sizeof(short) << endl;

    /* 4. constructor and deconstructor */
    class example_class
    {
    public:
        example_class(int a, int b) //这个可以重构
        {
            self_a = a;
            self_b = b;
            cout << "constructor:" << self_a << self_b << endl;
        }
        example_class(const example_class &obj) //拷贝构造函数时记得加上const以防对原始数据的误操作
        {
            self_a = obj.self_a; //拷贝的时候可以访问另一个的private和protected属性
            self_b = obj.self_b;
            cout << "constructor:" << self_a << self_b << endl;
        }//这一部分拷贝构造函数是由编译器默认提供的，有别的构造函数时可以不写，如果用户写了的话，就没有其他的构造函数默认提供了
        example_class()
        {
            self_a = 0;
            self_b = 0;
            cout << "constructor:" << self_a << self_b << endl;
        }//如果写了有参构造函数，这个就不会默认提供
        ~example_class()
        {
            cout << "deconstructor" << endl;
        }

    private: //在拷贝构造函数的时候时可以访问的
        int self_a, self_b;
    };

    example_class *obj1 = new example_class(1, 2);
    // obj1.self_a=4;//在这样的时候时不能访问private属性和方法的
    example_class *obj2 = new example_class(*obj1);//右边这个example_class()是个匿名对象, obj2是指向这个匿名对象的指针
    delete obj1; //在堆区创建对象在这里销毁，调用deconstructor
    cout << "end of code" << endl;

    //不同的对象构造方法
    example_class obj3(4, 5);
    example_class obj4(*obj2); //注意放在heap区的拷贝要这么用
    example_class obj5(obj3);
    example_class obj6;
    //到这里obj2占用的内存没释放要手动释放
    delete obj2;
    //程序结束自动释放后面的obj3,4,5,6

    /* 5. 类属性的初始化 */
    class example_class2
    {
        public:
        example_class2(int a, int b): param_1(a), param_2(b)//这里的初始化可以直接给param1和param2赋值
        {
            cout<<param_1<<" and "<<param_2<<endl;
        }
        private:
        int param_1, param_2;
    };

    example_class2 *obj7 = new example_class2(3,3);//在调用时，若给已经设置默认值的参数传递实际值，既要取代默认值，则在参数表中被取代参数的左边所定义的所有参数，无论是否有默认值，都必须传递实际参数。

    /* 6. 函数指针 */
    int (*ptr)(int, int);//声明要指定函数的返回值和参数列表数据类型
    ptr = redef_func;//注意引用和指针标记也要带上
    a=1;
    b=2;
    cout<<"a:"<<a<<endl;
    cout<<"b:"<<b<<endl;
    cout<<"function pointer:"<<ptr(a,b)<<endl;
    //返回引用的函数如何用函数指针调用？？
}
/* ************************************************************************************ */
int &ref_func(int &a, int &b)
{
    int c = a + b;
    return c;
}

int &ref_func2(const int &a, int &b)
{
    static int c = a + b;
    // a=12;//const防止在这里被修改
    return c;
}

int redef_func(int a, long long b)
{
    return a - b;
}

int redef_func(int a, int b)
{
    return a + b;
}
