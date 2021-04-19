/**
    https://vjudge.net/contest/433995#problem/A
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MAX 100005
#define MOD 1000000007

struct XorBasis{
    vector<ll> basis;
    ll N=0;
    void add(ll x){
        N++;
        for(auto &i : basis) x=min(x,x^i);
        if(!x) return;
        for(auto &i : basis) if((i^x)<i) i^=x;
        basis.push_back(x);
        sort(basis.begin(), basis.end());
    }
    ll size(){
        return (ll)basis.size();
    }
    void clear(){
        N=0;
        basis.clear();
    }
    bool possible(ll x){
        for(auto &i: basis) x=min(x, x^i);
        return !x;
    }
    ll maxxor(ll x=0){
        for(auto &i: basis) x=max(x, x^i);
        return x;
    }
    ll minxor(ll x=0){
        for(auto &i: basis) x=min(x, x^i);
        return x;
    }
    ll cntxor(ll x){
        if(!possible(x)) return 0LL;
        return (1LL<<(N-size()));
    }
    ll kth(ll k){
        ll sz=size();
        if(k > (1LL<<sz)) return -1;
        k--; ll ans=0;
        for(ll i=0; i<sz; i++) if(k>>i & 1) ans^=basis[i];
        return ans;
    }
};

int arr[MAX],N;
struct info
{
    XorBasis xb;
    info()
    {
        xb.clear();
    }
    info(XorBasis x)
    {
        xb=x;
    }
    void show(){
        cout<<xb.size()<<endl;
    }
}tree[3*MAX];

info outOfRange(){
    return info();
}

info merge(info x, info y){
    for(auto cur : y.xb.basis)
        x.xb.add(cur);
    return x;
}

void build(int node, int l,int r)
{
    if(l==r)
    {
        XorBasis xb;
        xb.add(arr[l]);
        tree[node]=info(xb);
        return;
    }
    int mid=(l+r)/2;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);

    tree[node]=merge(tree[node*2], tree[2*node+1]);
}

info query(int node, int l, int r, int i, int j)
{
    if(i>r || j<l)
        return outOfRange();
    if(l>=i && r<=j)
        return tree[node];
    int mid=(l+r)/2;
    info x=query(node*2,l,mid,i,j);
    info y=query(node*2+1,mid+1,r,i,j);
    return merge(x,y);
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
    build(1,0,N-1);
}
info query(int i, int j){
    auto x = query(1, 0, N-1, i, j);
    return x;
}

void solve(){
    ll n,m,x,l,r,i,j,k;
    cin>>n>>m>>k;

    for(i=0; i<n; i++)
    {
        cin>>arr[i];
        arr[i]=arr[i]&(~k);
        //k er jei bit 1, or korle ans er sei bit
        // auto 1 hoye jabe. k te jei bit ghula 
        // zero, oighula consider korbo
    }
    
    build(n);

    while(m--)
    {
        cin>>l>>r;
        l--,r--;
        auto ans=query(l,r);
        cout<<(k|ans.xb.maxxor())<<endl;

    }
}

int main(){
    FAST;

    int tc=1;
    cin>>tc;
    while(tc--){
        solve();
    }
}
