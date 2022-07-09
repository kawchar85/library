/**
    https://atcoder.jp/contests/arc067/tasks/arc067_d
*/
#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 5003

#define CS(i) cout<<"Case "<<i<<": "

typedef long long ll;

ll dst[205][MAX][13],B[MAX][205],cum[MAX],dp[MAX];
ll n,m;

ll merge(ll x, ll y){
    return max(x,y);
}
void build(int n, int m){
    
    for(int i=1; i<=n; i++)
      for(int j=1; j<=m; j++)
        dst[j][i][0]=B[i][j];

    for(int j=1; j<=m; j++)
      for(int k=1; k<13; ++k)
        for(int i=1; (i+(1<<k)-1)<=n; ++i)
            dst[j][i][k] = merge(dst[j][i][k-1], dst[j][i+(1<<(k-1))][k-1]);
}

int query(int m, int l, int r){
    int k=31-__builtin_clz(r-l+1);
    //int k = __lg(r-l+1);
    return merge(dst[m][l][k], dst[m][r-(1<<k)+1][k]);
}

ll cost(int l, int r){
  ll sum = 0;
  for(int i=1; i<=m; i++)
    sum+=query(i, l,r);//i'th ticket er jonno max in this range
  return sum - (cum[r]-cum[l]); // -dis
}

void solve(int l, int r, int ql, int qr) {
  if(l > r) return;
  int mid = l + (r - l) / 2;
  
  ll pos =0, val = LLONG_MIN;
  for(int k = ql; k <= min(mid, qr); k++) {
    ll ret = cost(k, mid);
    if(ret > val) val = ret, pos = k; //max query
  }

  dp[mid] = val;

  // for H[j]<=H[j+1] i.e. cost(1,j)<=cost(1,j+1)
  solve(l, mid - 1, ql, pos);
  solve(mid + 1, r, pos, qr);
  // for H[j]>=H[j+1] i.e. cost(1,j)>=cost(1,j+1)
  //solve(l, mid - 1, pos, qr);
  //solve(mid + 1, r, ql, pos);

}
void syntex_error()
{
    ll x;

    cin>>n>>m;
    for(int i=2; i<=n; i++){
      cin>>x;
      cum[i]=cum[i-1]+x;
    }
    for(int i=1; i<=n; i++)
      for(int j=1; j<=m; j++)
        cin>>B[i][j];
    build(n,m);

    solve(1,n, 1, n);
    ll mx = 0;
    for(int i = 1; i<=n; i++)
      mx= max(mx, dp[i]);

    cout<<mx<<endl;
    
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
