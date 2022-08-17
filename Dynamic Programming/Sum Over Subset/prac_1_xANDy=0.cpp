/**
    https://codeforces.com/contest/165/problem/E

    x&(subMask(reverseBit(x))) = 0
*/
#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 8388609

#define CS(i) cout<<"Case "<<i<<": "

#define bitOn(n,i) ((1LL<<i)|n)
#define bitOff(n,i) (~(1LL<<i)&n)
#define bitToggle(n,i) ((1LL<<i)^n)
#define getbit(n,i) ((n>>i)&1)
typedef long long ll;

ll dp[MAX],arr[MAX];

//O(N*2^N)
void SOS_DP(int N){
  for(int i = 0; i<N; ++i)
    dp[arr[i]] = arr[i];
  for(int i = 0; i<22; ++i)
    for(int mask = 0; mask < (1<<22); ++mask){
      if(dp[mask] == -1 && getbit(mask,i))
        dp[mask] = dp[bitToggle(mask,i)];
  }
}
void syntex_error()
{
    ll n,x;

    cin>>n;
    for(int i=0; i<n; i++)
      cin>>arr[i];
    clean(dp, -1);
    SOS_DP(n);
    for(int i=0; i<n; i++)
      cout<<dp[arr[i]^((1<<22)-1)]<<" ";
    
}

int32_t main()
{
    FAST
    
    ll TC=1LL,cs=1LL;

    //cin>>TC;

    while(TC--){
        //CS(cs++);
        syntex_error();
    }

    return 0;
}
