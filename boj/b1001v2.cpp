#ifndef BIGDECIMAL_H
#define BIGDECIMAL_H

#include<string>
#include<iostream>
#include<sstream>
#include <algorithm>
#include <limits.h>
template <typename T>
std::string to_string(const T& t) {
    std::stringstream ss;
    ss<<t;
    return ss.str();
}
class BigDecimal {

public:
    BigDecimal() { }
    BigDecimal(const BigDecimal &num) : value(num.value) { }
    BigDecimal(const char *num) : value(num) {  }
    BigDecimal(std::string num) : value(num) {  }
    BigDecimal(int num) : value() { std::stringstream ss; ss << num; value = ss.str(); }
    BigDecimal(long long num) : value() { std::stringstream ss; ss << num; value = ss.str(); }
    BigDecimal(unsigned int num) : value() { std::stringstream ss; ss << num; value = ss.str(); }
    BigDecimal(unsigned long long num) : value() { std::stringstream ss; ss << num; value = ss.str(); }
    BigDecimal(float num) : value() { std::stringstream ss; ss << num; value = ss.str(); }
    BigDecimal(double num) : value() { std::stringstream ss; ss << num; value = ss.str(); }
    BigDecimal(long double num) { std::stringstream ss; ss << num; value = ss.str(); }

    BigDecimal operator+(const BigDecimal& num) {
        return BigDecimal::add(value, num.value);
    }

    BigDecimal operator-(const BigDecimal& num) {
        return BigDecimal::subtract(value, num.value);
    }

    BigDecimal operator*(const BigDecimal& num) {
        return BigDecimal::multiply(value, num.value);
    }

    BigDecimal operator/(const BigDecimal& num) {
        return BigDecimal::divide(value, num.value);
    }

    BigDecimal operator%(const BigDecimal& num) {
        return BigDecimal::modulus(value, num.value);
    }

    BigDecimal operator^(const BigDecimal& num) {
        return BigDecimal::pow(value, num.value);
    }

    void operator+=(const BigDecimal& num) {
        value = BigDecimal::add(value, num.value);
    }
    void operator-=(const BigDecimal& num) {
        value = BigDecimal::subtract(value, num.value);
    }
    void operator*=(const BigDecimal& num) {
        value = BigDecimal::multiply(value, num.value);
    }
    void operator/=(const BigDecimal& num) {
        value = BigDecimal::divide(value, num.value);
    }
    void operator^=(const BigDecimal& num) {
        value = BigDecimal::pow(value, num.value);
    }

    bool operator > (const BigDecimal& num) {
        return BigDecimal::compareTo(value, num.value)>0;
    }
    bool operator >= (const BigDecimal& num) {
        return BigDecimal::compareTo(value, num.value)>=0;
    }
    bool operator == (const BigDecimal& num) {
        return BigDecimal::compareTo(value, num.value)==0;
    }
    bool operator < (const BigDecimal& num) {
        return BigDecimal::compareTo(value, num.value)<0;
    }
    bool operator <= (const BigDecimal& num) {
        return BigDecimal::compareTo(value, num.value)<=0;
    }

    int toInt() {
        std::istringstream buffer(value);
        int ret;
        buffer >> ret;
        return ret;
    }

    unsigned int toUInt() {
        std::istringstream buffer(value);
        unsigned int ret;
        buffer >> ret;
        return ret;
    }

    long long toLongLong() {
        std::istringstream buffer(value);
        long long ret;
        buffer >> ret;
        return ret;
    }

    unsigned long long toULongLong() {
        std::istringstream buffer(value);
        unsigned long long ret;
        buffer >> ret;
        return ret;
    }

    long double toLongDouble() {
        std::istringstream buffer(value);
        long double ret;
        buffer >> ret;
        return ret;
    }

    double toDouble() {
        std::istringstream buffer(value);
        double ret;
        buffer >> ret;
        return ret;
    }

    float toFloat() {
        std::istringstream buffer(value);
        float ret;
        buffer >> ret;
        return ret;
    }

