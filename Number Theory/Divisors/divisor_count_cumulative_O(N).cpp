#include<bits/stdc++.h>
#define ll long long
using namespace std;
/**
 Cumulative sum of NOD
 CNOD(N)=NOD(1)+NOD(2)+...+NOD(N)
*/
///O(N)
ll CNOD(ll n)
{
    ll i,cnt=0;
    for(i=1; i<=n; i++)
        cnt+=n/i;
    return cnt;
}

int main()
{
    ll n;
    cin>>n;
    cout<<CNOD(n)<<endl;
}
