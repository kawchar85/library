/**
    https://codeforces.com/contest/321/problem/E
*/

#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 4004

#define CS(i) cout<<"Case "<<i<<": "

typedef long long ll;

ll dp[808][MAX];//dp[k][i]=(1...i) k part
ll cum[MAX][MAX];
ll cost(int l, int r){
  if(l>r) return 0LL;
  return (cum[r][r] - cum[l-1][r] - cum[r][l-1] + cum[l-1][l-1])/2;
}

void solve(int kk, int l, int r, int ql, int qr) {
  if(l > r) return;
  int mid = l + (r - l) / 2;
  
  ll pos =0, val = LLONG_MAX;
  for(int k = ql; k <= min(mid, qr); k++) {
    ll ret =dp[kk-1][k]+cost(k+1, mid);
    if(ret < val) val = ret, pos = k; //min query
  }

  dp[kk][mid] = val;

  // for H[j]<=H[j+1] i.e. cost(1,j)<=cost(1,j+1)
  solve(kk, l, mid - 1, ql, pos);
  solve(kk, mid + 1, r, pos, qr);
  // for H[j]>=H[j+1] i.e. cost(1,j)>=cost(1,j+1)
  //solve(l, mid - 1, pos, qr);
  //solve(mid + 1, r, ql, pos);

}
#define getchar _getchar_nolock
#define putchar _putchar_nolock
ll read() {
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(ll x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
void syntex_error()
{
    ll n,k,x;

    //cin>>n>>k;
    n=read(); k=read();
    for(int i=1; i<=n; i++){
      for(int j=1; j<=n; j++){
        x=read();
        cum[i][j]=cum[i-1][j]+cum[i][j-1]-cum[i-1][j-1]+x;
      }
    }

    for(int i=1; i<=n; i++) dp[1][i] = cost(1, i);
    for(int i=2; i<=k; i++) solve(i, 1, n, 1, n);

    print(dp[k][n]);
    //cout<<dp[k][n]<<endl;
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
