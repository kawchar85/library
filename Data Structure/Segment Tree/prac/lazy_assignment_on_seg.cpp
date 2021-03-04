//https://codeforces.com/edu/course/2/lesson/5/1/practice/contest/279634/problem/C
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
        lazy=-1;
        val=0LL;
    }
    void show()
    {
        cout<<val<<" "<<lazy<<endl;
    }
}tree[3*MAX];

ll merge(ll x, ll y)
{
    return x+y;
}

void propagate(int node, int l, int r)
{
    if(tree[node].lazy==-1)
        return;
    tree[node].val=tree[node].lazy;
    if(l!=r)
    {
        tree[2*node].lazy=tree[node].lazy;
        tree[2*node+1].lazy=tree[node].lazy;
    }
    tree[node].lazy=-1;
}

void build(int node, int l,int r)
{
    if(l==r)
    {
        tree[node].lazy=-1;
        tree[node].val=arr[l];
        return;
    }
    int mid=(l+r)/2;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);
    tree[node].lazy=-1;
    tree[node].val=merge(tree[node*2].val,tree[2*node+1].val);
}

ll query(int node,int l,int r,int idx)
{
    propagate(node,l,r);
    if(idx>r || idx<l)
        return 0LL;
    if(l==r)
        return tree[node].val;
    int mid=(l+r)/2;
    if(idx<=mid)
        return query(node*2,l,mid,idx);
    else
        return query(node*2+1,mid+1,r,idx);
}

void update(int node,int l,int r,int i,int j,ll val)
{
    propagate(node,l,r);
    if(i>r || j<l)
        return;
    if(l>=i && r<=j)
    {
        tree[node].lazy=val;
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
}
void build(int n){
    N=n;
    //build(1,0,N-1);
}
void update(int i, int j, ll val){
     update(1,0,N-1,i,j,val);
}
ll query(int idx){
    return query(1,0,N-1,idx);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll n,i,q,z,k;
    cin>>n>>q;

    build(n);

    while(q--)
    {
        cin>>k;
        if(k==1)
        {
            int l,r;
            cin>>l>>r>>z;
            update(l,r-1,z);
        }
        else
        {
            int idx;
            cin>>idx;
            cout<<query(idx)<<endl;
        }

    }
    return 0;
}
