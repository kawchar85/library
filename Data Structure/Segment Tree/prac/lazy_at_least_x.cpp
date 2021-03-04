//https://codeforces.com/edu/course/2/lesson/5/3/practice/contest/280799/problem/C

#include<bits/stdc++.h>
#define MAX 200005
#define ll long long
using namespace std;

ll arr[MAX];
int N;
struct info{
    ll lazy,val;
    info()
    {
        lazy=0LL;
        val=0LL;
    }
    void show()
    {
        cout<<val<<" "<<lazy<<endl;
    }
}tree[3*MAX];

void propagate(int node, int l, int r)
{
    tree[node].val+=tree[node].lazy;
    if(l!=r)
    {
        tree[2*node].lazy+=tree[node].lazy;
        tree[2*node+1].lazy+=tree[node].lazy;
    }
    tree[node].lazy=0;
}

ll merge(ll x, ll y)
{
    return max(x,y);
}

void build(int node, int l,int r)
{
    if(l==r)
    {
        tree[node].lazy=0LL;
        tree[node].val=arr[l];
        return;
    }
    int mid=(l+r)/2;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);
    tree[node].lazy=0LL;
    tree[node].val=merge(tree[node*2].val,tree[2*node+1].val);
}

int above_x(int node, int l, int r, ll x,int L)
{    
    propagate(node,l,r);
    if(L>r || tree[node].val<x) return -1;

    int mid=(l+r)/2;
    if(l==r)
        return l;
    int res=above_x(2*node, l, mid, x, L);
    if(res==-1)
        res=above_x(2*node+1, mid+1, r, x, L);
    
    return res;
}

void update(int node,int l,int r,int i,int j,ll val)
{
    propagate(node,l,r);
    if(i>r || j<l)
        return;
    if(l>=i && r<=j)
    {
        tree[node].lazy+=val;
        propagate(node,l,r);
        return;
    } 
    int mid=(l+r)/2;
    update(node*2,l,mid,i,j,val);
    update(node*2+1,mid+1,r,i,j,val);

    tree[node].val=merge(tree[node*2].val,tree[node*2+1].val);
}

void print(int node, int l,int r)
{
    cout<<"["<<l<<","<<r<<"]:--> ";
    tree[node].show();
    if(l==r)
        return;
    int mid=(l+r)/2;
    print(node*2,l,mid);
    print(node*2+1,mid+1,r);
}
void print(){
    print(1,0,N-1);
    cout<<"------\n";
}
 
void build(int n)
{
    N=n;
    //build(1,0,N-1);
}
void update(int i, int j, ll val)
{
    update(1,0,N-1,i,j,val);
}
int query(ll x, int L)
{
    return above_x(1,0,N-1,x,L);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n,m,i,k,a,b,c;
    ll val;

    cin>>n>>m;
    build(n);
    //print();
    while(m--)
    {
        cin>>k;
        if(k==1)
        {
            cin>>a>>b>>val;
            update(a,b-1,val);
            //print();
        }
        else
        {
            cin>>val>>a;
            cout<<query(val,a)<<endl;
        }
    }
    return 0;
}
