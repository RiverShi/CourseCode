#include <bits/stdc++.h>
#include "Merge.hpp"
#include "Quick.hpp"

using namespace std;

const int N1 = 1e4;
const int N2 = 1e5;
const int N3 = 1e6;
const int N4 = 1e7;
const int N5 = 1e8;
const int N = N4*2;

int a[N+100];
int b[N+100];
int c[N+100];
int d[N+100];
int e[N+100];
int f[N+100];

void output(int n, int flag = 1)
{
    int i, t1, t2, t3, interval;

    //归并、递归
    printf("归并，递归:  \t\t\t");
    t1 = clock();
    MergeSort(a,1,n);
    t2 = clock();
    interval = t2 - t1;
    
    cout << interval << endl;

    //归并、非递归
    printf("归并，非递归:\t\t\t");
    t1 = clock();
    MergeSort_NoRec(b,1,n);
    t2 = clock();
    interval = t2 - t1;
    
    cout << interval << endl;

    //快排,1
    printf("快排，首元素:\t\t\t");
    t1 = clock();
    if(n*flag < N2 && n <= N4) Quick_sort(c,1,n,1);
    t2 = clock();
    interval = t2 - t1;
    
    cout << interval << endl;

    //快排,2
    printf("快排，三数取中:\t\t\t");
    t1 = clock();
    Quick_sort(d,1,n,2);
    t2 = clock();
    interval = t2 - t1;
    
    cout << interval << endl;

    //快排,3
    printf("快排，随机划分:\t\t\t");
    t1 = clock();
    Quick_sort(e,1,n,3);
    t2 = clock();
    interval = t2 - t1;
    
    cout << interval << endl;

    //快排,4
    printf("快排，不同取大:\t\t\t");
    t1 = clock();
    if(n*flag < N2 && n <= N4) Quick_sort(f,1,n,4);
    t2 = clock();
    interval = t2 - t1;
    
    cout << interval << endl;

}

void test(int n)
{
    printf("\n数据量 = %d \n", n);
    int i, t1, t2, t3, interval;

    cout<<"随机序列"<<endl;
    for(i = 1;i <= n; i++) a[i] = b[i] = c[i] = d[i] = e[i] = f[i] = rand()*rand();
    output(n,0);
    putchar('\n');

    cout<<"正序序列"<<endl;
    output(n);
    putchar('\n');

    cout<<"反序序列"<<endl;
    for(i = 1;i <= n; i++) a[i] = b[i] = c[i] = d[i] = e[i] = f[i] = n+1-i;
    output(n);
    putchar('\n');

    cout<<endl;

}

int main()
{
    //srand(time(NULL));

    cout<<"running"<<endl;

    //freopen("output1.txt","w",stdout);

    int i,n;
    int t1, t2, interval;

    n = 10;
    int p[15];
    for(i = 1;i <= n; i++) p[i] = rand();
    MergeSort(p,1,n);

    test(N1);
    test(N1*2);
    test(N2);
    test(N2*2);
    test(N3);
    test(N3*2);
    test(N4);
    test(N4*2);

    printf("\n\ntotal time = %d\n", clock());
}