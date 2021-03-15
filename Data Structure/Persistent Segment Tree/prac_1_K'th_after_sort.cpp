//https://vjudge.net/problem/SPOJ-MKTHNUM

#include <bits/stdc++.h>
using namespace std;
#define ll long long


#define MAX 100005
#define LOG 20

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
        tree[node].val=0;
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
int k_th(int cur, int pre, int l, int r, int k)
{
    if(l==r)
        return l;
    int mid=(l+r)/2;
    int l_val=tree[tree[cur].L].val-tree[tree[pre].L].val;
    if(k<=l_val)
        return k_th(tree[cur].L, tree[pre].L, l, mid, k);
    else
        return k_th(tree[cur].R, tree[pre].R, mid+1, r, k-l_val);
}
void print(int node, int l=1, int r=N)
{
    if(l==r)
    {
        cout<<l<<":"<<tree[node].val<<endl;
        return;
    }
    int mid=(l+r)/2;
    print(tree[node].L, l, mid);
    print(tree[node].R, mid+1, r);
}
void build(int n)
{
    N=n;
    NEXT_FREE_INDEX=1;
    v_id=1;
    root[0]=NEXT_FREE_INDEX++;
    build(root[0], 1, N);
}
void update(int version, int pos, int x)
{
    root[v_id++]=update(root[version], 1, N, pos, x);
}
int query(int version, int i, int j)
{
    return query(root[version], 1, N, i, j);
}
int k_th(int l, int r, int k) 
{
    return k_th(root[r], root[l-1], 1, N, k);
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n,q,i,j,k,l,r,x;
    vector<int>v;
    cin>>n>>q;
    for(i=0; i<n; i++){
        cin>>arr[i];
        v.push_back(arr[i]);
    }
    build(n);

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    map<int, int> mp;
    for(i=0; i<v.size(); i++)
        mp[v[i]]=i+1; //mapping 1 to SZ

    for(i=0; i<n; i++)
    {
        update(v_id-1, mp[arr[i]], 1);
        //print(root[v_id-1]);
        //cout<<"---------\n";
    }
    
    while(q--)
    {
        cin>>l>>r>>k;
        k=k_th(l, r, k);
        cout<<v[k-1]<<endl; //v[i]=i+1, so index k hole val=v[i-1]
    }
    return 0;
}
