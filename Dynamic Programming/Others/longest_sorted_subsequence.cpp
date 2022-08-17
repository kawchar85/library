
#include<bits/stdc++.h>
using namespace std;

#define clean(x,y) memset(x,y,sizeof(x));
#define pb push_back
#define F first
#define S second
#define ALL(v) v.begin(),v.end()
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);


typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector< pii > vpi;
typedef vector< pll > vpl;


ll sortedLen(vpl &v)
{
    sort(ALL(v));

    ll mx=0;
    ll len=1;
    for(ll i=1; i<SZ(v); i++)
    {
        if(v[i].S<v[i-1].S)
        {
            mx=max(mx,len);
            len=1;
        }
        else
            len++;
    }
    mx=max(mx,len);
    return mx;
}

void syntex_error()
{
    ll i,j,k,l,r,n,m,a,b,c,x,y,z,sum=0LL;
    vpl v;

    cin>>n;
    for(i=0; i<n; i++)
    {
        cin>>x;
        v.pb({x,i});
    }
    
    cout<<sortedLen(v)<<endl;

}

int main()
{
    FAST
    
    ll TC=1LL;

    cin>>TC;

    while(TC--){
        syntex_error();
    }

    return 0;
}

