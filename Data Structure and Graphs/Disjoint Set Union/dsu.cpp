#include<bits/stdc++.h>
using namespace std;
#define MAX 10004

int parent[MAX],Size[MAX];

void make_set(int v)
{
    parent[v]=v;
    Size[v]=1;
}

int find_set(int v)
{
    if(parent[v]==v)
        return v;
    return parent[v]=find_set(parent[v]);
}

void union_sets(int a, int b)
{
    a=find_set(a);
    b=find_set(b);
    if(a!=b)
    {
        if(Size[a]<Size[b])
            swap(a,b);
        parent[b]=a;
        Size[a]+=Size[b];
    }
}
void init(int n)
{
    for(int i=0; i<=n; i++)
        make_set(i);
}
int main()
{

    return 0;
}
