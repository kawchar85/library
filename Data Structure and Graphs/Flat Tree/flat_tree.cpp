/*
    for any node x,
    L=in[x], R=out[x]
    (L,R] in FT, is child
    of x.
*/
#include<bits/stdc++.h>
using namespace std;
#define MAX 1001

vector<int> adj[MAX];
int FT[MAX],in[MAX], out[MAX];
int Timer=1;

void DFS(int u, int p)
{
    FT[Timer]=u;
    in[u] = Timer++;

    for(auto v: adj[u])
    {
        if(v==p) continue;
        DFS(v, u);
    }

    //FT[Timer]=u;
    out[u] = Timer-1;
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
    cout<<" In={ ";
    for(i=1; i<=n; i++)
        cout<<in[i]<<" ";
    cout<<"}\n";
    cout<<"out={ ";
    for(i=1; i<=n; i++)
        cout<<out[i]<<" ";
    cout<<"}\n";
    cout<<" FT={ ";
    for(i=1; i<=n; i++)
        cout<<FT[i]<<" ";
    cout<<"}\n";
    return 0;
}

/*
12
1 2
2 3
3 4
3 5
2 6
6 12
1 7
7 8
8 9
8 10
8 11
*/
