#include<bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define MAX 2003

typedef long long ll;

ll cum[MAX];
ll arr[MAX];

ll cum2[MAX][MAX];
ll arr2[MAX][MAX];

void init(int n){
    cum[0]=0;
    for(int i=1; i<=n; i++)
        cum[i]=cum[i-1]+arr[i];
}
ll get(int l, int r){
    return cum[r]-cum[l-1];
}

void init(int n, int m){
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
        {
            cum2[i][j]=cum2[i-1][j]+cum2[i][j-1]-cum2[i-1][j-1]+arr2[i][j];
        }
    }
}

//(a,b)-->(c,d) 1 based
ll get(ll a, ll b, ll c, ll d)
{
   return (cum2[c][d]-cum2[a-1][d]-cum2[c][b-1]+cum2[a-1][b-1]);
}

