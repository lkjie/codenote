//
// Created by 李文杰 on 2018/7/25.
//
#include <iostream>

int n = 8;
int *c = new int[n];
int total = 0;

bool is_ok(int row) {
    for (int i = 0; i < row; ++i) {
        // 两者相等，或者斜率为正负1
        if (c[row] == c[i] || row - c[row] == i - c[i] || row + c[row] == i + c[i]) {
            return false;
        }
    }
    return true;
}

void eight(int row) {
    if (row == n) total++;
    else
        for (int col = 0; col < n; ++col) {
            c[row] = col;
            if (is_ok(row)) {
                eight(row + 1);
            }
        }
}

int main() {
    eight(0);
    printf("%d", total);
    return 0;
}