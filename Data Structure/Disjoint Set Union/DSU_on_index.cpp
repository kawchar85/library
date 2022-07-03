/**
    You will be given an array A of n integers and q 
    operations. There are two types of operations:

    1 x y, for this operation, you should replace all 
      the occurrences of element x in the array with y
    2 idx, output the value A[idx]

    https://vjudge.net/problem/Toph-unbelievable-array
 */

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 200005

#define CS(i) cout<<"Case "<<i<<":\n"
typedef long long ll;


ll par[MAX],idx[MAX], arr[MAX];

ll findPar(ll v){
    if(par[v] == v) return v;
    return par[v] = findPar(par[v]);
}

void union_sets(ll v, ll p){ //new par=p
    v=findPar(v);
    p=findPar(p);
    par[v]=p;
}

void translate(ll x, ll y){ //x-->y
    ll id_x = idx[x];
    ll id_y = idx[y];
    if(x == y || id_x == -1) return;

    if(id_y == -1){ //1st occu of y
        idx[y] = id_x;
        arr[id_x] = y; //update value
    } else { //merge x's with old y
        union_sets(id_x, id_y);
    }
    idx[x]=-1;
}
void init(ll n){

    memset(idx, -1, sizeof idx);
    for(int i=0; i<MAX; i++) par[i]=i;
    for(int i=1; i<=n; i++){
        int id = idx[arr[i]]; //index of current element
        if(id == -1) idx[arr[i]] = i; //1st occurence
        else union_sets(i, id); //par[i] = old occu
    }
}

void syntex_error(){
    ll n,q,x,y,t;

    cin>>n>>q;

    for(int i=1; i<=n; i++)
        cin>>arr[i];

    init(n);
    while(q--){
        cin>>t;

        if(t == 1){
            cin>>x>>y;
            translate(x,y);
        }
        else {
            cin>>x;
            cout<<arr[findPar(x)]<<endl;
        }
    }    
}

int32_t main()
{
    FAST
    
    ll TC=1LL,cs=1LL;

    cin>>TC;

    while(TC--){
        CS(cs++);
        syntex_error();
    }

    return 0;
}
