//https://vjudge.net/problem/Gym-102361A

#include<bits/stdc++.h>
using namespace std;
#define PI acos(-1.0)
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

    PT conj() {return {x,-y};}
    PT perp() {return {-y,x};}
};


ostream& operator<<(ostream& os, PT p) {
    return os << "("<< p.x << "," << p.y << ")";
}

bool operator<(PT p1, PT p2){
    if(fabs(p1.x-p2.x)<EPS)
        return p1.y<p2.y;
    return p1.x<p2.x;
}

T Value(PT p){
    T base=2500005003LL;
    return p.x*base+p.y;
}
T slope(PT p){
    if(p.x==0)
        p=PT(0,1);
    else if(p.y==0)
        p=PT(1,0);
    else
    {
        if(p.x<0)
        {
            p.x*=-1;
            p.y*=-1;
        }
        T g=__gcd(abs(p.x), abs(p.y));
        p.x/=g;
        p.y/=g;
    }
    return Value(p);
}
T perp_slop(PT p){
    return slope(p.perp());
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);

    T i,j,k,n,q;
    unordered_map<T,T> cnt;

    //cin>>n>>q;
    scanf("%lld %lld", &n, &q);

    PT p[n+5],A[n+5];
    T ans[n+5];

    for(i=0; i<n; i++)
        scanf("%lld %lld", &p[i].x, &p[i].y);
        //cin>>p[i].x>>p[i].y;

    for(i=0; i<q; i++)
    {
        //cin>>A[i].x>>A[i].y;
        scanf("%lld %lld", &A[i].x, &A[i].y);

        cnt.clear();
        T sum=0;
        //Right angle in A
        for(j=0; j<n; j++)
            cnt[slope(p[j]-A[i])]++;
        for(j=0; j<n; j++)
            sum+=cnt[perp_slop(p[j]-A[i])];
        sum/=2;

        ans[i]=sum;

    }

    //Right angle not in A
    for(j=0; j<n; j++)
    {
        cnt.clear();
        for(k=0; k<n; k++)
        {
            if(j==k) continue;
            cnt[slope(p[j]-p[k])]++;
        }
        for(i=0; i<q; i++)
            ans[i]+=cnt[perp_slop(p[j]-A[i])];
    }
    for(i=0; i<q; i++)
        printf("%lld\n", ans[i]);
        //cout<<ans[i]<<endl;

}
