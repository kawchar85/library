#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MXN             100000+10
#define M1              1000000009
#define M2              1000004119
#define B1              1021
#define B2              1297

ll H1[MXN] , H2[MXN] , pow1[MXN] , pow2[MXN];

void pre()
{
    pow1[0] = pow2[0] = 1;
    for(ll i = 1 ; i<MXN ; i++){
        pow1[i] = (pow1[i-1] * B1)%M1;
        pow2[i] = (pow2[i-1] * B2)%M2;
    }
}

void calculate(string str)
{
    ll n = str.size();
    for(ll i = 1 ; i<=n ; i++){
        H1[i] = (B1*H1[i-1] + str[i-1] - 'a' + 1)%M1;
        H2[i] = (B2*H2[i-1] + str[i-1] - 'a' + 1)%M2;
    }
}

ll getHash1(ll lft , ll rgt)
{
    ll len = rgt - lft + 1;
    ll ret = (H1[rgt] - H1[lft - 1]*pow1[len]%M1 + M1)%M1;
    return ret;
}

ll getHash2(ll lft , ll rgt)
{
    ll len = rgt - lft + 1;
    ll ret = (H2[rgt] - H2[lft - 1]*pow2[len]%M2 + M2)%M2;
    return ret;
}


///Find s in t.
int main()
{
    pre();

    string s,t;
    cin>>t>>s;
    calculate(t);

    ll n = s.size();
    ll h1=0,h2=0;
    for(ll i = 1 ; i<=n ; i++){
        h1 = (B1*h1 + s[i-1] - 'a' + 1)%M1;
        h2 = (B2*h2 + s[i-1] - 'a' + 1)%M2;
    }

    for(ll i=1; i+s.size()<=t.size(); i++ )
    {
        if(getHash1(i, i+s.size()-1)==h1 && getHash2(i, i+s.size()-1)==h2)
            cout<<i<<" ";
    }


    return 0;
}
