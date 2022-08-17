#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll EGCD(ll a, ll b, ll &x, ll &y)
{
    if(a==0)
    {
        x=0; y=1;
        return b;
    }
    ll x1,y1;
    ll d = EGCD(b%a, a, x1, y1);
    x = y1 - (b/a)*x1;
    y = x1;
    return d;
}

void inverse(ll a, ll m)
{
    ll g,x,y;
    g = EGCD(a,m,x,y);
    if(g!=1)
        cout<<"No solution\n";
    else
    {
        x=(x%m+m)%m;
        cout<<x<<"\n";
    }
}

int main()
{

}
