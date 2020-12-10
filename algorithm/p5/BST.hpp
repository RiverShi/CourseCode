#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

struct BST_node
{
    int val;    //节点值
    int times;  //这个值出现的次数
    BST_node *Left, *Right;

    BST_node():val(0),times(0),Left(NULL),Right(NULL){}
};

BST_node *BST_root = NULL;

int BST_find(BST_node *&root, int num); 
BST_node* BST_find(BST_node *&root, int num, int& acc);
BST_node* BST_insert(BST_node *&root, int num);
void visit(BST_node *&root,  int array[]);
void visit(BST_node *&root, int array[], int& index);

// 定义此BST的左子树上的节点值小于根节点，右子树上的值大于根节点，相等的值用times域表示

BST_node* BST_insert(BST_node *&root, int num)    //向根节点为root的一颗BST中插入一个值为num的项
{
    if(!root)   //空树
    {
        root = new BST_node;
        root->val = num;
        root->times = 1;
        return root;
    }

    if(num < root->val)return BST_insert(root->Left, num);
    if(num > root->val)return BST_insert(root->Right, num);
    root->times++;
    return root;
}


int BST_find(BST_node *&root, int num)
{
    int acc = 0;
    BST_find(root, num, acc);
    return acc;
}

// BST_node* BST_find(BST_node *&root, int num)
// {
//     if(!root){return NULL;}
//     if(num < root->val)return BST_find(root->Left, num, acc);
//     if(num > root->val)return BST_find(root->Right, num, acc);
//     return root;
// }

// BST_node* BST_find(BST_node *&root, int num, int &acc)
// {
//     acc += 0; //递归传参惩罚
//     acc++;
//     if(!root){return NULL;}
//     acc++;
//     if(num < root->val)return BST_find(root->Left, num, acc);
//     acc++;
//     if(num > root->val)return BST_find(root->Right, num, acc);
//     return root;
// }

BST_node* BST_find(BST_node *&root, int num, int &acc)
{
    auto node = root;
    while(node != NULL)
    {
        acc++;
        if(num < node->val){acc++;node = node->Left;}
        else 
        {
            acc++;
            if(num > node->val){acc++;node = node->Right;}
            else return node;
        }
        acc++;
    }
    return NULL;
}


//删除可分为删除某个数（一次），删除某个数（所有），删除某个节点（给出地址）
//可以假删除，更改times域的值即可，times == 0可认为节点不存在
//此处只写删除已给出指针的指定节点的实现
//要真的物理删除这个节点还有点麻烦，加一个Father域可能好实现一些
//这里还是假删除，删掉另一个节点，将这个节点修改
//将这个节点更改为左子树的最大值或右子树的最小值，删去左子树的最大值或右子树的最小值
//没有父节点域，当这个节点为叶节点时，没法把这个节点的父亲和它的联系断掉啊
//算了，不写这种了
//算了，不写删除了，这个实验里面也用不到删除。
//还是写个假删除把
void BST_delete(BST_node *&root, int key)
{
    auto node = root;
    while(node != NULL)
    {
        if(key == node->val)
        {
            node->times--;
            if(node->times < 0)node->times = 0;
            return;
        }
        if(key < node->val)node = node->Left;
        else node = node->Right;  
    }
    return;
}

//中序遍历输出
void visit(BST_node *&root,  int array[])
{
    int index = 0;
    visit(root, array, index);
}

void visit(BST_node *&root, int array[], int& index)
{
    if(root->Left != NULL)visit(root->Left, array, index);
    index++;
    array[index] = root->val;
    if(root->Right != NULL)visit(root->Right, array, index);
}




