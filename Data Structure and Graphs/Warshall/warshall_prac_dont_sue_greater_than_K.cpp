//https://codeforces.com/gym/310122/problem/F

#include <bits/stdc++.h>
using namespace std;
#define ll long long


ll dp[205][205][205];
vector< pair<ll,ll> > v;
int n;


void warshall(ll n)
{
    int i,j,k;
    for(ll k=1; k<=n; k++)
        for(ll i=1; i<=n; i++)
            for(ll j=1; j<=n; j++)
            {
                ll x=v[k].second;
                dp[k][i][j]=min(dp[k-1][i][j], dp[k-1][i][x]+dp[k-1][x][j]);
                dp[k][j][i]=dp[k][i][j];
            }
}
 
int main()
{
 
    int t,q,x,tc=1,u,vv,w,i,j,k;
    cin >> t;
    while(t--)
    {
 
        cout << "Case #" << tc << ": " ;
        tc++;
        v.clear();
 
        v.push_back({-1,0});
        cin>>n>>q;
        for(i=1; i<=n; i++)
        {
            cin>>x;
            v.push_back({x,i});
        }
        for(i=1; i<=n; i++)
        {
            for(j=1; j<=n; j++)
            {
                cin>>x;
                dp[0][i][j]=x;
                dp[0][j][i]=x;
            }
        }
        sort(v.begin(),v.end());
    
        warshall(n);
 
        while(q--)
        {
            cin>>u>>vv>>w;
            k=0;
            for(i=1; i<=n; i++)
            {
                if(v[i].first<=w)
                    k=i;
            }
            cout<<dp[k][u][vv]<<endl;
        }
    }
 
    return 0;
}
