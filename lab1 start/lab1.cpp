#include <iostream>
#include <string>
using namespace std;
struct str_global
{
    int param1;
    char param2;
    float param3;
} obj_global;

void func(str_global *ptr);

int main()
{
    /* 1. Input and Output */
    // std::cout<<"hello world!"<<std::endl;
    // int a,b=1;
    // std::cin>>a>>b;
    // std::cout<<a+b<<std::endl;
    /* 多行注释快捷键shift+Alt+A */

    /* 2. Flow of Control */
    //while(cond){}
    //for(init;cond;op){}

    /* 3. input unknown number of input */
    // int sum=0, value=0;
    // std::cout<<"input some numbers:"<<std::endl;
    // while (std::cin>>value){//read until the end of file. read until no more number to read
    //     sum+=value;
    //     std::cout<<"sum is:"<<sum<<std::endl;
    // }
    // std::cout<<"final sum is:"<<sum<<std::endl;

    /* 4. structure */
    // definitioin
    struct student //这里的struct关键字可以省略
    {
        string name;
        int age;
        float score;
    };
    // initialization
    student s1 = {"Andy", 12, 98};
    // assignment
    student s2;
    s2.name = "Roger";
    s2.age = 13;
    s2.score = 100;
    //create new obj when define
    struct teacher
    {
        string name;
        string course;
    } T1;
    T1.name = "Andrea";
    T1.course = "Physics";

    /* 5. 结构体数组 */
    student student_lst[3] = {{"Andrea", 14, 97},
                              {"Iman", 12, 100},
                              {"Hariri", 15, 60}};

    student_lst[0].score = 99;

    /* 6. 结构体指针 */
    student *p = &s1;
    p->name = "Mr.Nobody";
    cout << s1.name << endl;

    /* 7. 函数参数为结构体 */
    obj_global.param1 = 1;
    obj_global.param2 = 'q';
    obj_global.param3 = 3.1415f;
    func(&obj_global); //用这个可以免去值传递复制占用的空间

    return 0;
}

void func(str_global *ptr) //这里的参数如果用const修饰则结构体里的东西不能在这个函数中被改变
{
    cout << ptr->param1 << endl;
    cout << ptr->param2 << endl;
    cout << ptr->param3 << endl;
}