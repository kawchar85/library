/**
 * there doesn't exist a non-empty subset of segments
 * such that bitwise XOR of the numbers from them is equal to 0.
 * 
 * Notice that, saying all subsets of a set yeild non-zero xor is
 * equivalent to saying all subsets of that set yeild different 
 * xor-sum
 * 
 * https://codeforces.com/contest/1101/problem/G
 * */

#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);

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
}xb;

void solve(){
    ll n,x,pre=0,ans;
    cin>>n;
    while(n--)
    {
        cin>>x;
        pre^=x;
        xb.add(pre);
    }
    if(pre == 0LL)
        ans=-1;
    else
        ans=xb.size();
    cout<<ans<<endl;
    
    xb.clear();
}

int main(){
    FAST;

    int tc=1;
    //cin>>tc;
    while(tc--){
        solve();
    }
}