    std::string toString() {
        return value;
    }

    void round(int scale) {
        if(scale>=1)
            value = BigDecimal::round(value, scale);
    }

    std::string getIntPart() {
        std::size_t dot = value.find('.');
        if(dot != std::string::npos) {
            if(dot == 0)
                return std::string("0");
            if(dot == 1 && value[0] == '-')
                return std::string("-0");
            return value.substr(0, dot);
        }else{
            return value;
        }
    }

    std::string getDecPart() {
        std::size_t dot = value.find('.');
        if(dot != std::string::npos)
            return value.length()>dot+1?value.substr(dot+1):std::string("0");
        else
            return std::string("0");
    }

private:
    std::string value;

public:

    static void setscale (int scale);

    static std::string divide (const std::string &lhs, const std::string &rhs,int scale = INT_MIN);

    static std::string modulus (const std::string &lhs, const std::string &rhs,int scale = INT_MIN);

    static std::string pow (const std::string &lhs, const std::string &rhs,int scale = INT_MIN);

    static std::string add (const std::string &lhs, const std::string &rhs,int scale = INT_MIN);

    static std::string subtract (const std::string &lhs, const std::string &rhs,int scale = INT_MIN);

    static std::string multiply (const std::string &lhs, const std::string &rhs,int scale = INT_MIN);

    static std::string round (const std::string &lhs,int scale = INT_MIN);

    static int compareTo (const std::string &lhs, const std::string &rhs,int scale = INT_MIN);

    static std::string log2(const std::string &lhs,int scale = INT_MIN);

    static std::string ln(const std::string &lhs,int scale = INT_MIN);

    static std::string log(const std::string &lhs,int scale = INT_MIN);

    static std::string sin(const std::string &lhs,int scale = INT_MIN);

    static std::string stringToHex(std::string &lhs,int caps = 0);
};

#define _ASSERT(cond) ((!(cond)) ? _assert(#cond,__FILE__,__LINE__) : _noassert())

#include "BigDecimal.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
static int _scale = 100;

static const std::string ONE ("1");
static const std::string ZERO ("0");
static const std::string TEN("10");
static void _noassert() { }
static std::string getLeftOfDot(std::string &value)
{
    std::size_t dot = value.find('.');
    if(dot != std::string::npos) {
        if(dot == 0)
            return std::string("0");
        if(dot == 1 && value[0] == '-')
            return std::string("-0");
        return value.substr(0, dot);
    }else{
        return value;
    }
}
static void _assert(const char *assertion, const char *file, int line) {
    std::cerr<<"Critical Error in: "<<assertion<<", File '"<<file<<"' in line "<<line<<"."<<std::endl;
    exit(-1);
}
std::string trimTrailingZeros(std::string input)
{
    if(input.find(".") != std::string::npos)
    {
        std::string result = "";
        std::size_t i;
        std::string inp(input.rbegin(),input.rend());
        result = inp.erase(0,std::min(inp.find_first_not_of('0'),inp.size()-1));
        if(result.at(0) == '.')
        {
            result = result.erase(0,1);
        }
        return std::string(result.rbegin(),result.rend());
    }
    else
    {
        return input;
    }
}
//parse a number into parts, returns scale on success and -1 on error
static int parse_number (const std::string &s, int &lsign, int &lint, int &ldot, int &lfrac, int &lscale) {
    int i = 0;
    lsign = 1;
    if (s[i] == '-' || s[i] == '+') {
        if (s[i] == '-') {
            lsign = -1;
        }
        i++;
    }
    int len = s.length();
    if (i >= len) {
        return -1;
    }
    lint = i;

    while (i < len && '0' <= s[i] && s[i] <= '9') {
        i++;
    }
    ldot = i;

    lscale = 0;
    if (i < len && s[i] == '.') {
        lscale = (int)s.length() - i - 1;
        i++;
    }
    lfrac = i;

    while (i < len && '0' <= s[i] && s[i] <= '9') {
        i++;
    }

    if (i < len) {
        return -1;
    }

    while (s[lint] == '0' && lint + 1 < ldot) {
        lint++;
    }
//  while (lscale > 0 && s[lfrac + lscale - 1] == '0') {
//    lscale--;
//  }
    if (lscale == 0 && lfrac > ldot) {
        lfrac--;
        _ASSERT (lfrac == ldot);
    }

    if (lsign < 0 && (lscale == 0 && s[lint] == '0')) {
        lsign = 1;
    }
    return lscale;
}

