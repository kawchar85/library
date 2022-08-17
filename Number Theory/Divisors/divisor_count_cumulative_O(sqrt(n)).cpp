#include<bits/stdc++.h>
#define ll long long
using namespace std;

/**
 Cumulative sum of NOD
 CNOD(N)=NOD(1)+NOD(2)+...+NOD(N)
*/

///O(sqrt(n))
ll CNOD(ll n)
{
    ll i,cnt=0,sq=sqrt(n);
    for(i=1; i<=sq; i++)
        cnt+=(n/i)-i;
    cnt*=2;
    cnt+=sq;
    return cnt;
}

int main()
{
    ll n;
    cin>>n;
    cout<<CNOD(n);
}
