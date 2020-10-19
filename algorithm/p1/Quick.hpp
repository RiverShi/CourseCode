#include <iostream>
#include <cstdio>
#include <cstdlib>

#define MAX(a, b)       (((a) > (b) ) ? (a) : (b))
#define MIN(a, b)       (((a) < (b) ) ? (a) : (b))
#define MID(a,b,c)      (MAX(a,b)>c? MAX(MIN(a,b),c) : MIN(MAX(a,b),c))

using namespace std;
void Quick_sort(int array[], int L, int R, int Method)
{
	int Mid=array[(L+R)/2],temp;
	int a,b,c;
    int i,j;

	switch (Method)  // 1:首元素  2：三数取中  3：随机划分  4：不同取大
	{
	case 1:
		Mid=array[L];
		break;

	case 2:
		a = array[L];
        b = array[R];
        c = array[(L+R)>>1];
        Mid = MID(a,b,c);
		break;

	case 3:
		a = L + rand()%(R-L+1);
		Mid = array[a];
		break;

	case 4:
		Mid = array[L];
        for(i = L+1; i <= R; i++)
            if(array[i] != Mid) {Mid = MAX(array[i],Mid); break;}
        if(i > R) return;
		break;
	
	default:
		Mid = array[(L+R)>>1];
		break;
	}


	int x=L,y=R;
	while(x<=y)
	{
		while(array[x]<Mid) x++;
		while(array[y]>Mid) y--;		// 与划分值比较
		if(x<=y)
		{
			temp=array[x]; array[x]=array[y]; array[y]=temp; //交换变量值
            x++; y--;
		}	
	}
	if(L<y) Quick_sort(array, L, y, Method);
    if(x<R) Quick_sort(array, x, R, Method);
}