/**
    Resource: https://satashun.github.io/algorithm/cpp_src/other/LineContainer.hpp.html
    problem: https://vjudge.net/problem/SPOJ-CHTPRAC
 */

#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 200005

#define CS(i) cout<<"Case "<<i<<": "

typedef long long ll;

struct Line {
  //mx+c
  mutable ll m, c, p;
  bool operator<(const Line& o) const { return m < o.m; }
  bool operator<(ll x) const { return p < x; }
};

//for min query LineContainer(true), normally->max
struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  static const ll inf = LLONG_MAX;
  int mnQ=1;
  LineContainer(bool minQuery=false){
    if(minQuery) mnQ=-1;
    else mnQ=1;
  }
  ll div(ll a, ll b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator x, iterator y) {
    if (y == end()) return x->p = inf, 0;
    if (x->m == y->m) x->p = x->c > y->c ? inf : -inf;
    else x->p = div(y->c - x->c, x->m - y->m);
    return x->p >= y->p;
  }
  void add(ll m, ll c) {
    m*=mnQ, c*=mnQ;
    auto z = insert({m, c, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  ll query(ll x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return mnQ*(l.m * x + l.c);
  }
};

void syntex_error()
{
    ll n,m,i,j,k,a,b,c,x,y,z;
    
    cin>>n>>a;
    LineContainer h(a%2);
    //LineContainer h=LineContainer(a%2);

    while(n--){
        cin>>x;

        if(x==1){
            cin>>m>>c;
            h.add(m,c);
        }
        else{
            cin>>x;
            cout<<h.query(x)<<endl;
        }
    }

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
