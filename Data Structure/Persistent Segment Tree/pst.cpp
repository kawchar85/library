//https://www.spoj.com/problems/PSEGTREE/
#include <bits/stdc++.h>
using namespace std;
#define ll long long


#define MAX 100005
#define LOG 17

struct info{
    int L,R,val;
};
info tree[LOG*MAX];
int root[MAX],arr[MAX],N,NEXT_FREE_INDEX=1,v_id=1;

int merge(int x, int y)
{
    return x+y;
}
void build(int node, int l, int r)
{
    if(l==r)
    {
        tree[node].val=arr[l];
        return;
    }
    int mid=(l+r)/2;
    int x=NEXT_FREE_INDEX++;
    int y=NEXT_FREE_INDEX++;
    tree[node].L=x;
    tree[node].R=y;
    build(tree[node].L, l, mid);
    build(tree[node].R, mid+1, r);
    tree[node].val=merge(tree[x].val, tree[y].val);
}
int update(int node, int l, int r, int pos, int val)
{
    if(pos<l || r<pos) return node;
    if(l==r)
    {
        int x=NEXT_FREE_INDEX++;
        tree[x].val=tree[node].val+val;
        return x;
    }
    int mid=(l+r)/2;
    int z=NEXT_FREE_INDEX++;
    int x=update(tree[node].L, l, mid, pos, val);
    int y=update(tree[node].R, mid+1, r, pos, val);

    tree[z].val=merge(tree[x].val, tree[y].val);
    tree[z].L=x;
    tree[z].R=y;
    
    return z;    
}
int query(int node, int l, int r, int i, int j)
{
    if(j<l || r<i) return 0;
    if(l>=i && r<=j) return tree[node].val;
    int mid=(l+r)/2;
    int x=query(tree[node].L, l, mid, i, j);
    int y=query(tree[node].R, mid+1, r, i, j);
    return merge(x,y);
}
void build(int n)
{
    N=n;
    NEXT_FREE_INDEX=1;
    v_id=1;
    root[0]=NEXT_FREE_INDEX++;
    build(root[0], 0, N-1);
}
void update(int version, int pos, int x)
{
    root[v_id++]=update(root[version], 0, N-1, pos, x);
}
int query(int version, int i, int j)
{
    return query(root[version], 0, N-1, i, j);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n,q,i,j,l,r,x,ver,t,pos;

    cin>>n;
    for(i=0; i<n; i++)
        cin>>arr[i];
    build(n);

    cin>>q;
    while(q--)
    {
        cin>>t;
        if(t==1)
        {
            cin>>ver>>pos>>x;
            pos--;
            update(ver, pos, x);
        }
        else
        {
            cin>>ver>>l>>r;
            l--,r--;
            cout<<query(ver, l, r)<<endl;
        }
    }
    return 0;
}
