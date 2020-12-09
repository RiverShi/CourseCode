#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>

#include "BST.hpp"
#include "Binary.hpp"

using namespace std;


int A[2000],B[2000];
int arr[2000];
BST_node *treeA = NULL;
BST_node *treeB = NULL;

int main()
{
    int i;
    for(i = 1; i <= 1024; i++)A[i] = B[i] = 2*i-1;
    random_shuffle(B+1,B+1+1024);

    //建树
    for(i = 1; i <= 1024; i++)BST_insert(treeA, A[i]);
    for(i = 1; i <= 1024; i++)BST_insert(treeB, B[i]);

    int sumA = 0, sumB = 0;
    for(i = 1; i <= 1024; i++)
    {
        sumA += BST_find(treeA,A[i]);
        sumB += BST_find(treeB,A[i]);
    }

    int sumAf = 0, sumBf = 0;
    for(i = 1; i <= 1024; i++)
    {
        sumAf += BST_find(treeA,A[i]+1);
        sumBf += BST_find(treeB,A[i]+1);
    }

    double aveA,aveB,aveAf,aveBf;
    aveA = (double)sumA/1024;
    aveB = (double)sumB/1024;
    aveBf = (double)sumBf/1024;
    aveAf = (double)sumAf/1024;
    
    printf("aveA = %lf\naveB = %lf\naveAf = %lf\naveBf = %lf\n",aveA,aveB,aveAf,aveBf);

    visit(treeB, arr);

    int sum = 0, sumf = 0;
    for(i = 1; i <= 1024; i++)
    {
        sum += binary_find(arr,1,1024,A[i]);
        sumf += binary_find(arr,1,1024,A[i]+1);
    }
    double ave, avef;
    ave = (double)sum/1024;
    avef = (double)sumf/1024;

    printf("ave = %lf\navef = %lf\n",ave,avef);
    
    return 0;
}
