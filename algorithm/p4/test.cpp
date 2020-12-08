#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include <algorithm>
#include <bitset>

using namespace std;

char bin_code[50];
char bin_inv[50];

void to_bin(int x)
{
    int pos = 0, front, back;
    while(x)
    {
        bin_inv[pos++] = '0'+ (x&1);
        x >>= 1;
    }
    for(front = 0, back = pos-2; back >= 0; front++,back--)
    {
        bin_code[front] = bin_inv[back];
    }
    bin_code[pos-1] = '\0';
}

int main()
{
    to_bin(10);
    printf("%s \n",bin_code);
    return 0;
}