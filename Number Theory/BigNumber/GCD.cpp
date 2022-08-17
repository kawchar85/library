/**
    Find GCD(A,B).
    0<=A<=10^18
    0<=B<=10^250
    
    we know gcd(a,b)=gcd(b,a)=gcd(a, b%a)
    a is Long Long, b%a will be Long long
    replace b by b%a.

    https://www.spoj.com/problems/GCD2/
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mod(string a, ll b)
{
    ll temp=0,idx=0;

    while(idx<a.size())
    {
        temp=(temp*10+a[idx++]-'0')%b;
    }
    return temp;
}
ll gcd(ll x,ll y)
{
    if(y==0)
        return x;
    else
        return gcd(y,x%y);
}
int main()
{
    int t,i,j,n;
    ll a,b;
    string s;
    cin>>t;
    for(i=1;i<=t;i++)
    {
        cin>>a>>s;
        if(a==0LL)
            cout<<s<<endl;
        else
        {
            b=mod(s,a);
            cout<<gcd(a,b)<<endl;
        }
    }
    return 0;
}