static std::string _zero (int scale) {
    if (scale == 0) {
        return ZERO;
    }
    std::string result (scale + 2, '0');
    result[1] = '.';
    return result;
}

static int _compareTo (const char *lhs, int lint, int ldot, int lfrac, int lscale, const char *rhs, int rint, int rdot, int rfrac, int rscale, int scale) {
    int llen = ldot - lint;
    int rlen = rdot - rint;

    if (llen != rlen) {
        return (llen < rlen ? -1 : 1);
    }

    for (int i = 0; i < llen; i++) {
        if (lhs[lint + i] != rhs[rint + i]) {
            return (lhs[lint + i] < rhs[rint + i] ? -1 : 1);
        }
    }

    int i;
    for (i = 0; (i < lscale || i < rscale) && i < scale; i++) {
        int lchar = (i < lscale ? lhs[lfrac + i] : '0');
        int rchar = (i < rscale ? rhs[rfrac + i] : '0');
        if (lchar != rchar) {
            return (lchar < rchar ? -1 : 1);
        }
    }

    return 0;
}

static std::string _round (char *lhs, int lint, int ldot, int lfrac, int lscale, int scale, int sign, bool add_trailing_zeroes, bool round_last = false) {
    while (lhs[lint] == '0' && lint + 1 < ldot) {
        lint++;
    }

    _ASSERT (lint > 0 && lscale >= 0 && scale >= 0);

    if (sign < 0 && lhs[lint] == '0') {
        sign = 1;
        for (int i = 0; i < lscale; i++) {
            if (lhs[lfrac + i] != '0') {
                sign = -1;
                break;
            }
        }
    }

    if(round_last) {
        if (lscale > scale) {
            while (scale > 0 && lhs[lfrac + scale - 1] == '9' && lhs[lfrac + scale] >= '5') {
                scale--;
            }
            lscale = scale;
            if (lhs[lfrac + scale] >= '5') {
                if (scale > 0) {
                    lhs[lfrac + scale - 1]++;
                } else {
                    lfrac--;
                    _ASSERT (lfrac == ldot);

                    int i;
                    lhs[lint - 1] = '0';
                    for (i = 0; lhs[ldot - i - 1] == '9'; i++) {
                        lhs[ldot - i - 1] = '0';
                    }
                    lhs[ldot - i - 1]++;
                    if (ldot - i - 1 < lint) {
                        lint = ldot - i - 1;
                    }
                }
            }
        }

        while (lscale > 0 && lhs[lfrac + lscale - 1] == '0') {
            lscale--;
        }
    }else{
        if (lscale > scale) {
            lscale = scale;
        }
    }

    if (lscale == 0 && lfrac > ldot) {
        lfrac--;
        _ASSERT (lfrac == ldot);
    }

    if (sign < 0) {
        lhs[--lint] = '-';
    }

    if (lscale == scale || !add_trailing_zeroes) {
        return std::string (std::string(lhs + lint).substr(0, lfrac + lscale - lint));
    } else {
        std::string result (std::string(lhs + lint).substr(0, lfrac + lscale - lint));
        if (lscale == 0) {
            result+='.';
        }
        for(int kI = 0; kI < scale - lscale; ++kI)
            result+='0';
        return result;
    }
}

