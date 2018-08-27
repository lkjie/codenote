#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        const int coeff[3] = {2,3,5};
        long long tmp = 1;
        set<long long> s;
        priority_queue<long long,vector<long long>, greater<long long>> priorityQueue;
        priorityQueue.push(1);
        while(n-->0) {
            tmp = priorityQueue.top(); priorityQueue.pop();
            for (auto j:coeff){
                long long e = tmp * j;
                if(!s.count(e)){
                    s.insert(e);
                    priorityQueue.push(e);
                }
            }
        }
        return tmp;
    }
};

int main(){
    int n;
//    cin >> n;
    Solution s;
    for (int i = 1; i < 20; ++i) {
        int tmp = s.nthUglyNumber(i);
        cout << tmp << ' ';
    }
    return 0;
}