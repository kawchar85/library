#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define MAX 1000006
using namespace std;

bool siv[MAX];
vector<ll>prime;
ll lcm[MAX];

///max_number obdi prime ber kore rakhbo
void sieve()
{
    ll i,j;
    for(i=3; i*i<MAX; i+=2)
        if(!siv[i])
            for(j=i*i; j<MAX; j+=i+i)
                siv[j]=1;
    prime.pb(2);
    for(i=3; i<MAX; i+=2)
        if(!siv[i]) prime.pb(i);
}

void prime_factorization(ll n)
{
    ll i,sq=sqrt(n),mul;
    for(i=0; i<prime.size()&&prime[i]<=sq; i++)
    {
        if(n%prime[i]==0)
        {
            mul=1;
            while(n%prime[i]==0)
            {
                n/=prime[i];
                mul*=prime[i];
            }
           lcm[prime[i]]=max(lcm[prime[i]],mul);
           sq=sqrt(n);
        }
    }

    if(n>1)
        lcm[n]=max(lcm[n],n);
}

string mul(string a, ll x)
{
    string ans,k;
    ll temp,carray=0,r;
    for(int i=a.size()-1; i>=0; i--)
    {
        temp= (a[i]-'0')*x+carray;
        r=temp%10;
        carray=temp/10;
        ans+=to_string(r);
    }
    if(carray)
    {
        k=to_string(carray);
        reverse(k.begin(),k.end());
        ans+=k;
    }
    reverse(ans.begin(),ans.end());

    return ans;
}

int main()
{
    sieve();
    int t,i,j,k,n;
    ll a,x,y,z;
    scanf("%d",&t);
    for(i=1;i<=t;i++)
    {
        memset(lcm,0,sizeof lcm);
        scanf("%d",&n);
        for(j=0;j<n;j++)
        {
            scanf("%lld",&a);
            prime_factorization(a);
        }

        string ans="1";
        for(k=0; k<prime.size(); k++)
        {
            if(lcm[prime[k]])
                ans=mul(ans,lcm[prime[k]]);
        }
        printf("Case %d: ",i);
        cout<<ans<<"\n";
    }


    return 0;
}