static std::string add_positive (const char *lhs, int lint, int ldot, int lfrac, int lscale, const char *rhs, int rint, int rdot, int rfrac, int rscale, int scale, int sign) {
    int llen = ldot - lint;
    int rlen = rdot - rint;

    int resint, resdot, resfrac, resscale;

    int result_len = std::max (llen, rlen) + 1;
    int result_scale = std::max (lscale, rscale);
    int result_size = result_len + result_scale + 3;
    std::string result(result_size, '0');

    int i, um = 0;
    int cur_pos = result_size;
    int was_frac = 0;
    for (i = result_scale - 1; i >= 0; i--) {
        if (i < lscale) {
            um += lhs[lfrac + i] - '0';
        }
        if (i < rscale) {
            um += rhs[rfrac + i] - '0';
        }

        if (um != 0 || was_frac) {
            result[--cur_pos] = (char)(um % 10 + '0');
            um /= 10;
            was_frac = 1;
        }
    }
    resscale = result_size - cur_pos;
    resfrac = cur_pos;
    if (was_frac) {
        result[--cur_pos] = '.';
    }
    resdot = cur_pos;

    for (int i = 0; i < result_len; i++) {
        if (i < llen) {
            um += lhs[ldot - i - 1] - '0';
        }
        if (i < rlen) {
            um += rhs[rdot - i - 1] - '0';
        }

        result[--cur_pos] = (char)(um % 10 + '0');
        um /= 10;
    }
    resint = cur_pos;
    _ASSERT (cur_pos > 0);

    return _round ((char*)result.data(), resint, resdot, resfrac, resscale, scale, sign, 1);
}

static std::string subtract_positive (const char *lhs, int lint, int ldot, int lfrac, int lscale, const char *rhs, int rint, int rdot, int rfrac, int rscale, int scale, int sign) {
    int llen = ldot - lint;
    int rlen = rdot - rint;

    int resint, resdot, resfrac, resscale;

    int result_len = llen;
    int result_scale = std::max (lscale, rscale);
    int result_size = result_len + result_scale + 3;
    std::string result (result_size, '0');

    int i, um = 0, next_um = 0;
    int cur_pos = result_size;
    int was_frac = 0;
    for (i = result_scale - 1; i >= 0; i--) {
        um = next_um;
        if (i < lscale) {
            um += lhs[lfrac + i] - '0';
        }
        if (i < rscale) {
            um -= rhs[rfrac + i] - '0';
        }
        if (um < 0) {
            next_um = -1;
            um += 10;
        } else {
            next_um = 0;
        }

        if (um != 0 || was_frac) {
            result[--cur_pos] = (char)(um + '0');
            was_frac = 1;
        }
    }
    resscale = result_size - cur_pos;
    resfrac = cur_pos;
    if (was_frac) {
        result[--cur_pos] = '.';
    }
    resdot = cur_pos;

    for (int i = 0; i < result_len; i++) {
        um = next_um;
        um += lhs[ldot - i - 1] - '0';
        if (i < rlen) {
            um -= rhs[rdot - i - 1] - '0';
        }
        if (um < 0) {
            next_um = -1;
            um += 10;
        } else {
            next_um = 0;
        }

        result[--cur_pos] = (char)(um + '0');
    }
    resint = cur_pos;
    _ASSERT (cur_pos > 0);

    return _round ((char*)result.data(), resint, resdot, resfrac, resscale, scale, sign, 1);
}

