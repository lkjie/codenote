//#include <iostream>
//#include <limits>
//
//
//class Bttsp
//{
//public:
//    static int n;
//    static int* x;
//    static int* bestx;
//    static float bestc;
//    static float cc;
//    static float ** a;
//
//public:
//    static float tsp(int *v) {
//        x = new int[n + 1];
//        for (int i = 1; i <= n; ++i) {
//            x[i] = i;
//        }
//        bestc = std::numeric_limits<float>::max();
//        bestx = v;
//        cc = 0;
//        backtrack(2);
//        return bestc;
//    }
//
//    static void swap(int *x,int i,int j){
//        int tmp = x[j];
//        x[j] = x[i];
//        x[i] = tmp;
//    }
//
//private:
//    static void backtrack(int i){
//        if(i==n){
//            if(a[x[n-1]][x[n]]<std::numeric_limits<float>::max() &&
//               a[x[n]][x[1]]<std::numeric_limits<float>::max() &&
//               (bestc==std::numeric_limits<float>::max()||cc+a[x[n-1]][x[n]]+a[x[n]][1]<bestc)){
//                for (int j = 1; j <= n ; ++j) {
//                    bestx[j] = x[j];
//                    bestc=cc+a[x[n-1]][x[n]]+a[x[n]][1];
//                }
//            }
//        }else{
//            for (int j = i; j <= n; ++j) {
//                if(a[x[j-1]][x[j]]<std::numeric_limits<float>::max()&&
//                   (bestc==std::numeric_limits<float>::max()||cc+a[x[i-1]][x[j]]<bestc)){
//                    swap(x,i,j);
//                    cc+=a[x[i-1]][x[i]];
//                    backtrack(i+1);
//                    cc-=a[x[i-1]][x[i]];
//                    swap(x,i,j);
//                }
//            }
//        }
//    }
//
//};
//int main() {
//    std::cout << "Hello, World!" << std::endl;
//    Bttsp c1 = Bttsp();
//    c1.n = 4;
//    int n = c1.n;
//    c1.a = new float*[c1.n + 1];
//    c1.x = new int[c1.n + 1];
//    int * v = new int[c1.n + 1];
//
//    for (int i = 0; i < n + 1; i++) {
//        c1.a[i] = new float[n + 1];
//        c1.x[i] = i;
//
//        for (int j = 0; j < n + 1; j++)
//            c1.a[i][j] = std::numeric_limits<float>::max();
//    }
//
//    c1.a[1][2] = c1.a[2][1] = 30;
//    c1.a[1][3] = c1.a[3][1] = 6;
//    c1.a[1][4] = c1.a[4][1] = 4;
//
//    c1.a[2][3] = c1.a[3][2] = 5;
//    c1.a[2][4] = c1.a[4][2] = 10;
//
//    c1.a[3][4] = c1.a[4][3] = 20;
//
//    c1.tsp(v);
//
//    return 0;
//}