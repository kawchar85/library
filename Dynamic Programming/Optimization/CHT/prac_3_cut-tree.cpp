/**
  problem: https://codeforces.com/contest/319/problem/C

  //Bruteforce
  for(i=1; i<=n; i++)
    for(j=1; j<i; j++)
        dp[i]=min(dp[i], a[i]*b[j]+dp[j]);

   min{a[i]*b[j]+dp[j]} for j<i
   fj(x) = b[j]*x+dp[j]
   b[]-->dec slop
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


struct CHT{
    //f=mx+c
    vector<ll> M,C;
    bool decSlop, minQuery;
    int ptr;
    
    CHT(bool _decSlop=true, bool mnQuery=true){
        decSlop = _decSlop; minQuery = mnQuery;
        ptr=0;
    }

    bool bad(int l1, int l2, int l3){
        //dec+min || inc+max <=
        //dec+max || inc+min >=
        if( decSlop^minQuery )
            return 1.0*(C[l3]-C[l1])*(M[l1]-M[l2]) >= 1.0*(C[l2]-C[l1])*(M[l1]-M[l3]);
        else
            return 1.0*(C[l3]-C[l1])*(M[l1]-M[l2]) <= 1.0*(C[l2]-C[l1])*(M[l1]-M[l3]);
    }

    void add(ll m, ll c){
        M.push_back(m);
        C.push_back(c);
        int sz = M.size();
        while(sz>2 && bad(sz-3, sz-2, sz-1)){
            M.erase(M.end()-2);
            C.erase(C.end()-2);
            sz--;
        }
    }

    ll f(int i, ll x) { return M[i]*x + C[i]; }
    ll check(ll x, ll y){
        if(minQuery) return min(x,y);
        else return max(x,y);
    }

    ll query(ll x){
        int l=0, h=M.size()-1;
        ll ans=1e18;
        if( !minQuery ) ans= -1e18;

        while(l+3 <= h){
            int m1=(l+l+h)/3;
            int m2=(l+h+h)/3;
            ll val1 = f(m1, x), val2 = f(m2, x);
            bool ok = (val1 >= val2);
            if(minQuery) ok = (val1 <= val2);
            if(ok)
                ans=check(ans, val1), h=m2-1;
            else
                ans=check(ans, val2), l=m1+1;
        }

        for(int i=l; i<=h; i++)
            ans=check(ans, f(i, x));
        return ans;
    }
    ll queryBS(ll x,int l, int r){
        int mid=(l+r)/2;
        if(minQuery){
            if(mid+1 < M.size() && f(mid + 1, x) < f(mid, x))
                return queryBS(x,mid+1, r);
        }
        else{
            if(mid+1 < M.size() && f(mid+1, x) > f(mid, x))
                return queryBS(x,mid+1, r);
        }
        if(minQuery){
            if(mid-1 >= 0 && f(mid-1, x) < f(mid, x)) 
                return queryBS(x,l, mid-1);
        }
        else{
            if(mid-1 >= 0 && f(mid-1, x) > f(mid, x)) 
                return queryBS(x,l, mid-1);
        }
        return f(mid, x);
  }

    /**
     * will work if
     * decSlop xor minQuery = 0 and x(i)<=x(i+1)
     * decSlop xor minQuery = 1 and x(i)>=x(i+1)
    */
    ll querySP(ll x) {
        int sz = M.size();
        if(ptr >= sz) ptr = sz-1;
        while(ptr < sz-1 && f(ptr, x) > f(ptr+1, x)) ptr++;
        return f(ptr, x);
    }

    void clear(){
        M.clear();C.clear();
        //decSlop = 1; minQuery = 1;
        ptr = 0;
    }
};

ll dp[MAX];

void syntex_error()
{
    ll n;
    CHT h = CHT(1, 1);

    cin>>n;
    ll a[n+5],b[n+5];
    
    for(int i=1; i<=n; i++) cin>>a[i];
    for(int i=1; i<=n; i++) cin>>b[i];

    dp[1] = 0;
    h.add(b[1],dp[1]);
    for(int i=2; i<=n; i++){
        dp[i]=h.query(a[i]);
        h.add(b[i], dp[i]);
    }
   
    cout<<dp[n]<<endl;

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
