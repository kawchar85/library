//https://vjudge.net/problem/LightOJ-1418

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

#define EPS 1e-9

typedef long long T;

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
    T angle() {return atan2(y,x);}
};

T dot(PT a, PT b){
    return a.x*b.x+a.y*b.y;
}
T cross(PT a, PT b){
    return (a.x*b.y-a.y*b.x);
}
bool operator<(PT p1, PT p2){
    if(fabs(p1.x-p2.x)<EPS)
        return p1.y<p2.y;
    return p1.x<p2.x;
} 

T areaPolygon(vector<PT> &p){
    T area = 0.0;
    for(int i=0, n=p.size(); i<n; i++)
        area += cross(p[i], p[(i+1)%n]);
    return abs(area)/2.0;
}
T point(PT a, PT b)
{
    T x=abs(a.x-b.x);
    T y=abs(a.y-b.y);

    return __gcd(x,y)-1;
}
void syntex_error()
{
    ll i,j,k,l,r,n,m,a,b,c,d,x,y,z;
    ll sum=0LL, mn=LLONG_MAX, mx=LLONG_MIN, cnt=0LL;
    vl v;
    string s;
    
    cin>>n;
    vector< PT > p;

    for(i=0; i<n; i++)
    {
        cin>>x>>y;
        p.pb({x,y});
    }

    ll on_boundary=n;
    ll area=0LL;

    for(i=0; i<n; i++)
    {
        area+=cross(p[i],p[(i+1)%n]);
        on_boundary+=point(p[i],p[(i+1)%n]);
    }
    area/=2;
    if(area<0)
        area*=-1;

    //By pick theorem area=In+(on_boundary/2)-1
    ll inside=area-(on_boundary/2)+1LL;
    cout<<inside<<endl;
}

int32_t main()
{
    FAST
    
    ll TC=1LL,cs=1LL;

    cin>>TC;

    while(TC--){
        CS(cs++);
        syntex_error();
    }

    return 0;
}
