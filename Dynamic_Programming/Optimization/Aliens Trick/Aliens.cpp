//https://robert1003.github.io/2020/02/26/dp-opt-wqs-binary-search.html
//https://rezwanarefin01.github.io/posts/ioi16-aliens-trick/

pair<ll,ll> solveWithPenalty(ll p){
  //add p with targets
  ll ans=0,cnt=0;
  //cal ans
  //.....
  //remove p from targets
  return {ans, cnt};
}

ll Alien(ll l, ll r, ll need){
  ll ans=-1;
  while(l <= r) {
    ll mid = l+(r-l)/2;
    //solveWithPenalty() retrun {ansWithPenalty, cnt}
    pair<ll,ll> res = solveWithPenalty(mid); 
    if(res.second >= need) ans = res.first - mid * need, l = mid + 1;
    else r = mid - 1;
  }
  return ans;
}