static std::string multiply_positive (const char *lhs, int lint, int ldot, int lfrac, int lscale, const char *rhs, int rint, int rdot, int rfrac, int rscale, int scale, int sign) {
    int llen = ldot - lint;
    int rlen = rdot - rint;

    int resint, resdot, resfrac, resscale;

    int result_len = llen + rlen;
    int result_scale = lscale + rscale;
    int result_size = result_len + result_scale + 3;
    std::string result (result_size, '0');

    int *res = (int *)malloc(sizeof (int) * result_size);
    memset(res, 0, sizeof (int) * result_size);
    for (int i = -lscale; i < llen; i++) {
        int x = (i < 0 ? lhs[lfrac - i - 1] : lhs[ldot - i - 1]) - '0';
        for (int j = -rscale; j < rlen; j++) {
            int y = (j < 0 ? rhs[rfrac - j - 1] : rhs[rdot - j - 1]) - '0';
            res[i + j + result_scale] += x * y;
        }
    }
    for (int i = 0; i + 1 < result_size; i++) {
        res[i + 1] += res[i] / 10;
        res[i] %= 10;
    }

    int cur_pos = result_size;
    for (int i = 0; i < result_scale; i++) {
        result[--cur_pos] = (char)(res[i] + '0');
    }
    resscale = result_size - cur_pos;
    resfrac = cur_pos;
    if (result_scale > 0) {
        result[--cur_pos] = '.';
    }
    resdot = cur_pos;

    for (int i = result_scale; i < result_len + result_scale; i++) {
        result[--cur_pos] = (char)(res[i] + '0');
    }
    resint = cur_pos;
    _ASSERT (cur_pos > 0);

    free(res);

    char *data = (char*)malloc((result.length()+1)*sizeof(char));
    sprintf(data, result.c_str());
    std::string ret = _round (data, resint, resdot, resfrac, resscale, scale, sign, 0);
    free(data);

    return ret;
}

static std::string divide_positive (const char *lhs, int lint, int ldot, int lfrac, int lscale, const char *rhs, int rint, int rdot, int rfrac, int rscale, int scale, int sign) {
    int llen = ldot - lint;
    int rlen = rdot - rint;

    int resint, resdot = -1, resfrac = -1, resscale;

    int result_len = std::max (llen + rscale - rlen + 1, 1);
    int result_scale = scale;
    int result_size = result_len + result_scale + 3;

    if (rscale == 0 && rhs[rint] == '0') {
        std::cerr << ("Division By ZERO")<< std::endl<< std::endl;
        return ZERO;
    }

    int dividend_len = llen + lscale;
    int divider_len = rlen + rscale;
    int *dividend = (int *)malloc(sizeof (int) * (result_size + dividend_len + divider_len));
    int *divider = (int *)malloc(sizeof (int) * divider_len);
    memset(dividend, 0, sizeof (int) * (result_size + dividend_len + divider_len));
    memset(divider, 0, sizeof (int) * divider_len);

    for (int i = -lscale; i < llen; i++) {
        int x = (i < 0 ? lhs[lfrac - i - 1] : lhs[ldot - i - 1]) - '0';
        dividend[llen - i - 1] = x;
    }

    for (int i = -rscale; i < rlen; i++) {
        int x = (i < 0 ? rhs[rfrac - i - 1] : rhs[rdot - i - 1]) - '0';
        divider[rlen - i - 1] = x;
    }

    int divider_skip = 0;
    while (divider_len > 0 && divider[0] == 0) {
        divider++;
        divider_skip++;
        divider_len--;
    }
    _ASSERT (divider_len > 0);

    int cur_pow = llen - rlen + divider_skip;
    int cur_pos = 2;

    if (cur_pow < -scale) {
        divider -= divider_skip;
        divider_len += divider_skip;
        free(dividend);
        free(divider);
        return _zero (scale);
    }

    std::string result (result_size, '0');
    resint = cur_pos;
    if (cur_pow < 0) {
        result[cur_pos++] = '0';
        resdot = cur_pos;
        result[cur_pos++] = '.';
        resfrac = cur_pos;
        for (int i = -1; i > cur_pow; i--) {
            result[cur_pos++] = '0';
        }
    }

    int beg = 0, real_beg = 0;
    while (cur_pow >= -scale) {
        char dig = '0';
        while (true) {
            if (real_beg < beg && dividend[real_beg] == 0) {
                real_beg++;
            }

            bool less = false;
            if (real_beg == beg) {
                for (int i = 0; i < divider_len; i++) {
                    if (dividend[beg + i] != divider[i]) {
                        less = (dividend[beg + i] < divider[i]);
                        break;
                    }
                }
            }
            if (less) {
                break;
            }

            for (int i = divider_len - 1; i >= 0; i--) {
                dividend[beg + i] -= divider[i];
                if (dividend[beg + i] < 0) {
                    dividend[beg + i] += 10;
                    dividend[beg + i - 1]--;
                }
            }
            dig++;
        }

        result[cur_pos++] = dig;

        if (cur_pow == 0) {
            resdot = cur_pos;
            if (scale > 0) {
                result[cur_pos++] = '.';
            }
            resfrac = cur_pos;
        }
        cur_pow--;
        beg++;
    }
    resscale = cur_pos - resfrac;

    divider -= divider_skip;
    divider_len += divider_skip;
    free(dividend);
    free(divider);

    char *data = (char*)malloc((result.length()+1)*sizeof(char));
    sprintf(data, result.c_str());
    std::string ret = _round (data, resint, resdot, resfrac, resscale, scale, sign, 0);
    free(data);

    return ret;
}


