#include<bits/stdc++.h>
#define ll long long
using namespace std;

vector<ll>fact;

///O(sqrt(n))
void Factorization(ll n)
{
    while(n%2==0)
    {
        fact.push_back(2);
        n/=2;
    }

    for(ll i=3; i*i<=n; i+=2)
    {
        while(n%i==0)
        {
            fact.push_back(i);
            n/=i;
        }
    }

    if(n>1)
        fact.push_back(n);
}

int main()
{
    ll n;
    cin>>n;
    Factorization(n);
    for(auto x : fact)
        cout<<x<<" ";
}
