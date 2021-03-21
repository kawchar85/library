/**
https://www.spoj.com/problems/CLFLARR/
*/
#include<bits/stdc++.h>
using namespace std;
#define MAX 200005

int parent[MAX];

void make_set(int v)
{
    parent[v]=v;
}

int find_set(int v)
{
    if(parent[v]==v)
        return v;
    return parent[v]=find_set(parent[v]);
}

void init()
{
    for(int i=0; i<MAX; i++)
        make_set(i);
}
struct data{
    int l,r,c;
};
int color[MAX];
data query[MAX];
int main()
{
    init();

    int n,q,l,r,c,i;
    cin>>n>>q;
    for(i=0; i<q; i++)
    {
        cin>>query[i].l>>query[i].r>>query[i].c;
    }

    for(i=q-1; ~i; i--)
    {
        l=query[i].l;
        r=query[i].r;
        c=query[i].c;
        for(int v=find_set(l); v<=r; v=find_set(v))
        {
            color[v]=c;
            parent[v]=v+1;
        }
    }
    for(i=1; i<=n; i++)
        cout<<color[i]<<endl;


    return 0;
}