static std::string _add (const char *lhs, int lsign, int lint, int ldot, int lfrac, int lscale, const char *rhs, int rsign, int rint, int rdot, int rfrac, int rscale, int scale) {
    if (lsign > 0 && rsign > 0) {
        return add_positive (lhs, lint, ldot, lfrac, lscale, rhs, rint, rdot, rfrac, rscale, scale, 1);
    }

    if (lsign > 0 && rsign < 0) {
        if (_compareTo (lhs, lint, ldot, lfrac, lscale, rhs, rint, rdot, rfrac, rscale, 1000000000) >= 0) {
            return subtract_positive (lhs, lint, ldot, lfrac, lscale, rhs, rint, rdot, rfrac, rscale, scale, 1);
        } else {
            return subtract_positive (rhs, rint, rdot, rfrac, rscale, lhs, lint, ldot, lfrac, lscale, scale, -1);
        }
    }

    if (lsign < 0 && rsign > 0) {
        if (_compareTo (lhs, lint, ldot, lfrac, lscale, rhs, rint, rdot, rfrac, rscale, 1000000000) <= 0) {
            return subtract_positive (rhs, rint, rdot, rfrac, rscale, lhs, lint, ldot, lfrac, lscale, scale, 1);
        } else {
            return subtract_positive (lhs, lint, ldot, lfrac, lscale, rhs, rint, rdot, rfrac, rscale, scale, -1);
        }
    }

    if (lsign < 0 && rsign < 0) {
        return add_positive (lhs, lint, ldot, lfrac, lscale, rhs, rint, rdot, rfrac, rscale, scale, -1);
    }

    _ASSERT (0);
    return ZERO; //Is dummy...
}

void BigDecimal::setscale (int scale) {
    if (scale < 0) {
        _scale = 0;
    } else {
        _scale = scale;
    }
}

std::string BigDecimal::divide (const std::string &lhs, const std::string &rhs,int scale) {
    if (scale == INT_MIN) {
        scale = _scale;
    }
    if (scale < 0) {
        std::cerr << "Scale ("<<to_string(scale).c_str()<<") Cant Be Negative!!!"<<std::endl;
        scale = 0;
    }
    if (lhs.empty()) {
        return _zero (scale);
    }
    if (rhs.empty()) {
        std::cerr << "Division By Empty "<<  rhs.c_str() << std::endl;
        return _zero (scale);
    }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number (lhs, lsign, lint, ldot, lfrac, lscale) < 0) {
        std::cerr << "\""<<  lhs.c_str() <<"\" Is Not A Number"<< std::endl;
        return ZERO;
    }

    int rsign, rint, rdot, rfrac, rscale;
    if (parse_number (rhs, rsign, rint, rdot, rfrac, rscale) < 0) {
        std::cerr << "\""<< rhs.c_str() <<"\" Is Not A Number"<< std::endl;
        return ZERO;
    }

    return trimTrailingZeros(divide_positive (lhs.c_str(), lint, ldot, lfrac, lscale, rhs.c_str(), rint, rdot, rfrac, rscale, scale, lsign * rsign));
}

