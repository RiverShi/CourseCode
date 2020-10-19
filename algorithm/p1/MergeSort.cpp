#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e7;

void Merge(int array[], int L, int Mid, int R)  // 有序数组合并操作 [L,Mid], [Mid+1,R]
{
    static const int MAXN = 2e8+10;
    static int Temp[MAXN];

    int i = L, j = Mid+1, k = L;
    while(i <= Mid && j <= R)
    {   //比较，取小
        if(array[i] <= array[j])Temp[k++] = array[i++];
        else Temp[k++] = array[j++];
    }
    while(i <= Mid)Temp[k++] = array[i++];
    while(j <= R) Temp[k++] = array[j++];   //把剩余的放入辅助数组
    for(i = L; i <= R; i++)array[i] = Temp[i];  //把合并后的段拷贝回原数组
}

void MergeSort(int array[], int L, int R)  //递归实现的归并排序
{
    if(L >= R)return;
    int Mid = (L+R) >> 1;
    MergeSort(array, L, Mid);
    MergeSort(array, Mid+1, R);
    Merge(array, L, Mid, R);
}

void MergeSort_NoRec(int array[], int L, int R) //非递归实现的归并排序
{
    int len = R-L+1;
    int i, st, Mid, ed;
    for(i = 0; (1<<i) <= len; i++)    //从小段开始归并，直到将整个数组归并
    {
        for(st = L; st <= R; st += 1<<(i+1) )
        {
            Mid = st-1 + (1<<i);
            ed = st-1 + (1<<(i+1)); 
            if(Mid > R) Mid = R;
            if(ed > R) ed = R;
            Merge(array, st, Mid, ed);
        }
    }
}

int a[50000],b[50000],c[50000];

int test()
{
	int cnt = 0, n, i, j;
	while(cnt++ < 10000)
	{
		n=rand()%10000;
		for(i=1;i<=n;i++)a[i] = b[i] = c[i] = rand();
		
		MergeSort_NoRec(a,1,n);
		sort(b+1,b+1+n);
		cout<<n<<endl;
		//getchar();
		for(i=1;i<=n;i++)
		{
			//printf("%d\n",a[i]-b[i]);
			if(a[i] != b[i])
			{
				printf("Something Wrong!\n");
				freopen("wrong7.txt","w",stdout); 
				printf("%d  %d\n", n);
				for(j = 1; j <= n; j++)printf("%d ",c[j]);
				putchar('\n');
				for(j = 1; j <= n; j++)printf("%d ",a[j]);
				putchar('\n');
				for(j = 1; j <= n; j++)printf("%d ",b[j]);

				return 0;
			}
		}
		printf("OK!\n");
	}
	return 1;
}

int main()
{
    if(!test())return 0;
}

