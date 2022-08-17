/**
    https://codeforces.com/contest/895/problem/C

    Sol:
    For each number in a, we only need to consider 
    the primes that divide it an odd number of times.
    Since there are only 19 primes in [1, 70], each 
    number corresponds to a vector in 19D space and 
    multiplying two numbers corresponds to an xor 
    operation. A square corresponds to the 0 vector.

*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MAX 100005
#define MOD 1000000007

int prime[]= {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
ll get(ll n){
    ll pf=0;
    for(int i=0; i<19; i++)
    {
        ll cnt=0;
        while(n%prime[i]==0){
            n/=prime[i];
            cnt++;
        }
        pf=pf*2+cnt%2;
    }
    return pf;
}
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
        //return (1LL<<(N-size()));
        ll ans=1LL;
        for(int i=0; i<N-size(); i++)
            ans=(ans*2)%MOD;
        return ans;
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
        xb.add(get(x));
    }

    cout<<xb.cntxor(0LL)-1<<endl; //-1 for empty subset
}
int main(){
    FAST;

    int tc=1;
    //cin>>tc;
    while(tc--){
        solve();
    }
}
