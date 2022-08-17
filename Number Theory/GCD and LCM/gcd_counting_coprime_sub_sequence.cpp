/**
    Given an array a consisting of n 
    positive integers, find the number
    of its coprime subsequences(non-empty). Since
    the answer may be very large, print
    it modulo 10^9 + 7.
*/
#include<bits/stdc++.h>
using namespace std;


#define MOD 1000000007
#define MAX 100005

typedef long long ll;

ll cnt[MAX];
ll bigmod(ll n,ll p)
{
    ll temp;
    if(p==0)
        return 1;
     temp=bigmod(n,p/2);
     temp=(temp*temp)%MOD;
    if(p&1)
        temp=(temp*n)%MOD;
    return temp;
}
ll cntSub(ll n)
{
    //total sub seq=2^n
    //-1 for non-empty
    return (bigmod(2LL, n)-1+MOD)%MOD;
}
void syntex_error()
{
    ll n,x,i,j;
    cin>>n;
    for(i=0; i<n; i++)
    {
        cin>>x;
        for(j=1; j*j<=x; j++)
        {
            if(x%j==0)
            {
                cnt[j]++;
                if(j*j!=x)
                    cnt[x/j]++;
            }
        }
    }
    for(i=1; i<MAX; i++)
    {
        cnt[i]=cntSub(cnt[i]);
    }
    for(i=MAX-1; i>0; i--)
    {
        for(j=i+i; j<MAX; j+=i)
            cnt[i]=(cnt[i]-cnt[j]+MOD)%MOD;
    }
    cout<<cnt[1]<<endl;
}

int main()
{
    FAST
    
    ll TC=1LL;

    //cin>>TC;

    while(TC--){
        syntex_error();
    }

    return 0;
}
