// A&(-1)=A
//A|0=A

//https://codeforces.com/edu/course/2/lesson/5/2/practice/contest/279653/problem/C
#include<bits/stdc++.h>
#define MAX 200005
#define ll long long
using namespace std;

#define MOD 1000000007
ll arr[MAX];
int N;
struct info{
    ll lazy,val;
    info()
    {
        lazy=0LL; //x|0=x
        val=0LL;
    }
    void show()
    {
        cout<<val<<" "<<lazy<<endl;
    }
}tree[3*MAX];

void propagate(int node, int l, int r)
{
    tree[node].val|=tree[node].lazy;
    if(l!=r)
    {
        tree[2*node].lazy|=tree[node].lazy;
        tree[2*node+1].lazy|=tree[node].lazy;
    }
    tree[node].lazy=0LL; //x|0=x
}

ll merge(ll x, ll y)
{
    return (x&y);
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

ll query(int node,int l,int r,int i, int j)
{
    propagate(node,l,r);
    if(i>r || j<l)
        return -1; //x&(-1)=x
    if(l>=i && j>=r)
        return tree[node].val;
    int mid=(l+r)/2;
    ll x=query(node*2,l,mid,i,j);
    ll y=query(node*2+1,mid+1,r,i,j);
    return merge(x,y);
}

void update(int node,int l,int r,int i,int j,ll val)
{
    propagate(node,l,r);
    if(i>r || j<l)
        return;
    if(l>=i && r<=j)
    {
        tree[node].lazy|=val;
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
ll query(int i, int j){
    return query(1,0,N-1,i, j);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll n,i,q,z,k;
    cin>>n>>q;
    int l,r;

    build(n);

    while(q--)
    {
        cin>>k;
        if(k==1)
        {
            
            cin>>l>>r>>z;
            update(l,r-1,z);
        }
        else
        {
            cin>>l>>r;
            cout<<query(l,r-1)<<endl;
        }

    }
    return 0;
}
