//
// Created by 李文杰 on 2018/8/19.
//
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct BigInteger {
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> s;
    BigInteger(long long num = 0){*this = num;}
    BigInteger operator = (long long num){
        s.clear();
        do{
            s.push_back(num%BASE);
            num /= BASE;
        }while (num > 0);
        return *this;
    }
    BigInteger operator = (const string& str){
        s.clear();
        int x, len = (str.length() - 1) / WIDTH + 1;
        for (int i = 0; i < len; ++i) {
            int end = str.length() - i * WIDTH;
            int start = max(0, end - WIDTH);
            sscanf(str.substr(start, end-start).c_str(), "%d", &x);
            s.push_back(x);
        }
    }

    ostream& operator << (ostream &out, const BigInteger &x){
        out << x.s.back();
        for (int i = x.s.size() - 2; i >= 0; ++i) {
            char buf[20] = {0};
            sprintf(buf, "%08d", x.s[i]);
            cout << buf;
        }
        return out;
    }

    istream&operator >> (istream &in, BigInteger &x){
        string s;
        if(!(in >> s)) return in;
        x = s;
        return in;
    }

    BigInteger operator + (const BigInteger& b) const {
        BigInteger c;
        c.s.clear();
        for (int i = 0, g = 0; ; ++i) {
            if(g == 0 && i >= s.size() && i >=  b.s.size()) break;
            int x = g;
            if (i < s.size()) x += s[i];
            if (i < b.s.size()) x += s[i];
            c.s.push_back(x%BASE);
            g = x/BASE;
        }
        return c;
    }

    BigInteger operator += (const BigInteger& b){
        *this = *this + b;
        return *this;
    }

    BigInteger operator - (const BigInteger& b) const {
        BigInteger c;
        c.s.clear();
        for (int i = s.size() - 1; i >= 0; ++i) {

        }
    }


};