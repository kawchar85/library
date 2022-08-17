/**
    https://cses.fi/problemset/task/2182/
*/
#include<bits/stdc++.h>
using namespace std;
 
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
typedef long long ll;


ll BigMod(ll n,ll p)
{
    ll temp;
    if(p==0)
        return 1LL;
    temp=BigMod(n,p/2);
    temp=(temp*temp)%MOD;
    if(p&1)
        temp=(temp*n)%MOD;
    return temp;
}

ll inverse(ll a, ll m){
    return BigMod(a, m-2);
}

void syntex_error()
{
    ll n,p,a,i;
    ll nod=1,tnod=1,pod=1,sod=1;

    cin>>n;
 
    for(i=0; i<n; i++)
    {
        cin>>p>>a;

        nod=nod*(a+1)%MOD;
        sod=sod*(BigMod(p, a+1)-1+MOD)%MOD*inverse(p-1, MOD)%MOD;
        pod=BigMod(pod, a+1)*BigMod(BigMod(p, (a*(a+1)/2)), tnod)%MOD;
        tnod=tnod*(a+1)%(MOD-1);
    }

    cout<<nod<<" "<<sod<<" "<<pod<<endl;
}
 
int32_t main()
{
    FAST
    
    ll TC=1LL,cs=1LL;
 
    //cin>>TC;
 
    while(TC--){
        //CS(cs++);
        syntex_error();
    }
 
    return 0;
}
