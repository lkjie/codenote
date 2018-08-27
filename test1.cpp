//#include <iostream>
//#include <string>
//using namespace std;
//
//void g(string &a,const string &b)
//{
//    cout<<"a address :"<<&a<<endl;
//    cout<<"b address :"<<&b<<endl;
//
////    return a;
//}
//
//string f()
//{
//}
//int main()
//{
//    string input="I love you";
//    char *b0="***";
//    const char *b1="***";
//    int a=1;
// //   int b=2;
//    cout<< "input address: "<<&input<<endl;
//    cout<<"b0 address: "<<&b0<<endl;
//    cout<<"b1 address: "<<&b1<<endl;
//
////    g(input,b);
//
////    g(input,input);
//
//    getchar();
//return 0;
//}

#include<iostream>
#include <unistd.h>
#include "boj/BigDecimal.h"
#include <cmath>

using namespace std;

void bar();

int main() {
    double r;
    int n;
    int MIN_VALUE;
    while(cin>>r>>n){
        char str[256];
        if(abs(r) < MIN_VALUE){
            cout << 0 <<endl;
            continue;
        }
        sprintf(str,"%lf",r);
        string result = str;
        string b1 = result.substr(0,result.find('.'));
        string b2 = result.substr(result.find('.')+1,result.size());
        for (unsigned long i = b2.length() - 1; b2[i] == '0'; --i) {
            b2.erase(i);
        }
        int pointzero = (int)b2.length() * n;
        b1 = b1 + b2;
        BigDecimal bi(b1.c_str());
        bi = bi^n;
        string res(bi.toString());
        int i=0;
        while(res[i] == '0') i++;
        res = res.substr(i,res.length());
        if (res.length() < pointzero){
            char *c = new char[pointzero - res.length() + 1];
            memset(c,'0', sizeof(char)*(pointzero - res.length()));
            c[pointzero - res.length()] = 0;
            cout << "." << c << res << endl;
        } else if(pointzero == 0){
            cout << res << endl;
        } else{
            cout << res.substr(0,res.length()-pointzero) << '.' << res.substr(res.length()-pointzero,res.length()) << endl;
        }
    }
}

void bar() {
    int i, j;
    printf("/n");
    for (i = 0; i <= 10; i++) {
        printf("[");
        for (j = 0; j < i; j++) printf(">");
        for (; j < 10; j++) printf(" ");
        printf("]");
        printf("%3d%%", i * 10);
        if (i == 10) { printf(" [COMPLETED]"); }
        printf("/r");
        fflush(stdout);
        sleep(1);
    }
    printf("/n");
}
