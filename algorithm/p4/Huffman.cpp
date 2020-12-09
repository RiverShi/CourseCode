#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#include <algorithm>
#include <bitset>

using namespace std;

struct Haffuman_node
{
    int ch;
    Haffuman_node *Left, *Right;

    Haffuman_node():ch(0),Left(NULL),Right(NULL){}
};

map<int,int> ch_count;      //字符出现的次数统计
map<int,int> code_book;    //字符的编码对应
priority_queue<int, vector<int>, greater<int> > heap;   //没用上
Haffuman_node* Haffuman_tree_root = new Haffuman_node;   //建立的haffuman树，建树过程得到code_book, decode的过程中当作字典树用于查询
int ch_tot = 0, ch_spec = 0;        //字符总个数、字符种类数
int freq[10000+10];                 //字符出现频次排序
char bin_code[50];
char bin_inv[50];
int node_cnt = 0;

void get_freq(char*);      //字符计数
void make_book(Haffuman_node* node, int L, int R, int sum, int code); //建树，code表示区间的编码前缀
void encode(int ch);    //编码
int decode(FILE* file);          //解码（对一个长二进制串）
void to_bin(int);

void lookup(Haffuman_node*);

char source_path[] = "haff_no_zh_cn.cpp";


int main()
{
    freopen("result1.txt","w",stdout);
    get_freq(source_path);
    
    printf("文件字符总数：%d\n",ch_tot);
    printf("文件字符种类数：%d\n",ch_spec);

    for(int i = 1; i <= ch_spec; i++)
    {
        int ch = freq[i]&(255);
        int times = freq[i]>>8;
        printf("%#x \t %d\n",ch,times);
    }

    printf("\n\n生成code_book\n");
    make_book(Haffuman_tree_root, 1, ch_spec, ch_tot, 1);  //建树， 编码去除前导0和首1才是字符的haffuman编码

    printf("\n\n遍历code_book\n");
    for(auto it = code_book.begin(); it != code_book.end(); it++)
    {
        printf("%#x\t  %d  \t(1)",it->first, it->second);
        to_bin(it->second);
        printf("%s \n",bin_code);
    }

    //遍历haffman树
    printf("\n\n遍历haffman树\n");
    lookup(Haffuman_tree_root);
    printf("共%d个结点\n",node_cnt);

    //文件编码
    FILE* source = fopen(source_path,"rb");
    FILE* encode_result = fopen("encode_result1.txt","w");
    FILE* decode_result = fopen("decode_result1.txt","w");

    setbuf(encode_result,NULL);

    printf("\n\n编码\n");
    int ch;
    for(ch = fgetc(source); ch != EOF; ch = fgetc(source))
    {
        encode(ch);
        fprintf(encode_result,"%s",bin_code);
        putchar(ch);
        printf("\n%s\n",bin_code);
    }
    fflush(encode_result);
    fclose(source);
    fclose(encode_result);

    //文件解码测试
    encode_result = fopen("encode_result1.txt","rb");
    
    setbuf(encode_result,NULL);
    printf("\n\n解码\n");

    while(ch = decode(encode_result))
    {
        fprintf(decode_result,"%c",char(ch));
        
        putchar('\n');
        cout << ch <<endl;
        putchar(ch);
        putchar('\n');
    }

    fflush(encode_result);
    fclose(encode_result);
    fclose(decode_result);

}

int len = 0;
char line[100];
void lookup(Haffuman_node* node)
{
    len++;
    node_cnt++;
    if(node->ch != 0 )
    {
        line[len]='\0';
        printf("%s \t\t %#x\n",line+1,node->ch);
        len--;
        return;
    }
    line[len]='0';
    lookup(node->Left);
    line[len]='1';
    lookup(node->Right);
    len--;
    return;
}

void to_bin(int x)
{
    int pos = 0, front, back;
    while(x){bin_inv[pos++] = '0'+ (x&1);x >>= 1;}
    for(front = 0, back = pos-2; back >= 0; front++,back--)bin_code[front] = bin_inv[back];
    bin_code[pos-1] = '\0';
}

void encode(int ch)
{
    int code = code_book[ch];
    to_bin(code);
}

int decode(FILE* file)
{
    Haffuman_node *node = Haffuman_tree_root;
    for(int ch = fgetc(file); ch != EOF; ch = fgetc(file))
    {
        putchar(ch);
        if(ch == '0')node = node->Left;
        else node = node->Right;
        if(node->ch != 0)return node->ch;
    }
    return 0;
}

void make_book(Haffuman_node* node, int L, int R, int sum, int code) //code表示区间的编码前缀
{
    //printf("%d\t%d\t%d\t%d\n",L,R,sum,code);
    //if(code < 0)return;
    if(L == R)  //区间只有一个值，确定编码，返回
    {
        int ch = freq[L]&(255);
        code_book[ch] = code;  //字符ch对应编码为code
        node->ch = ch;
        to_bin(code);
        printf("coding\t%#x\t %s\t %c\n",ch,bin_code,char(node->ch));
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

void get_freq(char* source_file)
{
    FILE* fp=fopen(source_file,"rb");
    int t = fgetc(fp);
    ch_tot = 0;
    while(t != EOF)
    {
        ch_count[t]++;
        ch_tot++;
        t = fgetc(fp);
    }
    fclose(fp);

    int key, val, mix;
    ch_spec = 0;
    for(auto it = ch_count.begin(); it != ch_count.end(); it++)
    {
        //printf("%d %d\n",it->first, it->second);
        key = it->first;
        val = it->second;
        mix = (val<<8) + key;   //混合信息
        //heap.push(mix);
        freq[++ch_spec] = mix;
    }

    sort(freq+1, freq+1+ch_spec, [](int a, int b){return a > b;});

    // cout<<endl;
    // for(int i = 1; i <= ch_spec; i++)
    // {
    //     int ch = freq[i]&(255);
    //     int times = freq[i]>>8;
    //     printf("%d %d\n",ch,times);
    // }
}