#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>

#define eps 1e-8

using namespace std;
const int maxn=20+5;

struct Matrix
{
	int m,n;
	double element[maxn][maxn];
	
	Matrix():m(0),n(0)					//Ĭ�Ϲ��캯��
	{
		int i,j;
		for(i=0;i<maxn;i++)
		   for(j=0;j<maxn;j++)element[i][j]=0;
	}
	
	Matrix(int x,int y):m(x),n(y)  		//����mxn�� ����� 
	{
		int i,j;
		for(i=0;i<maxn;i++)
		   for(j=0;j<maxn;j++)element[i][j]=0;
	}
	
	Matrix(int k):m(k),n(k)  			//����һ��K�׵�λ���� 
	{
		m=n=k;
		int i,j;
		for(i=0;i<maxn;i++)
		   for(j=0;j<maxn;j++)element[i][j]=0;
		   
		for(i=1;i<=k;i++)element[i][i]=1;
	}
	
	void clear()
	{
		int i,j;
		for(i=1;i<=m;i++)
		   for(j=1;j<=n;j++)element[i][j]=0;
		m=0;n=0;
	}
	
	void assignment()   			//����һ������ 
	{
		scanf("%d %d",&m,&n);
		int i,j;
		for(i=1;i<=m;i++)
		   for(j=1;j<=n;j++)scanf("%lf",&element[i][j]);  
	}
	
	Matrix operator + (const Matrix& B)const
	{
		Matrix C;
		if(m!=B.m||n!=B.n){printf("wrong\n");return C;}
		
		C.m=m;C.n=n;
		int i,j;
		for(i=1;i<=m;i++)
		   for(j=1;j<=n;j++)
		      C.element[i][j]=element[i][j]+B.element[i][j];
		      
		return C;
	} 
	
	Matrix operator - ()const   		//ȡ������ 
	{
		Matrix B;
		B.m=m;B.n=n;
		int i,j;
		for(i=1;i<=m;i++)
		   for(j=1;j<=n;j++)
		      B.element[i][j]=-element[i][j];
		return B;
	}
	
	Matrix operator - (const Matrix& B)const
	{
		Matrix C;
		if(m!=B.m||n!=B.n){printf("wrong\n");return C;}
		
		C.m=m;C.n=n;
		int i,j;
		for(i=1;i<=m;i++)
		   for(j=1;j<=n;j++)
		      C.element[i][j]=element[i][j]-B.element[i][j];
		      
		return C;
	}
	
	Matrix operator * (const double& t)const  //����
	{
		Matrix A;
		A.m=m;A.n=n;
		for(int i=1;i<=m;i++)
		   for(int j=1;j<=n;j++) A.element[i][j]=element[i][j]*t;
		return A;
	}
	
	Matrix operator * (const Matrix& B)const  //������� 
	{
		Matrix C;
		if(n!=B.m){printf("wrong\n");return C;}
		
		C.m=m; C.n=B.n;
		int i,j,k;
		for(i=1;i<=m;i++)
		   for(j=1;j<=C.n;j++)
		      for(k=1;k<=n;k++)
		         C.element[i][j]+=element[i][k]*B.element[k][j];

		return C;	 
	}
	
	
	Matrix inverse()const       				//������������ 
	{
		Matrix E(m);
		if(m!=n){printf("wrong\n");return E;}  	//ȷ��Ϊ���� 
		
		Matrix A(*this);
		double value = 1;
		int rank=m;
		double temp;
        int i,j;

        for(int k=1;k<=rank;k++)  		//ͨ�� �б任 �����������ͷ��� ��ͬʱ������������ʽ��ֵ 
        {
            
            if(fabs(A.element[k][k]) < eps)			//k:��ǰ����ָ��
            {
                value = -value;
                for(i=k+1;i<=rank;i++)				//i������ʽ��ָ��
                {
                    if(fabs(A.element[i][k])>eps)
                    {
                        for (j=1;j<=rank;j++)		//j������ʽ��ָ��
                        {   
							//j��1��ʼ�������Ǵ�k��ʼ ,����������ʽ���� 
                            swap(A.element[k][j], A.element[i][j]);
                            swap(E.element[k][j], E.element[i][j]);
                        }
                        break;
                    }
                }
            }

            value *= A.element[k][k];
            if (fabs(value) < eps) {printf("wrong\n");return E;}

            for(i=k+1;i<=rank;i++)
            {
                if((fabs(A.element[i][k]) > eps))
                {
                    temp = A.element[i][k] / A.element[k][k];
                    for(j=1;j<=rank;j++)
                    {   
						//j��1��ʼ�������Ǵ�k��ʼ ,����������ʽ���� 
                        A.element[i][j] -= A.element[k][j] * temp;
                        E.element[i][j] -= E.element[k][j] * temp;
                    }
                }
            }
        }
        
        for(int k=rank;k>=1;k--)
		{
			for(i=k-1;i>=1;i--)
            {
                if((fabs(A.element[i][k]) > eps))
                {
                    temp = A.element[i][k] / A.element[k][k];
                    A.element[i][k]=0;
                    for(j=1;j<=rank;j++)
					{
						E.element[i][j] -= E.element[k][j] * temp;
					} 
                    
                    
                }
            }

            for(j=1;j<=rank;j++)E.element[k][j]/=A.element[k][k];
            A.element[k][k]=1;
		} 
        
        return E;
	}

	
	Matrix operator ^ (int k)  //K���� 
	{
		Matrix A(*this);
		Matrix ans(m);
		while(k)
		{
			if(k&1)A=ans*A;
			A=A*A;
			k>>=1;
		}
		return ans;
	}
	
	
	Matrix Row_echelon()const // �н����ξ��� 
	{
		Matrix A(*this);
		int i,j,k;
		int x,y;
		double temp;
		
		x=y=1;
		
		
		while(x<=m&&y<=n)
		{
			if(fabs(A.element[x][y])<eps)
			{
				for(i=x+1;i<=m;i++)
				{
					if(fabs(A.element[i][y])>=eps)
					{
						for(j=y;j<=n;j++)
						{
							swap(A.element[x][j],A.element[i][j]);
						}
						break;
					}
				}
				
				if(fabs(A.element[x][y])<eps)
				{
					y++;
					continue;
				}
			}
			
			for(i=x+1;i<=m;i++)
			{
				temp=A.element[i][y]/A.element[x][y];
				
				for(j=y;j<=n;j++)
				{
					A.element[i][j]-=A.element[x][j]*temp;
				}
			}
			
			//A.Print();cout<<endl;
			
			x++;y++;	
		}
		return A; 
	}
	
