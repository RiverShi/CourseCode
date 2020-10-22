#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

#define ldb long double
#define uLL unsigned long long


/*
    大数也就图一乐,精度问题没法解决
    不过只是比较时间复杂度倒是没什么
    pow的参数类型是double，用 long double保存数据是没有意义的, 到 10^308也就inf了，精度也不会更高
    不如就自然溢出吧
*/

ldb pow_ldb(ldb a, int x)
{
    ldb ans = 1;
    while(x)
    {
        if(x&1) ans = ans*a;
        a *= a;
        x >>= 1;
    }
    return ans;
}


double fib_GF(int n)
{
    static ldb sqrt_5 = sqrt(5);
    return ( pow_ldb((1+sqrt_5)/2, n)-pow_ldb((1-sqrt_5)/2, n) ) / sqrt_5;
}


uLL fib[10000];


int main()
{
    for(int i = 1; i <= 2000; i++)
    {
        cout<<fib_GF(i)<<endl;
    }
    //fib[1] = fib[2] = 1;
    //for(int i = 3; i <= 100; i++)fib[i] = fib[i-1] + fib[i-2],cout<<fib[i]<<endl;
}