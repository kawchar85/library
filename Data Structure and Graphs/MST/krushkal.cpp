#include<bits/stdc++.h>
#define pb push_back
#define MAX 205
#define in(x) scanf("%d",&x)
using namespace std;

struct Edge{
    int u,v,w;
    Edge(){}
    Edge(int x,int y,int z)
    {
        u=x;v=y;w=z;
    }
};
bool operator<(Edge a,Edge b)
{
    return a.w<b.w;
}

vector<Edge>E;
int par[MAX];

int find_par(int x)
{
    return par[x]==x?x:par[x]=find_par(par[x]);
}

int MST(int n)
{
    int i,cnt=0,u,v,total=0;
    for(i=1; i<=n; i++)
        par[i]=i;
    sort(E.begin(),E.end());
    vector<Edge>tree;
    for(auto now : E)
    {
        u=find_par(now.u);
        v=find_par(now.v);
        if(u==v) continue;
        par[u]=v;
        total+=now.w;
        cnt++;
        tree.pb(now);
    }
    E.clear();
    E=tree;
    if(cnt!=n-1) total=-1;
    return total;
}

int main()
{
    int t,cs,i,j,n,w;
    Edge x;
    in(t);
    for(cs=1; cs<=t; cs++)
    {
        E.clear();
        printf("Case %d:\n",cs);
        in(n); in(w);
        for(i=0; i<w; i++)
        {
            in(x.u);in(x.v);in(x.w);
            E.pb(x);
            printf("%d\n",MST(n));
        }
    }
    return 0;
}
