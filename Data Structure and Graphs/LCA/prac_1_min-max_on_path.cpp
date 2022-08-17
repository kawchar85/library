//https://vjudge.net/problem/SPOJ-DISQUERY

#include<bits/stdc++.h>
using namespace std;
#define maxN 20
#define MAX 100001

vector< pair<int, int> > adj[MAX];
int lvl[MAX];
int LCA[MAX][maxN+1],min_w[MAX][maxN+1],max_w[MAX][maxN+1];

void DFS(int v, int p)
{
    LCA[v][0]=p;
    for(int i=0; i<adj[v].size(); i++)
    {
        int x=adj[v][i].first;
        int cost=adj[v][i].second;
        if(x==p) continue;
        lvl[x]=lvl[v]+1;
        min_w[x][0]=max_w[x][0]=cost;
        DFS(x, v);
    }
}
void init(int N)
{
    for(int j=1; j<=maxN; j++)
    {
        for(int i=1; i<=N; i++)
        {
            LCA[i][j]=-1;
            min_w[i][j]=INT_MAX;
            max_w[i][j]=INT_MIN;
        }
    }

    min_w[1][0]=max_w[1][0]=lvl[1]=0;
    DFS(1, -1);
    for(int j=1; j<=maxN; j++)
    {
        for(int i=1; i<=N; i++)
        {
            if(~LCA[i][j-1])
            {
                int p = LCA[i][j-1];
                LCA[i][j]=LCA[p][j-1];
                min_w[i][j]=min(min_w[i][j-1], min_w[p][j-1]);
                max_w[i][j]=max(max_w[i][j-1], max_w[p][j-1]);
            }
        }
    }

}

pair<int, int> find_lca(int a, int b)
{
    if(lvl[a]>lvl[b])   swap(a,b);
    int d=lvl[b]-lvl[a];
    int mx=INT_MIN, mn=INT_MAX;
    while(d>0)
    {
        int j = log2(d);
        mx=max(mx, max_w[b][j]);
        mn=min(mn, min_w[b][j]);
        b=LCA[b][j];
        d-=(1<<j);
    }
    if(a==b)    return {mn, mx};

    for(int j=maxN; ~j; j--)
    {
        if(~LCA[a][j] && (LCA[a][j]!=LCA[b][j]))
        {
            mx=max(mx, max_w[a][j]);
            mn=min(mn, min_w[a][j]);
            mx=max(mx, max_w[b][j]);
            mn=min(mn, min_w[b][j]);
            a=LCA[a][j];
            b=LCA[b][j];
        }
    }
    mx=max(mx, max_w[a][0]);
    mn=min(mn, min_w[a][0]);
    mx=max(mx, max_w[b][0]);
    mn=min(mn, min_w[b][0]);
    return {mn, mx};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n,i,j,q,x,y,w;
    cin>>n;
    for(i=1; i<n; i++)
    {
        cin>>x>>y>>w;
        adj[x].push_back({y,w});
        adj[y].push_back({x,w});
    }
    init(n);
    cin>>q;
    while(q--)
    {
        cin>>x>>y;
        pair<int, int> ans = find_lca(x,y);
        cout<<ans.first<<" "<<ans.second<<"\n";
    }


    return 0;
}
