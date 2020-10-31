#include <stdio.h>
#include <windows.h>

#define uLL unsigned long long


using namespace std;
#define DLLEXPORT extern "C" __declspec(dllexport)



DLLEXPORT uLL get_fib_by_DT(int n)        //递推算法 DiTui
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
