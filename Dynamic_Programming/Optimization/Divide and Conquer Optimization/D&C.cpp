//https://robert1003.github.io/2020/02/25/dp-opt-divide-and-conquer.html
ll dp[N];
ll cost(int l, int r){
  return 1;
}

void solve(int l, int r, int ql, int qr) {
  if(l > r) return;
  int mid = l + (r - l) / 2;
  
  ll pos =0, val = INT_MAX; //check min or max ?
  for(int k = ql; k <= min(mid, qr); k++) {
    ll ret = cost(k, mid);
    if(ret < val) val = ret, pos = k; // min or max?
  }

  dp[mid] = val;

  // for H[j]<=H[j+1] i.e. cost(1,j)<=cost(1,j+1)
  solve(l, mid - 1, ql, pos);
  solve(mid + 1, r, pos, qr);
  // for H[j]>=H[j+1] i.e. cost(1,j)>=cost(1,j+1)
  //solve(l, mid - 1, pos, qr);
  //solve(mid + 1, r, ql, pos);

}
