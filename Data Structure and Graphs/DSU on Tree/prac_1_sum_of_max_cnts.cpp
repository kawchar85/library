//https://codeforces.com/contest/600/problem/E

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 200005
typedef long long ll;

vector<ll> adj[MAX];

int val[MAX];
int cnt[MAX];
bool big[MAX];
int sz[MAX];

ll ans[MAX];
ll sum;
int mx_cnt;

void processQuery(int v){
	ans[v] = sum;
	//cout<<v<<" "<<mx_cnt<<" "<<sum<<endl;
}
void getSize(int v, int p){
	sz[v] = 1;
	for(auto u : adj[v]){
		if( u == p ) continue;
		getSize(u, v);
		sz[v] += sz[u];
	}
}

void add(int v, int p, int x){
	cnt[ val[v] ] += x;
	if(cnt[ val[v] ] > mx_cnt) sum=0, mx_cnt = cnt[ val[v] ];
	if(cnt[ val[v] ] == mx_cnt) sum += val[v];

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
		sum = 0;
		mx_cnt = 0;
	}
}
void process(int root = 1){
	getSize(root, -1);
	dfs(root, -1, 0);
}

void syntex_error(){
	
    ll n,m,i,j,k,a,b,c,x,y,z;
    
    cin>>n;
    for(i=1; i<=n; i++)
    	cin>>val[i];

    for(i=1; i<n; i++){
    	cin>>x>>y;

    	adj[x].push_back(y);
    	adj[y].push_back(x);
    }

    process();
    for(i=1; i<=n; i++)
    	cout<<ans[i]<<" ";
    
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
