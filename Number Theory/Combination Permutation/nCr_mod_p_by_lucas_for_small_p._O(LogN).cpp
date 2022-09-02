//https://vjudge.net/contest/512856#problem/C

#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

#define MAX 1000003
#define MOD 1000003

ll fact[MAX],inv[MAX],invFact[MAX];

///O(N)
void PreCalculaton(){
    ll i;
    fact[0]=1;
    for(i=1; i<MAX; ++i)
        fact[i]=i*fact[i-1]%MOD;
    inv[1]=1;
    for(i=2; i<MAX; ++i) ///must be MAX<MOD
        inv[i]=((MOD-MOD/i)*inv[MOD%i])%MOD;
    invFact[0]=1;
    for(i=1; i<MAX; ++i)
        invFact[i]=(invFact[i-1]*inv[i])%MOD;
}
///O(1)
ll C(ll n, ll r){
    if(r>n) return 0;
    return fact[n]*invFact[r]%MOD*invFact[n-r]%MOD;
}
//O(log n)
ll Lucas(ll n, ll m){
    if(n==0 && m==0) return 1ll;
    ll ni = n % MOD;
    ll mi = m % MOD;
    if(mi>ni) return 0;
    return (Lucas(n/MOD, m/MOD)*C(ni, mi))%MOD;
}

ll nCr(ll n, ll r){
    return Lucas(n, r);
}
void solve()
{
    ll n,l,r;
    cin >> n >> l >> r;
    n=nCr(n+r-l+1, r-l+1)-1+MOD;
    n%=MOD;
    cout << n << endl;
}

int main()
{
    FAST
    PreCalculaton();
    int t=1;
    cin >> t;
    while(t--) solve();
}
