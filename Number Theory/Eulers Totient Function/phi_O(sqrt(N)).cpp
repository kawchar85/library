#include<stdio.h>
typedef long long ll;

///O(sqrt(n))
ll phi(ll n)
{
    ll i,result=n;
    for(i=2;i*i<=n;i++)
    {
        if(n%i==0)
        {
            while(n%i==0)
                n/=i;
            ///result-=result/i; same as result=result*(i-1)/i
            result=result/i*(i-1);
        }
    }
    if(n>1)
         result=result/n*(n-1);
    return result;

}

int main()
{
    ll x;
    scanf("%lld",&x);
    printf("%lld",phi(x));
    return 0;
}
