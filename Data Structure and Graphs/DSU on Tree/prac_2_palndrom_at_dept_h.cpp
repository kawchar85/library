//https://codeforces.com/contest/570/problem/D

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 500005
typedef long long ll;

vector<ll> adj[MAX];

int val[MAX];
int cnt[MAX][27];
bool big[MAX];
int sz[MAX];
int dept[MAX];

ll ans[MAX];
vector<pair<ll,ll>> query[MAX]; //v-->h,id

void processQuery(int v){
	for(auto p : query[v]){
		int h = p.first;
		int id = p.second;

		int odd = 0;
		for(int i=0; i<26; i++)
		{
			odd += (cnt[h][i]%2);
		}

		ans[id] = (odd<2);
	}
}
void getSize(int v, int p){
	sz[v] = 1;
	dept[v] = 1 + dept[p];

	for(auto u : adj[v]){
		if( u == p ) continue;
		getSize(u, v);
		sz[v] += sz[u];
	}
}

void add(int v, int p, int x){
	cnt[dept[v]][val[v]] += x;

	for(auto u : adj[v])
		if(u != p && !big[u])
			add(u, v, x);
}

void dfs(int v, int p, bool keep){
	int mx = -1, bigChild = -1;
	for(auto u : adj[v])
		if(u != p && sz[u] > mx)
			mx = sz[u], bigChild = u;
	for(auto u : adj[v])
		if(u != p && u != bigChild)
			dfs(u, v, 0);
	if(bigChild != -1)
		dfs(bigChild, v, 1), big[bigChild] = 1;
	add(v, p, 1);

	processQuery(v);

	if(bigChild != -1)
		big[bigChild] = 0;
	if(keep == 0){
		add(v, p, -1);
		
	}
}
void process(int root = 1){
	
	getSize(root, 0);
	dfs(root, -1, 0);
}

void syntex_error(){
	
    ll n,m,i,j,k,a,b,c,x,y,z;
    string s;

    cin>>n>>m;
    for(i=2; i<=n; i++){
    	cin>>x;

    	adj[x].push_back(i);
    	adj[i].push_back(x);
    }
    cin>>s;
    for(i=1; i<=n; i++)
    	val[i] = s[i-1]-'a';
    
    for(i=0; i<m; i++){
    	cin>>x>>y;
    	query[x].push_back({y, i});
    }


    process();
    
    for(i=0; i<m; i++){
    	if(ans[i]) cout<<"Yes\n";
    	else cout<<"No\n";
    }

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
