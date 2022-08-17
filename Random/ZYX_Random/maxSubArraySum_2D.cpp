#include<bits/stdc++.h>
using namespace std;

#define MAX 111
#define ll long long

ll cum[MAX][MAX];

ll getSum(ll x1, ll y1, ll x2, ll y2)
{
	return cum[x2][y2]-cum[x1-1][y2]-cum[x2][y1-1]+cum[x1-1][y1-1];
}

int32_t main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	ll n,i,j,k,sum;
	cin>>n;
	for(i=1; i<=n; i++)
	{
		for(j=1; j<=n; j++)
		{
			cin>>cum[i][j];
			cum[i][j]+=cum[i-1][j]+cum[i][j-1]-cum[i-1][j-1];
		}
	}

	ll mx=LLONG_MIN;
	for(i=1; i<=n; i++)
	{
		for(j=i; j<=n; j++)
		{
			sum=0;
			for(k=1; k<=n; k++)
			{
				sum+=getSum(i,k,j,k);
				mx=max(mx,sum);
				sum=max(sum,0LL);
			}
		}
	}
	cout<<mx<<endl;
}