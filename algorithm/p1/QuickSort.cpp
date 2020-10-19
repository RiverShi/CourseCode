#include<iostream>
#include<cstdio>
#include<ctime>
#include<algorithm>

using namespace std;

#define MAX(a, b)       (((a) > (b) ) ? (a) : (b))
#define MIN(a, b)       (((a) < (b) ) ? (a) : (b))
#define MID(a,b,c)      (MAX(a,b)>c? MAX(MIN(a,b),c) : MIN(MAX(a,b),c))

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

int a[50000], b[50000], c[50000];

int test(int method)
{
	int cnt = 0, n, i, j;
	while(cnt++ < 10000)
	{
		n=rand()%10000;
		for(i=1;i<=n;i++)a[i] = b[i] = c[i] = rand();
		
		Quick_sort(a,1,n,method);
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
				printf("%d  %d\n",method, n);
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
	return method;
}


int main()
{
	srand(time(NULL));
	
	//freopen("1004in.txt","r",stdin);
	//freopen("sort.txt","w",stdout);
	
	if(!test(1))return 0;
	if(!test(2))return 0;
	if(!test(3))return 0;
	if(!test(4))return 0;
	
}








