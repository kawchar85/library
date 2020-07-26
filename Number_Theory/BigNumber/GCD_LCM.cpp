#include<bits/stdc++.h>
#include<string>
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
ll gcd(string x,ll y)
{
    if(y==0)
        return stoll(x);
    else
        return gcd(to_string(y),mod(x,y));
}

string lcm(string x, ll y)
{
    ll a=y/gcd(x,y);
    return mul(x,a);
}

int main()
{
    int t,i,j,n;
    ll a,b;
    scanf("%d",&t);
    for(i=1;i<=t;i++)
    {
        scanf("%d %lld",&n,&b);
        string ans=to_string(b);
        for(j=1;j<n;j++)
        {
            scanf("%lld",&a);
            ans=lcm(ans,a);
        }
        printf("Case %d: ",i);
        cout<<ans<<"\n";
    }
    return 0;
}

