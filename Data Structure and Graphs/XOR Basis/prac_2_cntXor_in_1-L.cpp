//https://codeforces.com/contest/959/problem/F

#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MAX 100005
#define MOD 1000000007

ll power[MAX];
void pre(){
    power[0]=1LL;
    for(int i=1; i<MAX; i++)
        power[i]=(power[i-1]*2)%MOD;
}
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
        return power[(N-size())];
    }
    ll kth(ll k){
        ll sz=size();
        if(k > (1LL<<sz)) return -1;
        k--; ll ans=0;
        for(ll i=0; i<sz; i++) if(k>>i & 1) ans^=basis[i];
        return ans;
    }
}xb;

ll ans[MAX];

void solve(){
    ll n,m,x,l,i;
    cin>>n>>m;
    vector<ll> v;
    for(i=0; i<n; i++)
    {
        cin>>x;
        v.push_back(x);
    }
    vector< pair<ll,ll> > q[n+5];//id,x
    for(i=0; i<m; i++)
    {
        cin>>l>>x;
        l--;
        q[l].push_back({i,x});
    }

    for(i=0; i<n; i++)
    {
        xb.add(v[i]);
        for(auto p : q[i])
        {
            ans[p.first]=xb.cntxor(p.second);
        }
    }

    for(i=0; i<m; i++)
        cout<<ans[i]<<endl;

    xb.clear();
}

int main(){
    FAST;

    pre();
    int tc=1;
    //cin>>tc;
    while(tc--){
        solve();
    }
}
