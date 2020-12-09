#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define pii pair<int,int>

const int maxn = 10000;

int dis[maxn+10];


vector<pii> G[maxn];

void addedge(int u, int v, int w)
{
    G[u].push_back(make_pair(v,w));
}

void dp(int s, int t)
{
    if(s == t){dis[t] = 0; return;}
    int u = s, v, w;
    for(auto& p : G[s] )
    {
        v = p.first;
        w = p.second;
        dp(v,t);
        dis[u] = min(dis[v]+w, dis[u]);  
    }
}


int main()
{
    
}