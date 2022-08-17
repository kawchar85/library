//https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/A

#include<bits/stdc++.h>
#define MAX 200005
#define ll long long
using namespace std;

#define MOD 1000000007
ll arr[MAX];
int N;
struct info{
    ll lazy[2],val;
    info()
    {
        lazy[0]=-1;//assignment
        lazy[1]=0LL;//addition
        val=0LL;
    }
    void show()
    {
        cout<<val<<" "<<lazy[0]<<" "<<lazy[1]<<endl;
    }
}tree[3*MAX];

void propagate(int node, int l, int r, int type)
{
    if(type==0)
    {
        if(tree[node].lazy[0]==-1) return;
        
        tree[node].val=tree[node].lazy[0]*(r-l+1);
        if(l!=r)
        {
            tree[2*node].lazy[0]=tree[node].lazy[0];
            tree[2*node].lazy[1]=0LL;
            tree[2*node+1].lazy[0]=tree[node].lazy[0];
            tree[2*node+1].lazy[1]=0;
        }
        tree[node].lazy[0]=-1;
        tree[node].lazy[1]=0LL;
    }
    else
    {
        propagate(node,l,r,0);

        if(tree[node].lazy[1]==0) return;
        tree[node].val+=tree[node].lazy[1]*(r-l+1);
        if(l!=r)
        {
            int mid=(l+r)/2;
            propagate(2*node,l,mid,0);
            propagate(2*node+1,mid+1, r,0);

            tree[2*node].lazy[1]+=tree[node].lazy[1];
            tree[2*node+1].lazy[1]+=tree[node].lazy[1];
        }
        tree[node].lazy[1]=0LL;
    }
}

ll merge(ll x, ll y)
{
    return (x+y);
}

ll query(int node,int l,int r,int i, int j)
{
    propagate(node,l,r,1);
    if(i>r || j<l)
        return 0LL;
    if(l>=i && j>=r)
        return tree[node].val;
    int mid=(l+r)/2;
    ll x=query(node*2,l,mid,i,j);
    ll y=query(node*2+1,mid+1,r,i,j);
    return merge(x,y);
}

void update0(int node,int l,int r,int i,int j,ll val)
{
    propagate(node,l,r,1);
    if(i>r || j<l)
        return;
    if(l>=i && r<=j)
    {
        tree[node].lazy[0]=val;
        propagate(node,l,r,1);
        return;
    }
    int mid=(l+r)/2;
    update0(node*2,l,mid,i,j,val);
    update0(node*2+1,mid+1,r,i,j,val);

    tree[node].val=merge(tree[node*2].val,tree[node*2+1].val);
}

void update1(int node,int l,int r,int i,int j,ll val)
{
    propagate(node,l,r,1);
    if(i>r || j<l)
        return;
    if(l>=i && r<=j)
    {
        tree[node].lazy[1]+=val;
        propagate(node,l,r,1);
        return;
    } 
    int mid=(l+r)/2;
    update1(node*2,l,mid,i,j,val);
    update1(node*2+1,mid+1,r,i,j,val);

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
    cout<<"-----\n";
}
void build(int n){
    N=n;
    //build(1,0,N-1);
}
void update(int i, int j, ll val, int type){
     if(type==1)
        update0(1,0,N-1,i,j,val);
    else
        update1(1,0,N-1,i,j,val);
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
        if(k<3)
        {
            
            cin>>l>>r>>z;
            update(l,r-1,z,k);
            //print();
        }
        else
        {
            cin>>l>>r;
            //print();
            cout<<query(l,r-1)<<endl;
        }

    }
    return 0;
}
