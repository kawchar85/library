/**
    https://csacademy.com/contest/archive/task/xor-closure/statement/
    
    Sol:
    If we have a set of values S such that
    for any two values their xor is also in S,
    then it follows that for every subset of S
    the xor of all the values is also in S

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
    ll N=0,tmp=0;
    void add(ll x){
        N++;tmp|=x;
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
        N=0;tmp=0;
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
    ll sumOfAll(){
        ll ans=tmp*(1LL<<(N-1));
        return ans;
    }
    ll kth(ll k){
        ll sz=size();
        if(k > (1LL<<sz)) return -1;
        k--; ll ans=0;
        for(ll i=0; i<sz; i++) if(k>>i & 1) ans^=basis[i];
        return ans;
    }
}xb;

void solve(){
    ll n,x;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>x;
        xb.add(x);
    }

    ll total=1LL<<xb.size();
    cout<<total-n<<endl;
}
int main(){
    FAST;

    int tc=1;
    //cin>>tc;
    while(tc--){
        solve();
    }
}
