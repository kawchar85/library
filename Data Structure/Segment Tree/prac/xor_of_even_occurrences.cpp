//link: https://vjudge.net/problem/Gym-102800M


/**
    "If you have an apple and I have an apple and
    we exchange apples then you and I will still
    each have one apple. But if you have an idea
    and I have an idea and we exchange these
    ideas, then each of us will have two ideas."
                        -George Bernard Shaw
*/
#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 500005

#define CS(i) cout<<"Case "<<i<<": "

typedef long long ll;

ll arr[MAX];
int N;

struct info{
    ll sum;
    info(){
        sum=0;
    }
    info(ll x){
        sum=x;
    }
};
info tree[3*MAX];

info leaf(int i){
    return info(arr[i]);
}
info outOfRange(){
    return info(0);
}
info Set(ll x){
    return info(x);
}
info merge(info x, info y){
    info temp;
    temp.sum=x.sum^y.sum;
    return temp;
}


void build(int node, int l,int r)
{
    if(l==r)
    {
        tree[node]=leaf(l);
        return;
    }
    int mid=(l+r)/2;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);
    tree[node]=merge(tree[node*2],tree[2*node+1]);
}

info query(int node,int l,int r,int i,int j)
{
    if(i>r || j<l)
        return outOfRange();
    if(l>=i && r<=j)
        return tree[node];
    int mid=(l+r)/2;
    auto x=query(node*2,l,mid,i,j);
    auto y=query(node*2+1,mid+1,r,i,j);
    return merge(x,y);
}

void update(int node,int l,int r,int pos,ll val)
{
    if(pos>r || pos<l)
        return;
    if(l==r)
    {
        tree[node]=Set(val);
        return;
    }
    int mid=(l+r)/2;
    if(pos<=mid)
        update(node*2,l,mid,pos,val);
    else
        update(node*2+1,mid+1,r,pos,val);

    tree[node]=merge(tree[node*2],tree[2*node+1]);
}
void build(int n){
    N=n;
    //build(1,0,N-1);
}
void update(int pos, ll val){
    update(1,0,N-1,pos,val);
}
ll query(int x, int y){
    auto ans = query(1,0,N-1,x,y); 
    return ans.sum;
}

ll cum[MAX],ans[MAX];
vector<pair<ll,ll>> q[MAX]; //{l,id}

ll getXor(int l, int r){
	ll ans = cum[r];
	if(l) ans ^= cum[l-1];
	return ans;
}

void syntex_error(){
	
    ll n,m,i,j,k,a,b,c,x,y,z;
    vector<ll> v;

    cin>>n>>k;
    for(i=0; i<n; i++){
    	cin>>x;

    	if(i) cum[i] = cum[i-1];
    	cum[i] ^= x;

    	v.push_back(x);
    }

    for(i=0; i<k; i++){
    	cin>>x>>y;
    	x--;y--;
    	q[y].push_back({x,i});
    }

    map<ll,ll> last;

    build(n);
    for(i=0; i<n; i++){
    	if(last.find(v[i]) != last.end()){
    		update(last[v[i]], 0LL);
    	}

    	update(i, v[i]);
    	last[v[i]] = i;

    	for(auto p : q[i]){
    		//unique^(total/odd's) = even's
    		ans[p.second] = getXor(p.first, i)^query(p.first, i);
    	}
    }

    for(i=0; i<k; i++)
    	cout<<ans[i]<<endl;

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
