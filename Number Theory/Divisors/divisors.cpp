#include<bits/stdc++.h>
#define ll long long
using namespace std;

vector<ll>D;
void Divisor(ll n)
{
    for(ll i=1; i*i<=n; i++)
    {
        if(i*i==n)
            D.push_back(i);
        else if(n%i==0)
        {
            D.push_back(i);
            D.push_back(n/i);
        }
    }
}

int main()
{
    ll n;
    cin>>n;
    Divisor(n);
    for(auto i : D)
        cout<<i<<" ";
}
