#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <list>
#include <stack>
#include <stdexcept>
#include <typeinfo>
#include <exception>
#include <queue>
#include <iterator>
#include <unistd.h>
#include <cassert>
#include <fstream>
#include <cmath>
#include <ctime>
#include <sstream>
#include <iomanip>
using namespace std;

// detail see the website : https://blog.csdn.net/xiajun07061225/article/details/8092247
// website has an error, the B should d[j][k] instead d[k][j]
const int n = 7;//点的数目
const int MaxVal = 999999;
const int MaxLen = 201;

struct tagPoint{
    double x,y;
};

//计算点i和点j之间的直线距离
double distance(tagPoint *points,int i,int j)
{
    return sqrt((points[i].x - points[j].x) * (points[i].x - points[j].x) +
                (points[i].y - points[j].y) * (points[i].y - points[j].y));
}

double DP(tagPoint *points,int n)
{
    double b[MaxLen][MaxLen];//记录最短路径的长度
    //计算所有情况下的b[i][j]，1 <= i, j; i >= j
    //初始化
    b[2][1] = distance(points,1,2);
    for (int i = 3; i <= n; ++i)
    {
        //j < i - 1
        for (int j = 1;j < i - 1; ++j)
        {
            b[i][j] = b[i - 1][j] + distance(points,i - 1, i);
        }
        //j = i - 1,b[i][j] = min(b[j][k] + distance(i, k));
        b[i][i - 1] = MaxVal;
        for (int k = 1;k < i - 1; ++k)
        {
            double temp = b[i - 1][k] + distance(points, i, k);
            if (temp < b[i][i - 1])
            {
                b[i][i - 1] = temp;
            }
        }
    }
    b[n][n] = INT_MAX;
//    for (int i = 1; i < n; ++i) {
//        double temp = b[n][i] + distance(points, i, n);
//        if(temp < b[n][n]) {
//            b[n][n] = temp;
//        }
//    }
    b[n][n] = b[n][n - 1] + distance(points, n, n - 1);


    return b[n][n];
}

int main()
{
    int NUM = 7;
//    while(cin >> NUM)
    {
        auto *points = new tagPoint[NUM + 1];
//        for (int i = 1;i <= NUM;++i)
//        {
//            cin >> points[i].x;
//            cin >> points[i].y;
//        }
        points[1].x = 0;
        points[1].y = 6;
        points[2].x = 1;
        points[2].y = 0;
        points[3].x = 2;
        points[3].y = 3;
        points[4].x = 5;
        points[4].y = 4;
        points[5].x = 6;
        points[5].y = 1;
        points[6].x = 7;
        points[6].y = 5;
        points[7].x = 8;
        points[7].y = 2;

        double minDis = DP(points,NUM);
        //设置输出格式：精确到小数点后2位
        cout.setf(ios::fixed);
        cout << setprecision(2) << minDis << endl;
    }
}