std::string BigDecimal::modulus (const std::string &lhs, const std::string &rhs,int scale) {
    if (lhs.empty()) {
        return ZERO;
    }
    if (rhs.empty()) {
        std::cerr << "Modulo By empty "<<std::endl;
        return ZERO;
    }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number (lhs, lsign, lint, ldot, lfrac, lscale) != 0) {
        std::cerr << "\""<< lhs.c_str() <<"\" Is Not A Integer"<< std::endl;
        return ZERO;
    }

    int rsign, rint, rdot, rfrac, rscale;
    if (parse_number (rhs, rsign, rint, rdot, rfrac, rscale) != 0) {
        std::cerr << "\""<< rhs.c_str() <<"\" Is Not A Number"<< std::endl;
        return ZERO;
    }

    long long mod = 0;
    for (int i = rint; i < rdot; i++) {
        mod = mod * 10 + rhs[i] - '0';
    }

    if (rdot - rint > 18 || mod == 0) {
        std::cerr << "\""<< rhs.c_str() <<"\" Is Not A Non Zero Integer Less Than 1e18 By Absolute Value"<< std::endl;
        return ZERO;
    }

    long long res = 0;
    for (int i = lint; i < ldot; i++) {
        res = res * 2;
        if (res >= mod) {
            res -= mod;
        }
        res = res * 5 + lhs[i] - '0';
        while (res >= mod) {
            res -= mod;
        }
    }

    char buffer[20];
    int cur_pos = 20;
    do {
        buffer[--cur_pos] = (char)(res % 10 + '0');
        res /= 10;
    } while (res > 0);

    if (lsign < 0) {
        buffer[--cur_pos] = '-';
    }

    return std::string(trimTrailingZeros(std::string(buffer + cur_pos).substr(0, 20 - cur_pos)));
}

std::string BigDecimal::pow (const std::string &lhs, const std::string &rhs,int scale) {
    if (lhs.empty()) {
        return ZERO;
    }
    if (rhs.empty()) {
        return ONE;
    }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number (lhs, lsign, lint, ldot, lfrac, lscale) != 0) {
        std::cerr << "\""<<lhs.c_str()<<"\" Is Not A Number"<< std::endl;
        return ZERO;
    }

    int rsign, rint, rdot, rfrac, rscale;
    if (parse_number (rhs, rsign, rint, rdot, rfrac, rscale) != 0) {
        std::cerr << "\""<< rhs.c_str() <<"\" Is Not A Number"<< std::endl;
        return ZERO;
    }

    long long deg = 0;
    for (int i = rint; i < rdot; i++) {
        deg = deg * 10 + rhs[i] - '0';
    }

    if (rdot - rint > 18 || (rsign < 0 && deg != 0)) {
        std::cerr << "\""<< rhs.c_str() <<"\" Is Not A Non Negative Integer Less Than 1e18"<< std::endl;
        return ZERO;
    }

    if (deg == 0) {
        return ONE;
    }

    std::string result = ONE;
    std::string mul = lhs;
    while (deg > 0) {
        if (deg & 1) {
            result = multiply (result, mul, 0);
        }
        mul = multiply (mul, mul, 0);
        deg >>= 1;
    }

    return trimTrailingZeros(result);
}

std::string BigDecimal::add (const std::string &lhs, const std::string &rhs, int scale) {
    if (lhs.empty()) {
        return add (ZERO, rhs, scale);
    }
    if (rhs.empty()) {
        return add (lhs, ZERO, scale);
    }
    if (scale < 0) {
        std::cerr <<"Scale ("<<to_string(scale).c_str()<<") Cant Be Negative!!!"<< std::endl;
        scale = 0;
    }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number (lhs, lsign, lint, ldot, lfrac, lscale) < 0) {
        std::cerr << "\""<< lhs.c_str() << "\" Is Not A Number"<< std::endl;
        return _zero (scale);
    }

    int rsign, rint, rdot, rfrac, rscale;
    if (parse_number (rhs, rsign, rint, rdot, rfrac, rscale) < 0) {
        std::cerr << "\""<< rhs.c_str() << "\" Is Not A Number"<< std::endl;
        return _zero (scale);
    }

    return trimTrailingZeros(_add (lhs.c_str(), lsign, lint, ldot, lfrac, lscale, rhs.c_str(), rsign, rint, rdot, rfrac, rscale, std::max (lscale, rscale)));
}

