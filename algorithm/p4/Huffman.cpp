#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include <algorithm>
#include <bitset>

using namespace std;

string file_path = "";

struct Haffuman_node
{
    int ch;
    Haffuman_node *Left, *Right;

    Haffuman_node():ch(0),Left(NULL),Right(NULL){}
};

map<int,int> ch_count;      //字符出现的次数统计
map<char,int> code_book;    //字符的编码对应
priority_queue<int, vector<int>, greater<int> > heap;   //没用上
Haffuman_node Haffuman_tree_root;   //建立的haffuman树，建树过程得到code_book, decode的过程中当作字典树用于查询
int tot = 0, cnt = 0;
int freq[10000+10];         //字符出现频次排序

void file_count();      //字符计数
void make_book(Haffuman_node* node, int L, int R, int sum, int code); //建树，code表示区间的编码前缀
void encode(char ch);    //编码
void decode();          //解码（对一个长二进制串）

int main()
{
    //freopen("result.txt","w",stdout);
    file_count();

    int key, val, mix;
    cnt = 0;
    for(auto it = ch_count.begin(); it != ch_count.end(); it++)
    {
        printf("%d %d\n",it->first, it->second);
        key = it->first;
        val = it->second;
        mix = (val<<8) + key;   //混合信息
        //heap.push(mix);
        freq[++cnt] = mix;
    }

    sort(freq+1, freq+1+cnt, [](int a, int b){return a > b;});

    cout<<endl;
    for(int i = 1; i <= cnt; i++)
    {
        int ch = freq[i]&(255);
        int times = freq[i]>>8;
        printf("%d %d\n",ch,times);
    }

    // 去除前导0和首1才是字符编码
    make_book(&Haffuman_tree_root, 1, cnt, tot, 1);

    for(auto it = code_book.begin(); it != code_book.end(); it++)
    {
        printf("%#x %d\n",it->first, it->second);
    }
}

void file_count()
{
    FILE* fp=fopen("test.txt","rb");
    //freopen("test.txt","rb",stdin);
    int t = fgetc(fp);
    tot = 0;
    while(t != EOF)
    {
        //putchar(t);
        //putchar('\n');
        ch_count[t]++;
        tot++;
        t = fgetc(fp);
    }
    fclose(fp);
    cout<<tot<<endl;

}

void make_book(Haffuman_node* node, int L, int R, int sum, int code) //code表示区间的编码前缀
{
    //printf("%d\t%d\t%d\t%d\n",L,R,sum,code);
    if(code < 0)return;
    if(L == R)  //区间只有一个值，确定编码，返回
    {
        int ch = freq[L]&(255);
        code_book[ch] = code;  //字符ch对应编码为code
        node->ch = ch;
        printf("coding %#x\t",ch);
        bitset<10> bin(code);
        cout<<bin;
        putchar('\n');
        return;
    }

    node->Left  = new Haffuman_node;
    node->Right = new Haffuman_node;

    //寻找平分点
    int acc = 0, i;
    for(i = L; i <= R; i++)
    {
        acc += freq[i]>>8;
        if(acc*2 >= sum)break;
    }
    int Mid = i, m = freq[Mid]>>8;
    if(2*acc-sum > sum+2*m-2*acc) {Mid = Mid -1; acc-=m;}

    //递归建树
    make_book(node->Left, L, Mid, acc,code<<1);
    make_book(node->Right, Mid+1, R, sum-acc,(code<<1)|1);
}
