#include<bits/stdc++.h>
using namespace std;
#define MAX 100005
#define LOG 20

vector<int> adj[MAX];
int FT[2*MAX],in[MAX],dept[MAX];
int Timer;

int logs[2*MAX];
int table[2*MAX][LOG+1];

void cal_log(int n)
{
    logs[1]=0;
    for(int i=2; i<=n; i++)
    {
        logs[i]=logs[i/2]+1;
    }
}

int cmp(int x, int y)
{
    if(dept[x]<dept[y]) return x;
    return y;
}
//O(nLogn)
void buildSparseTable(int n)
{
    cal_log(n);
    int i,j;
    for(i=0; i<n; i++)
        table[i][0]=FT[i];

    for(j=1; j<=LOG; j++)
    {
        for(i=0; i+(1<<j)<=n; i++)
        {
            table[i][j]=cmp(table[i][j-1], table[i+(1<<(j-1))][j-1]);
        }
    }
}
//O(1)
int query(int L, int R)
{
    int j=logs[R-L+1];
    return cmp(table[L][j], table[R-(1<<j)+1][j]);
}
void DFS(int u, int p, int ht)
{
    dept[u]=ht;
    in[u]=Timer;
    FT[Timer++]=u;
    for(auto v: adj[u])
    {
        if(v==p) continue;
        DFS(v, u, ht+1);
        FT[Timer++]=u;
    }
}
void print(int n)
{
    int i;
    cout<<"\nIn={ ";
    for(i=1; i<=n; i++)
        cout<<in[i]<<" ";
    cout<<"}\n";
    
    cout<<"FT={ ";
    for(i=0; i<2*n-1; i++)
        cout<<FT[i]<<" ";
    cout<<"}\n";

    cout<<"HT={ ";
    for(i=0; i<2*n-1; i++)
        cout<<dept[FT[i]]<<" ";
    cout<<"}\n";
}
//O(nLong n)
void init(int n)
{
    DFS(1, -1, 1); 
    //print(n);
    int N=2*n-1;
    buildSparseTable(N);
}
//O(1)
int find_lca(int a, int b)
{
    if(in[a]>in[b]) swap(a,b);
    return query(in[a], in[b]);
}
int main()
{
    int n,m,i,j,q,x,y;
    cin>>n;
    for(i=1; i<n; i++)
    {
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    init(n);
    cin>>q;
    while(q--)
    {
        cin>>x>>y;
        cout<<"LCA of "<<x<<" and "<<y<<" is "<<find_lca(x,y)<<endl;
    }


    return 0;
}
