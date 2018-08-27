//
// Created by 李文杰 on 2018/8/2.
//
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Solution {
public:
    bool hasPath(char *matrix, int rows, int cols, char *str) {
        bool isValid = false;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                auto *used = new bool[strlen(matrix)]();
                memset(used,0,strlen(matrix));
                isValid = dfs(matrix, rows, cols, str, i, j, used);
                delete used;
                if (isValid) return isValid;
            }
        }
        return isValid;
    }

    bool dfs(char *matrix, int rows, int cols, char *str, int rowloc, int colloc, bool *used) {
        if (*str == NULL) {
            return true;
        }
        bool isValid = false;
        if (*str == matrix[rowloc * cols + colloc]) {
            used[rowloc * cols + colloc] = true;
            if (rowloc > 0 && !used[(rowloc - 1) * cols + colloc]) {
                isValid = dfs(matrix, rows, cols, str + 1, rowloc - 1, colloc, used);
                if (isValid) return isValid;
            }
            if (rowloc < rows - 1 && !used[(rowloc + 1) * cols + colloc]) {
                isValid = dfs(matrix, rows, cols, str + 1, rowloc + 1, colloc, used);
                if (isValid) return isValid;
            }
            if (colloc > 0 && !used[rowloc * cols + colloc - 1]) {
                isValid = dfs(matrix, rows, cols, str + 1, rowloc, colloc - 1, used);
                if (isValid) return isValid;
            }
            if (rowloc < cols - 1 && !used[rowloc * cols + colloc + 1]) {
                isValid = dfs(matrix, rows, cols, str + 1, rowloc, colloc + 1, used);
                if (isValid) return isValid;
            }
        }
        return isValid;
    }
};

string &replace_all(string &str, const string &old_value, const string &new_value) {
    while (true) {
        int pos = 0;
        if ((pos = str.find(old_value, 0)) != string::npos)
            str.replace(pos, old_value.length(), new_value);
        else break;
    }
    return str;
}

void splitString(const std::string &s, std::vector<std::string> &v, const std::string &c) {
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (std::string::npos != pos2) {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length())
        v.push_back(s.substr(pos1));
}

int main() {
    auto *str = new char[1000]();
    cin >> str;
    string string1(str);
    replace_all(string1, "\"", "");
    vector<string> v;
    splitString(string1, v, ",");
    char *matrix = const_cast<char *>(v.at(0).c_str());
    int rows = atoi(v.at(1).c_str());
    int cols = atoi(v.at(2).c_str());
    char *strfind = const_cast<char *>(v.at(3).c_str());
    Solution s = Solution();
    cout << s.hasPath(matrix, rows, cols, strfind);
}