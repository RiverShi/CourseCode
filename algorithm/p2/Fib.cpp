#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include "Matrix.hpp"

using namespace std;

#define db double
#define ldb long double
#define uLL unsigned long long


/*
    大数也就图一乐,精度问题没法解决
    不过只是比较时间复杂度倒是没什么
    pow的参数类型是double，用 long double保存数据是没有意义的, 到 10^308也就inf了，精度也不会更高
    不如就自然溢出吧
*/

uLL pow_long(uLL a, int x)      //二分快速幂
{
    uLL ans = 1;
    while(x)
    {
        if(x&1) ans = ans*a;
        a *= a;
        x >>= 1;
    }
    return ans;
}


double get_fib_by_GF(int n)     //通项公式
{
    static double sqrt_5 = sqrt(5);
    return ( pow((1+sqrt_5)/2, n)-pow((1-sqrt_5)/2, n) ) / sqrt_5;
}

uLL Fib_DGS[10000];

uLL get_fib_by_DT(int n)        //递推算法 DiTui
{
    if(n == 0)return 0;
    if(n == 1)return 1;
    uLL a = 0, b = 1, c, i;
    for(i = 2; i <= n; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

uLL get_fib_by_DG(int n)        //递归算法 DiGui
{
    if(n <= 1)return n;
    return get_fib_by_DG(n-1) + get_fib_by_DG(n-2);
}

uLL get_fib_by_DGS(int n)        //带保存结果的递归算法 (或许算动态规划？ Maybe)  DiGui with Save
{
    if(n <= 1)return n;
    if(Fib_DGS[n] >= 1)return Fib_DGS[n];
    return Fib_DGS[n] = get_fib_by_DGS(n-1) + get_fib_by_DGS(n-2);
}

uLL get_fib_by_Matrix(int n)       //矩阵加速
{
    if(n <= 1)return n;

    Matrix A(2,2);
	A.element[1][1]= 1;
	A.element[1][2]= 1;
	A.element[2][1]= 1;
	A.element[2][2]= 0;

    A = A^(n-1);

    Matrix F(2,1);
    F.element[1][1] = 1;
    F.element[2][2] = 0;

    Matrix Ans;
    Ans = A*F;
    return Ans.element[1][1];

    // 由于Matrix用double实现的，故会产生精度差问题
    // 与前面用long long实现的其他算法在数据较大时结果差异会比较大
}

int main()
{
    int i;
    for(i=1;i<=10;i++)cout<<get_fib_by_GF(i)<<endl;
    
}