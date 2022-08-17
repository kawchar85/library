/**
    problem: https://codeforces.com/contest/631/problem/E
    
    //left to right
    changed = i*a[j]+(cum[j]-j*a[j])-cum[i]
    so, fj(x) =a[j]*x + (cum[j]-j*a[j])
    query with i, extra -cum[i]

    //right to left shift
    .... 
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

ll arr[MAX],cum[MAX];
void syntex_error()
{
    ll n,m,i,j,k,a,b,c,x,y,z;
    
    cin>>n;
    LineContainer h;

    ll sum=0;
    for(i=1; i<=n; i++){
        cin>>arr[i];
        sum+=i*arr[i];
        cum[i]=cum[i-1]+arr[i];
    }

    ll mx = 0;

    h.add(arr[1], cum[1]-1*arr[1]);
    for(i=2; i<=n; i++){
        h.add(arr[i], cum[i]-i*arr[i]); //to make i=j; j<=i
        mx = max(mx, h.query(i)-cum[i]);
    }

    h=LineContainer();
    h.add(arr[n], cum[n-1]-n*arr[n]);
    for(i=n-1; i; i--){
        h.add(arr[i], cum[i-1]-i*arr[i]); //to make i=j; j<=i
        mx = max(mx, h.query(i)-cum[i-1]);
    }

    sum+=mx;
    cout<<sum<<endl;
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
