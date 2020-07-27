 #include<bits/stdc++.h>
 #define ll long long
 using namespace std;

 ///Only for small value of MOD.
 ll C(ll n,ll r,ll MOD)
{
    ll i,j,ans[2][r+1];
    for(i=0; i<=n; i++)
    {
        for(j=0; j<=r && j<=i; j++)
        {
            if(j==0 || j==i)
                ans[i&1][j]= 1ll;
            else
                ans[i&1][j]=(ans[(i-1)&1][j]+ans[(i-1)&1][j-1])%MOD;
        }
    }
    return ans[n&1][r];
}
 ///O(p2 * Logp n) or O(log n) ??
ll Lucas(ll n, ll m, ll p)
{
    if(n==0 && m==0) return 1ll;
    ll ni = n % p;
    ll mi = m % p;
    if(mi>ni) return 0;
    return (Lucas(n/p, m/p, p)*C(ni, mi, p))%p;
}

ll nCr(ll n, ll r, ll MOD)
{
    return Lucas(n, r, MOD);
}

int main()
{
    ll n,r,p;
    while(cin>>n>>r>>p)
        cout<<nCr(n,r,p)<<endl;
}
