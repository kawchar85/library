#include<bits/stdc++.h>
#define ll long long
using namespace std;

///O(sqrt(n))
bool isPrime(ll n)
{
    if(n<2LL) return 0;
    if(n==2LL) return 1;
    if(n%2==0) return 0;
    for(ll i=3LL; i*i<=n; i+=2)
        if(n%i==0) return 0;
    return 1;
}

int main()
{
    ll n;
    while(cin>>n)
    {
        if(isPrime(n))
            cout<<"Prime\n";
        else
            puts("Not Prime");
    }
    return 0;
}
