#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 101
#define pb push_back
vector<int> adj[MAX];
int par[MAX], in[MAX], out[MAX], dep[MAX], Time=1;

//call: par[1]=1; dep[1]=0; DFS(1,-1);
void DFS(int u, int p)
{
    in[u] = Time++;

    for(auto v: adj[u])
    {
        if(v==p) continue;
        par[v] = u;
        dep[v] = dep[u]+1;
        DFS(v, u);
    }

    out[u] = Time++;
}

///v is Ancestor of u?
bool isAnc(int v, int u)
{
	return in[v]<=in[u] && out[u]<=out[v];
}

/// v is on path x->y ?
bool onPath(ll x, ll v, ll y)
{
    return (isAnc(x, v) && isAnc(v, y));
}
int main()
{

    int i,j,n,m,k,fv;

    cin>>n>>m;

    for(i=1; i<n; i++)
    {
        int X,Y;
        cin>>X>>Y;
        adj[X].pb(Y);
        adj[Y].pb(X);
    }

    par[1]=1;
    dep[1]=0;
    DFS(1,-1);

    return 0;
}
