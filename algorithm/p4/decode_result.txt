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

map<int,int> ch_count;     
map<int,int> code_book;    
priority_queue<int, vector<int>, greater<int> > heap;   
Haffuman_node* Haffuman_tree_root = new Haffuman_node;   
int ch_tot = 0, ch_spec = 0;        
int freq[10000+10];                 
char bin_code[50];
char bin_inv[50];

void get_freq(char*);     
void make_book(Haffuman_node* node, int L, int R, int sum, int code); 
void encode(int ch);    
int decode(FILE* file);   
void to_bin(int);

void lookup(Haffuman_node*);

char source_path[] = "test.cpp";


int main()
{
    freopen("result.txt","w",stdout);
    get_freq(source_path);
    make_book(Haffuman_tree_root, 1, ch_spec, ch_tot, 1);  

    for(auto it = code_book.begin(); it != code_book.end(); it++)
    {
        printf("%#x\t  %d  \t(1)",it->first, it->second);
        to_bin(it->second);
        printf("%s \n",bin_code);
    }

    lookup(Haffuman_tree_root);

    FILE* source = fopen(source_path,"rb");
    FILE* encode_result = fopen("encode_result.txt","w");
    FILE* decode_result = fopen("decode_result.txt","w");

    setbuf(encode_result,NULL);
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

    encode_result = fopen("encode_result.txt","rb");
    
    setbuf(encode_result,NULL);

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

void make_book(Haffuman_node* node, int L, int R, int sum, int code) 
{
    //printf("%d\t%d\t%d\t%d\n",L,R,sum,code);
    //if(code < 0)return;
    if(L == R)
    {
        int ch = freq[L]&(255);
        code_book[ch] = code; 
        node->ch = ch;
        to_bin(code);
        printf("coding\t%#x\t %s\t %c\n",ch,bin_code,char(node->ch));
        return;
    }

    node->Left  = new Haffuman_node;
    node->Right = new Haffuman_node;

    int acc = 0, i;
    for(i = L; i <= R; i++)
    {
        acc += freq[i]>>8;
        if(acc*2 >= sum)break;
    }
    int Mid = i, m = freq[Mid]>>8;
    if(2*acc-sum > sum+2*m-2*acc) {Mid = Mid -1; acc-=m;}

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
        mix = (val<<8) + key;   
        //heap.push(mix);
        freq[++ch_spec] = mix;
    }

    sort(freq+1, freq+1+ch_spec, [](int a, int b){return a > b;});

    cout<<endl;
    for(int i = 1; i <= ch_spec; i++)
    {
        int ch = freq[i]&(255);
        int times = freq[i]>>8;
        printf("%d %d\n",ch,times);
    }
}