//https://vjudge.net/problem/Kattis-largesttriangle

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
    
};

ostream& operator<<(ostream& os, PT p) {
    return os << "("<< p.x << "," << p.y << ")";
}

bool operator<(PT p1, PT p2)
{
    if(p1.x==p2.x)
        return p1.y<p2.y;
    return p1.x<p2.x;
} 

T cross(PT a, PT b){
    return (a.x*b.y-a.y*b.x);
}

//co-linear-->0
//CCW-->1
//CW-->-1
int orientation(PT A, PT B, PT C) {
    T x=cross(B-A, C-B); //ABxBC
    if(fabs(x)<EPS)
        return 0;
    if(x>0)
        return 1;
    return -1;
}

bool cw(PT a, PT b, PT c){
    return orientation(a,b,c)==-1;
}
bool ccw(PT a, PT b, PT c){
    return orientation(a,b,c)==1;
}
void convex_hull(vector<PT> &v){
    int n=v.size();
    if(n<3) return;

    sort(v.begin(), v.end());
    PT p1=v[0], p2=v.back();
    vector<PT> up,down;
    up.push_back(p1);
    down.push_back(p1);

    for(int i=1; i<n; i++)
    {
        if(i+1==n || cw(p1, v[i], p2))
        {
            while(up.size()>1 && !cw(up[up.size()-2], up[up.size()-1], v[i]))
                up.pop_back();
            up.push_back(v[i]);
        }

        if(i+1==n || ccw(p1, v[i], p2))
        {
            while(down.size()>1 && !ccw(down[down.size()-2], down[down.size()-1], v[i]))
                down.pop_back();
            down.push_back(v[i]);
        }
    }

    v.clear();
    for(int i=0; i<(int)up.size(); i++)
        v.push_back(up[i]);
    for(int i=down.size()-2; i>0; i--)
        v.push_back(down[i]);
}

T getArea(PT a, PT b, PT c){
    return abs(a.x*b.y+b.x*c.y+c.x*a.y-b.x*a.y-c.x*b.y-a.x*c.y);
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    vector<PT> v;
    int i,j,k,n;
    T x,y;
    cin>>n;
    for(i=0; i<n; i++)
    {
        cin>>x>>y;
        v.push_back({x,y});
    }
    convex_hull(v);
    n=v.size();

    T ans=0;
    
    for(i=0; i<n; i++)
    {
        for(j=i+1,k=i+2; j<n; j++)
        {
            while(k+1<n && getArea(v[i],v[j],v[k])<=getArea(v[i],v[j],v[k+1]))
                k++;
            ans=max(ans, getArea(v[i],v[j],v[k]));
        }
    }

    cout<<(ans/2);
    if(ans&1) cout<<".5";
    cout<<endl;

}
