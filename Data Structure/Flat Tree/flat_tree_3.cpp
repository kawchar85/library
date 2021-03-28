/*
    Edge List stored.
    for n node size=2*n-1
*/
#include<bits/stdc++.h>
using namespace std;
#define MAX 1001

vector<int> adj[MAX];
int FT[2*MAX],in[MAX];
int Timer;

void DFS(int u, int p)
{
    in[u]=Timer;
    FT[Timer++]=u;
    for(auto v: adj[u])
    {
        if(v==p) continue;
        DFS(v, u);
        FT[Timer++]=u;
    }
}

int main()
{
    int i,j,n,m;

    cin>>n;
    for(i=1; i<n; i++)
    {
        int xx,yy;
        cin>>xx>>yy;
        adj[xx].push_back(yy);
        adj[yy].push_back(xx);
    }
    DFS(1, -1);
    
    cout<<"\nIn={ ";
    for(i=1; i<=n; i++)
        cout<<in[i]<<" ";
    cout<<"}\n";
    
    cout<<"FT={ ";
    for(i=0; i<2*n-1; i++)
        cout<<FT[i]<<" ";
    cout<<"}\n";
    return 0;
}
