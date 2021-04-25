/**
    https://codeforces.com/contest/459/problem/D

    use pair for multiset
*/
#include<bits/stdc++.h>
using namespace std;
 
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 1000006

typedef long long ll;
typedef pair<int,int> pii;


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<pii, null_type,less<pii>, rb_tree_tag,tree_order_statistics_node_update>
int ID;
//find_by_order(),order_of_key()

int arr[MAX];
void solve()
{
    ll n,m,q,a,b,x;
    ordered_set s;

    cin>>n;
    map<int,int> preF,sufF;
    vector<int> pre(n),suf(n);

    for(int i=0; i<n; i++)
    {
        cin>>arr[i];
    }
    
    for(int i=0; i<n; i++)
        pre[i]= ++preF[arr[i]];//count of arr[i] in [0...i]
    for(int i=n-1; i>=0; i--)
        suf[i]= ++sufF[arr[i]];//count of arr[i] in [i...n-1]
    
    ll total=0LL;
    for(int i=0; i<n; i++)
    {
        x=s.size()-s.order_of_key({suf[i]+1,0});
        s.insert({pre[i], ID++});
        total+=x;
        //cout<<suf[i]<<"--> "<<x<<endl;
    }
    cout<<total<<endl;
}
 
 
int32_t main()
{
    FAST
 
    ll TC=1LL,cs=1LL;
 
    //cin>>TC;
 
    while(TC--){
        //CS(cs++);
        solve();
    }
 
    return 0;
}
