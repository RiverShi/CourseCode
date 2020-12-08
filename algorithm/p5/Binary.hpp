#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

inline void du(int &d) 
{ 
    char t=getchar();bool Mark=false; 
    for(;t<'0'||t>'9';t=getchar())if(t=='-')Mark=!Mark; 
    for(d=0;t>='0'&&t<='9';t=getchar())d=d*10+t-'0'; 
    if(Mark)d=-d; 
}

bool binary_find(int* array,int L,int R,int key)
{
	int Mid;
	while(L<=R)
	{
		Mid=(L+R)>>1;
		if(array[Mid]==key)return true;
		if(array[Mid]<key)L=Mid+1;
		else R=Mid-1;
	}
	return false;
}

int binary_upper_find(int* array,int L,int R,int key)
{
	int Mid;
	while(L<=R)
	{
		Mid=(L+R)/2;
		if(array[Mid]<=key)L=Mid+1;
		else R=Mid-1;
	}
	return L;  //大于key的第一个数的位置 
}

int binary_lower_find(int* array,int L,int R,int key)
{
	int Mid;
	while(L <= R)
	{
		Mid=(L+R)>>1;
		if(array[Mid] < key)L=Mid+1;
		else R=Mid-1;
	}
	return L;  //大于等于key的第一个数的位置 
}

bool check(int x)
{
	return true;
} 

int binary_answer(int L,int R)  //仅仅只是一种示例 
{
	int Mid;
	while(L <= R)
	{
		Mid=(L+R)>>1;
		if(check(Mid))R=Mid-1;  //求满足.....的最小值 
		else L=Mid+1;
	}
	return L;
}



// int a[20]={0,4,68,2,4,56,65,9,9,9,9,9,9,9,9,9,9,9,9,9};

// int main()
// {
// 	sort(a+1,a+1+19);
	
// 	cout<<binary_upper_find(a,1,19,9);
	
// 	return 0; 
// } 

