#include<iostream>
#define ll long long
using namespace std;

///efficient prime checking
bool isPrime(ll n)
{
    if(n<2)  return 0;
    if(n<4)  return 1;
    if(n%2==0 || n%3==0) return 0;
    for(ll i=5; i*i<=n; i=i+6)
        if(n%i==0 || n%(i+2)==0)
           return 0;

    return 1;
}

int main()
{
    ll a;
    cin>>a;
    if(isPrime(a))
        cout<<"Prime\n";
    else
        cout<<"Not prime";
    return 0;
}


