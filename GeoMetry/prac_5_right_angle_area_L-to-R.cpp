//https://vjudge.net/problem/Gym-101992I

/**
    "If you have an apple and I have an apple and
    we exchange apples then you and I will still
    each have one apple. But if you have an idea
    and I have an idea and we exchange these
    ideas, then each of us will have two ideas."
                        -George Bernard Shaw
*/
#include<bits/stdc++.h>
using namespace std;

#define clean(x,y) memset(x,y,sizeof(x));
#define pb push_back
#define F first
#define S second
#define LB lower_bound
#define UB upper_bound
#define ALL(v) v.begin(),v.end()
#define PI acos(-1.0)
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define printa(a,L,R) for(int ii=L; ii<R; ii++) cout<<a[ii]<<" \n"[ii==R-1]
#define printv(a) printa(a,0,(int)a.size())
#define Unique(a) sort(ALL(a)); (a).resize(unique(ALL(a)) - (a).begin())
#define SZ(v) (int)v.size()
#define MOD 1000000007
#define MAX 200005
#define DEBUG 0

#define dbg(x) if(DEBUG) cout<<(#x)<<"="<<(x)<<":\n"
#define CS(i) cout<<"Case "<<i<<": "

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector< pii > vpi;
typedef vector< pll > vpl;
typedef map<int, int> mii;
typedef map<ll, ll> mll;

#define EPS 1e-11
#define PI_2 acos(0.0)
typedef long long int T;

struct PT{
    T x,y;
    PT() {}
    PT(T x, T y): x(x),y(y) {}
    
    PT operator+(PT p) {return {x+p.x, y+p.y};}
    PT operator-(PT p) {return {x-p.x, y-p.y};}
    PT operator*(T d) {return {x*d, y*d};}
    PT operator/(T d) {return {x/d, y/d};}
    PT operator*(PT p) {return {x*p.x-y*p.y, x*p.y+y*p.x};}
    PT operator/(PT p) {return {((*this)*p.conj())/(p*p.conj()).x};} 

    T sq() {return x*x + y*y;}
    T abs() {return sqrt(sq());}
    PT unit() {return (*this)/abs();}
    PT conj() {return {x,-y};}
    PT perp() {return {-y,x};}
    long double angle() {return atan2(y,x);}
};

bool operator<(PT p1, PT p2){
    if(p1.x==p2.x)
        return p1.y<p2.y;
    return p1.x<p2.x;
} 

T cross(PT a, PT b){
    return (a.x*b.y-a.y*b.x);
}
bool eql(long double a, long double b){
    return fabs(a-b)<EPS;
}
bool eql(PT a, PT b){
    return fabs(a.x-b.x)<EPS && fabs(a.y-b.y)<EPS;
}

void syntex_error()
{
    ll i,j,k,l,r,n,m,a,b,c,d,x,y,z;
    ll sum=0LL, mn=LLONG_MAX, mx=LLONG_MIN, cnt=0LL;
    vl v;
    string s;
    
    cin>>n>>l>>r;
    l*=2,r*=2;

    PT temp;
    vector<PT> p;    
    vector< pair<long double, PT> >slop;

    for(i=0; i<n; i++)
    {
        cin>>x>>y;
        p.pb(PT(x,y));
    }

    for(i=0; i<n; i++)
    {
        slop.clear();
        for(j=0; j<n; j++)
        {
            if(i==j) continue;
            temp=p[j]-p[i];
            slop.pb({temp.angle(),temp});
        }

        m=SZ(slop);
        sort(ALL(slop));

        for(j=0; j<m; j++)
            slop.pb({slop[j].F+2.0*PI, slop[j].S});

        for(j=0,k=0; j<m; j++)
        {
            ll sz=j+m;
            while(k<sz  && k<SZ(slop) && (slop[k].F-slop[j].F+EPS)<(PI_2))
                k++;

            x=k;
    
            while(x<SZ(slop) && x<sz && eql(slop[x].F-slop[j].F, PI_2)){
                ll area=abs(cross(slop[j].S, slop[x].S));
                
                if(l<=area && area<=r)
                    sum++;
                x++;
            }
        }
    }

    cout<<sum<<endl;
}

int32_t main()
{
    FAST
    freopen("points.in", "r", stdin);
    
    ll TC=1LL,cs=1LL;

    cin>>TC;

    while(TC--){
        //CS(cs++);
        syntex_error();
    }

    return 0;
}
