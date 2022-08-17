#include<bits/stdc++.h>
#define MAX 10001
#define ll long long

/** C(n,r) mod m
    Using recurrence:
    C(n,r) = C(n-1,r-1) + C(n-1,r)
    Time Complexity: O(n*r)
    Space Complexity: O(n*r)
    Up to 10000
*/
ll C(ll n,ll r,ll MOD)
{
    ll i,j,nCr[n+1][r+1];
    for(i=0; i<=n; i++)
    {
        for(j=0; j<=r && j<=i; j++)
        {
            if(j==0 || j==i)
                nCr[i][j]= 1ll;
            else
                nCr[i][j]=(nCr[i-1][j]+nCr[i-1][j-1])%MOD;
        }
    }
    return nCr[n][r];
}

/**  We can easily reduce the space complexity
     of the above solution by just keeping track
     of the previous row as we don’t need the rest rows.
     Time Complexity: O(n*r)
     Space Complexity: O(r)
*/
ll CC(ll n,ll r,ll MOD)
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

int main()
{
    ll n,r,p;
    while(cin>>n>>r>>p)
        cout<<nCr(n,r,p)<<endl;
}

