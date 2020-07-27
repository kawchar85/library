#include<bits/stdc++.h>
using namespace std;
#define ll long long

///Log(n) calculating...
ll LOG(ll n, ll b)
{
    return (n>=b)? 1+LOG(n/b, b) : 0LL;
}

int main()
{
    ll n,b;
    cin>>n>>b;
    cout<<LOG(n,b);
}

