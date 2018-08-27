//
// Created by 李文杰 on 2018/8/23.
//

#include <iostream>
//#include <string>
#include <algorithm>
#include <vector>
#include <map>

class A
{
public:
    A() { std::cout << "Constructor" << std::endl; }
    A(const A&) { std::cout << "Copy Constructor" << std::endl; }
    A(const A&&) { std::cout << "Move Constructor" << std::endl; }
    ~A() {}
};

static A getA()
{
    A a;
    printf("A\n");
    return a;
}
int main(){
   int a = 6;
   int &add_a(a);
   std::cout << &a << " " << &add_a << std::endl;
   add_a = 7;
   std::cout << a << std::endl;
   std::cout << &a << " " << &add_a << std::endl;
   int b = 16;
   int &&add_b(b + 1);
   std::cout << &b << " " << &add_b << std::endl;
   add_b = 17;
   std::cout << b << std::endl;
   std::cout << &b << " " << &add_b << std::endl;
    A c(getA());
    std::map<std::string, std::string> kv;
    kv.insert(std::pair<std::string,std::string>("123","456"));
    kv["sdf"] = "123213";
    std::string s("我是东方阿萨德未付");
    std::cout << s;
    
    return 0;
}