std::string BigDecimal::subtract (const std::string &lhs, const std::string &rhs, int scale) {
    if (lhs.empty()) {
        return subtract (ZERO, rhs, scale);
    }
    if (rhs.empty()) {
        return subtract (lhs, ZERO, scale);
    }
    if (scale < 0) {
        std::cerr <<"Scale ("<<to_string(scale).c_str()<<") Cant Be Negative!!!"<< std::endl;
        scale = 0;
    }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number (lhs, lsign, lint, ldot, lfrac, lscale) < 0) {
        std::cerr << "\""<<lhs.c_str()<<"\" Is Not A Number"<< std::endl;
        return _zero (scale);
    }

    int rsign, rint, rdot, rfrac, rscale;
    if (parse_number (rhs, rsign, rint, rdot, rfrac, rscale) < 0) {
        std::cerr << "\""<<rhs.c_str()<<"\" Is Not A Number"<< std::endl;
        return _zero (scale);
    }

    rsign *= -1;

    return trimTrailingZeros(_add (lhs.c_str(), lsign, lint, ldot, lfrac, lscale, rhs.c_str(), rsign, rint, rdot, rfrac, rscale, std::max (lscale, rscale)));
}

std::string BigDecimal::multiply (const std::string &lhs, const std::string &rhs, int scale) {
    if (lhs.empty()) {
        return multiply (ZERO, rhs, scale);
    }
    if (rhs.empty()) {
        return multiply (lhs, ZERO, scale);
    }
    if (scale < 0) {
        std::cerr <<"Scale ("<<to_string(scale).c_str()<<") Cant Be Negative!!!"<< std::endl;
        scale = 0;
    }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number (lhs, lsign, lint, ldot, lfrac, lscale) < 0) {
        std::cerr << "\""<<lhs.c_str()<<"\" Is Not A Number"<< std::endl;
        return ZERO;
    }

    int rsign, rint, rdot, rfrac, rscale;
    if (parse_number (rhs, rsign, rint, rdot, rfrac, rscale) < 0) {
        std::cerr << "\""<<rhs.c_str()<<"\" Is Not A Number"<< std::endl;
        return ZERO;
    }

    return trimTrailingZeros(multiply_positive (lhs.c_str(), lint, ldot, lfrac, lscale, rhs.c_str(), rint, rdot, rfrac, rscale, lscale + rscale, lsign * rsign));
}

int BigDecimal::compareTo (const std::string &lhs, const std::string &rhs, int scale) {
    if (lhs.empty()) {
        return BigDecimal::compareTo (ZERO, rhs, scale);
    }
    if (rhs.empty()) {
        return BigDecimal::compareTo (lhs, ZERO, scale);
    }

    if (scale == INT_MIN) {
        scale = _scale;
    }
    if (scale < 0) {
        std::cerr << "Scale ("<<to_string(scale).c_str()<<") Cant Be Negative!!!"<< std::endl;
        scale = 0;
    }

    int lsign, lint, ldot, lfrac, lscale;
    if (parse_number (lhs, lsign, lint, ldot, lfrac, lscale) < 0) {
        std::cerr << "\""<<lhs.c_str()<<"\" Is Not A Number"<< std::endl;
        return 0;
    }

    int rsign, rint, rdot, rfrac, rscale;
    if (parse_number (rhs, rsign, rint, rdot, rfrac, rscale) < 0) {
        std::cerr << "\""<<rhs.c_str()<<"\" Is Not A Number"<< std::endl;
        return 0;
    }

    if (lsign != rsign) {
        return (lsign - rsign) / 2;
    }

    return (1 - 2 * (lsign < 0)) * _compareTo (lhs.c_str(), lint, ldot, lfrac, lscale, rhs.c_str(), rint, rdot, rfrac, rscale, scale);
}

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