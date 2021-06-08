/**
    Given N distinct points in
    Euclidean 2D space, compute
    the minimum (squared) distance
    between any two distinct points.

    https://cses.fi/problemset/task/2194/
*/

#include<bits/stdc++.h>
using namespace std;
#define PI acos(-1.0)
#define EPS 1e-9
 
typedef unsigned long long ll;
 
//typedef long double T;
typedef long long T;
 
struct PT{
    T x,y; int id;
    PT() {}
    PT(T x, T y, int id): x(x),y(y), id(id) {}
};
 
struct cmp_x{
    bool operator()(const PT &a, const PT &b) const {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }
};
 
struct cmp_y{
    bool operator()(const PT &a, const PT &b) const {
        return a.y < b.y;
    }
};
 
int n;
vector<PT> p;
vector<PT> t;
 
ll mindist;
pair<int, int> best_pair;
 
void upd_ans(const PT &a, const PT &b){
    ll dist = (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
    if(dist < mindist){
        mindist = dist;
        best_pair = {a.id, b.id};
    }
}
 
 
//[l,r)
void rec(int l, int r)
{
    if(r-l <= 3)
    {
        for(int i = l; i < r; ++i)
        {
            for(int j = i + 1; j < r; ++j) {
                upd_ans(p[i], p[j]);
            }
        }
        sort(p.begin() + l, p.begin() + r, cmp_y());
        return;
    }
 
    int m = (l + r) >> 1;
    int midx = p[m].x;
    rec(l, m);
    rec(m, r);
 
    merge(p.begin()+l, p.begin()+m, p.begin()+m, p.begin()+r, t.begin(), cmp_y());
    copy(t.begin(), t.begin()+r-l, p.begin()+l);
 
    int tsz = 0;
    for(int i = l; i < r; ++i)
    {
        if(abs(p[i].x - midx) < mindist)
        {
            for (int j = tsz - 1; j >= 0 && p[i].y - t[j].y < mindist; --j)
                upd_ans(p[i], t[j]);
            t[tsz++] = p[i];
        }
    }
}
 
void closestPair(int n){
    t.resize(n);
    sort(p.begin(), p.end(), cmp_x());
    mindist = (ll)18446744073709551610;
    rec(0, n);
}
 
void solve(){
    T n,x,y,m;
 
    cin>>n;
    p.clear();
    for(int i=0; i<n; i++)
    {
        cin>>x>>y;
        p.push_back(PT(x,y,i));
    }
    closestPair(n);
    cout<<mindist<<endl;
 
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("angle1.in","r", stdin);
    //freopen("angle1.out","w", stdout);
 
    int t=1;
    //cin>>t;
 
    while(t--){
        solve();
    }
}
