#include<bits/stdc++.h>
#include<string>
#define MAX 100000002
#define sz 10004
#define p_sz 5761500
#define pb push_back
using namespace std;
typedef long long ll;
 
unsigned store[p_sz];
 
int prime[p_sz],cnt;
int marked[MAX/64 + 2];
 
#define isOn(x) (marked[x/64] & (1<<((x%64)/2)))
#define setOn(x)  marked[x/64] |= (1<<((x%64)/2))
 
void sieve()
{
    int i,j;
    for(i=3; i<sz; i+=2)
        if(!isOn(i))
            for(j=i*i; j<MAX; j+=i+i)
                setOn(j);
    prime[cnt++]=2;
    for(i=3; i<MAX; i+=2)
        if(!isOn(i)) prime[cnt++]=i;
}
 
void pre_calculation()
{
    store[0]=prime[0];
    for(int i=1; i<cnt; i++)
    {
        store[i]=store[i-1]*prime[i];
    }
}
 
unsigned calculation(int n)
{
    unsigned ans=1;
    ll mul;
    for(int i=0; prime[i]*prime[i]<=n; i++)
    {
        mul=(ll)prime[i];
        while(mul*prime[i]<=n)
        {
            mul*=prime[i];
            ans*=prime[i];
        }
    }
    return ans;
}
 
int main()
{
    sieve();
    //cout<<prime.size()<<" : "<<prime.back()<<endl;
    pre_calculation();
    int t,cs,n,pos;
    unsigned ans;
    scanf("%d",&t);
    for(cs=1; cs<=t; cs++)
    {
        scanf("%d",&n);
        pos = upper_bound(prime, prime+cnt, n) - prime;
        ans=store[pos-1];
        ans*=calculation(n);
        printf("Case %d: %u\n",cs,ans);
    }
    return 0;
}
