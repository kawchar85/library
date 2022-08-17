//CF 459D
#include<bits/stdc++.h>
#define MAX 1000006
#define ll long long
using namespace std;
 
ll temp[MAX];
ll freqL[MAX],freqR[MAX];
int N;
 
void Compress(vector<ll> &v)
{
    int n=(int)v.size();
    for(int i=0; i<n; i++)
    {
        temp[i]=v[i];
    }
    sort(temp,temp+n);
    int c=0;
    map<ll,int>mp;
    mp[temp[0]]=++c;
    for(int i=1; i<n; i++)
    {
        if(temp[i]!=temp[i-1])
            mp[temp[i]]=++c;
    }
    for(int i=0; i<n; i++)
        v[i]=mp[v[i]];
}
 
struct info{
    ll sum;
    info(){
        sum=0;
    }
    info(ll x){
        sum=x;
    }
    void show(){
        cout<<"Sum = "<<sum<<"\n";
    }
};
info tree[3*MAX];
 
info outOfRange(){
    return info(0);
}
info Set(ll x){
    return info(x);
}
info merge(info x, info y){
    info temp;
    temp.sum=x.sum+y.sum;
    return temp;
}
 
info query(int node,int l,int r,int i,int j)
{
    if(i>r || j<l)
        return outOfRange();
    if(l>=i && r<=j)
        return tree[node];
    int mid=(l+r)/2;
    auto x=query(node*2,l,mid,i,j);
    auto y=query(node*2+1,mid+1,r,i,j);
    return merge(x,y);
}
 
void update(int node,int l,int r,int pos,int val)
{
    if(pos>r || pos<l)
        return;
    if(l==r)
    {
        tree[node].sum+=val;
        return;
    }
    int mid=(l+r)/2;
    if(pos<=mid)
        update(node*2,l,mid,pos,val);
    else
        update(node*2+1,mid+1,r,pos,val);
 
    tree[node]=merge(tree[node*2],tree[2*node+1]);
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
void update(int pos, ll val){
    update(1,0,N-1,pos,val);
}
ll query(int x){
    auto ans = query(1,0,N-1,1,x); 
    return ans.sum;
}
 
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
 
    int i,n;
    vector<ll>v;
 
    cin>>n;
    for(i=0; i<n; ++i)
    {
        ll xx;
        cin>>xx;
        v.push_back(xx);
    }
    Compress(v);
    build(n);
    for(i=n-1; ~i; i--)
    {
        freqR[v[i]]++;
        update(freqR[v[i]], 1);
    }
    ll sum=0LL;
    for(i=0; i<n; i++)
    {
        freqL[v[i]]++;
        update(freqR[v[i]]--, -1);
        ll x=query(freqL[v[i]]-1);
        sum+=x;
        //cout<<i<<" "<<x<<endl;
    }
    cout<<sum<<endl;
 
} 
