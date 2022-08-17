///language C++ ( gcc 8.3)
#include<bits/stdc++.h>
using namespace std;

using ll = uint64_t;
using u128 = __uint128_t;

ll BigMod(ll n, ll p, ll mod)
{
    ll result=1;
    n%=mod;
    while(p>0)
    {
        if(p&1)
            result = ( (u128) result * n) % mod;
        p >>= 1;
        n = ( (u128) n * n ) % mod;
    }
    return result;
}

bool isComposite(ll n, ll a, ll d, int s)
{
    ll x=BigMod(a, d, n);
    if(x==1LL || x==n-1)
        return false;
    for(int r=1; r<s; r++)
    {
        x=( (u128) x * x ) % n;
        if(x==n-1)
            return false;
    }
    return true;
}

//returns true if n is probably prime, else returns false.
bool MillerRabin(ll n)
{
    int s=0;
    ll d=n-1;
    while((d&1) == 0)
    {
        d >>= 1;
        s++;
    }

    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    {
        if(n==a)
            return true;
        if(isComposite(n, a, d, s))
            return false;
    }
    return true;
}

bool isPrime(ll n)
{
    if(n==2LL || n==3LL)
        return true;
    if(n<5LL || n%2==0 || n%3==0)
        return false;
    return MillerRabin(n);
}

int main()
{
    
    ll n=999999999999999989LL;
    //cin>>n;
    if(isPrime(n))
    {
        cout<<"Prime"<<endl;
    }
    else
    {
        cout<<"Not prime"<<endl;
    }    
 
    return 0;
}  
