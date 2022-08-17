#include<bits/stdc++.h>
#define pb push_back
#define MAX 105
using namespace std;

struct Edge{
    int u,v,w,id;
};

bool operator<(Edge a,Edge b)
{
    return a.w<b.w;
}

vector<Edge>E,tree;
int par[MAX];

int find_par(int n)
{
    return par[n]==n?n:par[n]=find_par(par[n]);
}

bool MST(int n)
{
    sort(E.begin(),E.end());
    int u,v,w,i,cnt=0;
    for(i=0; i<MAX; i++)
        par[i]=i;
    for(auto now: E)
    {
        u=find_par(now.u);
        v=find_par(now.v);
        if(u==v) continue;
        par[u]=v;
        tree.pb(now);
        cnt++;
    }
    if(cnt==n-1) return 1;
    return 0;
}

int MST2(int n,int skip)
{
    int u,v,w,i,cnt=0,total=0;
    for(i=0; i<MAX; i++)
        par[i]=i;
    for(auto now: E)
    {
        if(now.id==skip) continue;
        u=find_par(now.u);
        v=find_par(now.v);
        if(u==v) continue;
        par[u]=v;
        total+=now.w;
        cnt++;
    }
    if(cnt!=n-1) total=0;
    return total;
}
int main()
{
    int t,cs,i,n,m,ans;
    Edge x;
    scanf("%d",&t);
    for(cs=1; cs<=t; cs++)
    {
        tree.clear();
        E.clear();
        scanf("%d %d",&n,&m);
        for(i=1; i<=m; i++)
        {
            scanf("%d %d %d",&x.u,&x.v,&x.w);
            x.id=i;
            E.pb(x);
        }
        printf("Case %d: ",cs);
        if(!MST(n)) puts("No way");
        else
        {
            ans=INT_MAX;
            for(auto v: tree)
            {
                m=MST2(n,v.id);
                if(m)
                    ans=min(ans,m);
            }
            if(ans==INT_MAX)
                puts("No second way");
            else
                printf("%d\n",ans);
        }
    }
    return 0;
}
