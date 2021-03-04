/**
https://codeforces.com/edu/course/2/lesson/4/2/practice/
*/

#include<bits/stdc++.h>
#define MAX 100005
#define ll long long
using namespace std;

ll arr[MAX], tree[3*MAX];
int N;

ll merge(ll x, ll y)
{
    return max(x,y);
}
void build(int node, int l,int r)
{
    if(l==r)
    {
        tree[node]=arr[l];
        return;
    }
    int mid=(l+r)/2;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);
    tree[node]=merge(tree[node*2],tree[2*node+1]);
}

void update(int node,int l,int r,int pos,ll val)
{
    if(pos>r || pos<l)
        return;
    if(l==r)
    {
        tree[node]=val;
        return;
    }
    int mid=(l+r)/2;
    if(pos<=mid)
        update(node*2,l,mid,pos,val);
    else
        update(node*2+1,mid+1,r,pos,val);

    tree[node]=merge(tree[node*2],tree[node*2+1]);
}

int above_x(int node, int l, int r, ll x)
{
    int mid=(l+r)/2;
    if(l==r)
        return l;
    if(x<=tree[2*node])
    {
       return above_x(2*node, l, mid, x);
    }
    else
    {
        return above_x(2*node+1, mid+1, r, x);
    }
}

int above_x_L(int node, int l, int r, ll x,int L)
{    
    if(L>r || tree[node]<x) return -1;
 
    int mid=(l+r)/2;
    if(l==r)
        return l;
    int res=above_x_L(2*node, l, mid, x, L);
    if(res==-1)
        res=above_x_L(2*node+1, mid+1, r, x, L);
    
    return res;
}

void print(int node, int l,int r)
{
    cout<<"["<<l<<","<<r<<"]:--> "<<tree[node]<<endl;
    if(l==r)
        return;
    int mid=(l+r)/2;
    print(node*2,l,mid);
    print(node*2+1,mid+1,r);
}
void print(){
    print(1,0,N-1);
}
void build(int n)
{
    N=n;
    build(1,0,N-1);
}
void update(int pos, ll val) //arr[pos]=val
{
    update(1,0,N-1,pos,val);
}
ll query(ll x) //minimum index j such that a[j]≥x
{
    if(x>tree[1]) return -1;
    return above_x(1,0,N-1,x);
}
int query(ll x, int L)//minimum index j such that j≥l and a[j]≥x
{
    return above_x_L(1,0,N-1,x,L);
}

int main()
{
    
    return 0;
}
