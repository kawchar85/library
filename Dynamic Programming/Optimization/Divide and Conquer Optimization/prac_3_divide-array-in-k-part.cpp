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
#define MAX 200005

#define CS(i) cout<<"Case "<<i<<": "

typedef long long ll;

ll dp[22][MAX];//dp[k][i]=(1...i) k part
ll arr[MAX],fre[MAX];
int cur_l=0, cur_r=-1; ll cnt=0;

void add(int pos){
  cnt+=fre[arr[pos]];
  fre[arr[pos]]++;
}
void sub(int pos){
  fre[arr[pos]]--;
  cnt-=fre[arr[pos]];
    
}

ll cost(int L, int R){
  while(cur_l>L)  add(--cur_l);
  while(cur_r<R)  add(++cur_r);

  while(cur_l<L)  sub(cur_l++);
  while(cur_r>R)  sub(cur_r--);

  return cnt;
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

void syntex_error()
{
    ll n,k,x;

    cin>>n>>k;
    
    for(int i=1; i<=n; i++){
      cin>>arr[i];
    }

    for(int i=1; i<=n; i++) dp[1][i] = cost(1, i);
    for(int i=2; i<=k; i++) solve(i, 1, n, 1, n);

    cout<<dp[k][n]<<endl;
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