	Matrix Basic_solution()const  //��������ϵ 
	{
		Matrix A=Row_echelon();
		
		int i,j;
		int k;
		double temp;
		
		for(i=1;i<=n;i++) A.element[0][i]=i;//������� 
		
		for(k=1;k<=m&&k<=n;k++)
		{
			if(fabs(A.element[k][k])<eps)
			{
				for(i=k+1;i<=n;i++)
				{
					if(fabs(A.element[k][i])>=eps)
					{
						for(j=0;j<=m;j++)
						{
							swap(A.element[j][k],A.element[j][i]);  //����k,j���У������������ 
						}
						break;
					}
				}
				
				if(fabs(A.element[k][k])<eps)
				{
					break;
				}
			}
			
		}
		cout<<endl;
		A.Print(); 
		cout<<endl;
		// ��ʱ�ɵó� R(A)=k-1;
		 
		int R=k-1; //�������
		
		for(k=R;k>=1;k--)
		{
			for(i=1;i<k;i++)
			{
				temp=A.element[i][k]/A.element[k][k];
				
				for(j=R+1;j<=n;j++)
				{
					A.element[i][j]-=A.element[k][j]*temp;
				} 
				A.element[i][k]=0;
			}
			
			for(j=R+1;j<=n;j++)A.element[k][j]/=A.element[k][k];
			A.element[k][k]=1;	   
		} 
		
		return A;
		
		
		
	}
	
	void Print()const          //������� 
	{
		if(m==0||n==0){printf("wrong\n");return;}
	    int i,j;
        for(i=1;i<=m;i++)
        {
    	   for(j=1;j<=n;j++)printf("%10lf ",element[i][j]);
    	   //for(j=1;j<=n;j++)cout<<element[i][j]<<' ';
    	   putchar('\n');
	    }
	    return;
	}	
	
};
ostream& operator << (ostream &out,const Matrix& A)  //����� 
{ 
    if(A.m==0||A.n==0){printf("wrong\n");return out;}
	int i,j;
    for(i=1;i<=A.m;i++)
    {
    	for(j=1;j<=A.n;j++)cout<<A.element[i][j]<<' ';
    	putchar('\n');
	}
	return out;
} 

Matrix operator * (double t, const Matrix& B )  //����
{
	Matrix A(B);
	for(int i=1;i<=A.m;i++)
		for(int j=1;j<=A.n;j++) A.element[i][j]=B.element[i][j]*t;
	return A;
}

 

void Translate(Matrix& ans)
{
	double X[25];
	int m=ans.m,n=ans.n;
	int i,j;
	int k=1;
	while(ans.element[k][k]==1)k++;
	int R=k-1;
	
	printf("free variable:");
	for(i=R+1;i<=n;i++)
	{
		printf("X%d ",(int)ans.element[0][i]);
	}
	
	cout<<endl;
	
	for(i=R+1;i<=n;i++)
	{
		for(j=1;j<=n;j++)X[j]=0;
		 
		printf("X%d=1 :",(int)ans.element[0][i]);
		X[(int)ans.element[0][i]]=1;
		for(j=1;j<=R;j++)
		{
			X[(int)ans.element[0][j]]=-ans.element[j][i];
		}
		
		for(j=1;j<=n;j++)printf("%10lf ",X[j]);
		putchar('\n');
	}
} 

