/**
    https://codeforces.com/contest/383/problem/E
   
*/
#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 16777217

#define CS(i) cout<<"Case "<<i<<": "

#define bitOn(n,i) ((1LL<<i)|n)
#define bitOff(n,i) (~(1LL<<i)&n)
#define bitToggle(n,i) ((1LL<<i)^n)
#define getbit(n,i) ((n>>i)&1)
typedef long long ll;

ll dp[MAX]; //cnt of no vowel

void SOS_DP(){
  for(int i = 0; i<24; ++i)
    for(int mask = 0; mask < (1<<24); ++mask){
      if(getbit(mask,i))
        dp[mask] += dp[bitToggle(mask,i)];
  }
}
ll sq(ll x){ return x*x;}
void syntex_error()
{
    ll n,x;
    string s;

    cin>>n;
    for(int i=0; i<n; i++){
      cin>>s;

      x=0;
      for(auto ch : s)
        x=bitOn(x,ch-'a');
      dp[x]++;
    }
    
    SOS_DP();
    x=0;
    for(int i=0; i<(1<<24); i++)
      x^=sq(n-dp[i]); //vowel = total - noVowel
    cout<<x<<endl;
    
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
