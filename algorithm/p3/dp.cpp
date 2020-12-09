#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define pii pair<int,int>

const int maxn = 1000+10;
const int inf = 1e9;
int n, m;

int dis1[maxn],dis2[maxn];
int mp[maxn][maxn];

int acc1, acc2;


vector<pii> G[maxn];

void addedge(int u, int v, int w)
{
    G[u].push_back(make_pair(v,w));
    mp[u][v] = w;
}

// void dp(int s, int t)
// {
//     if(s == t){dis1[t] = 0; return;}
//     if(dis1[s] < inf)return;
//     int u = s, v, w;
//     for(auto& p : G[s] )
//     {
//         v = p.first;
//         w = p.second;
//         dp(v,t);
//         dis1[u] = min(dis1[v]+w, dis1[u]);  
//     }
// }

void dp(int s, int t)
{
    acc1++;
    if(s == t){acc1++; dis1[t] = 0; return;}
    acc1++;
    if(dis1[s] < inf)return;
    acc1++;
    int u = s, v, w;
    acc1++;
    for(auto& p : G[s] )
    {
        acc1++;
        v = p.first;
        acc1++;
        w = p.second;
        acc1+=4;
        dp(v,t);
        acc1 += 2;
        if(dis1[v]+w < dis1[u]){acc1 ++; dis1[u] = dis1[v]+w;}
    }
}

void dp_mp(int s, int t)
{
    acc2++;
    if(s == t){acc2++; dis2[t] = 0; return;}
    acc2++;
    if(dis2[s] < inf)return;
    acc2++;
    int u = s, v, w, i;
    acc2 += 2;
    for(v = 1; v <= n; i++)
    {
        acc2++;
        if(mp[u][v] == inf) continue;
        acc2++;
        w = mp[u][v];
        acc2 += 4;
        dp_mp(v,t);
        acc2 == 2;
        if(dis2[v]+w < dis2[u]){acc2++; dis2[u] = dis2[v]+w;}
    }
}

void pre()
{
    int i, j;
    for(i = 0; i <= maxn; i++)dis1[i] = dis2[i] = inf;
    for(i = 0; i <= maxn; i++)mp[i][i] = 0;
    for(i = 0; i <= maxn; i++)
        for(j = 0; j <= maxn; j++)
            mp[i][j] = inf;
    acc1 = acc2 = 0;
}


int main()
{
    return 0;
    freopen("data1.in","r",stdin);
    scanf("%d %d",&n,&m);
    cin >> n >> m;
    int i,u,v,w;
    for(i = 1; i <= m; i++)
    {
        scanf("%d %d %d",&u,&v,&w);
        addedge(u,v,w);
    }
    int s,t;
    scanf("%d %d",&s,&t);
    
    pre();

    dp(s,t);
    dp_mp(s,t);

    printf("邻接链表 dis = %d \n邻接矩阵 dis = %d\n\n",dis1[s],dis2[s]);
    printf("count1 = %d\ncount2 = %d\n\n",acc1,acc2);

} 