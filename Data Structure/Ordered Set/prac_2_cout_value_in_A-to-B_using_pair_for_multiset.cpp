/**
    https://cses.fi/problemset/task/1144/
    count the number of values in range [a..b]
    
    Query:
    ! set[a]=b
    ? count [a..b]

    use pair for multiset
*/
#include<bits/stdc++.h>
using namespace std;
 
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 200005

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
    char ch;
    ordered_set s;

    cin>>n>>q;
    
    for(int i=1; i<=n; i++)
    {
        cin>>arr[i];
        s.insert({arr[i],ID++});
    }
    
    while(q--)
    {
        cin>>ch>>a>>b;
        if(ch=='!') //update: set arr[a]=b
        {
            auto it = s.lower_bound({arr[a],0});
            s.erase(it);
            
            arr[a]=b;
            s.insert({arr[a],ID++});
        }
        else
        {
            cout<<(s.order_of_key({b+1,0})-s.order_of_key({a,0}))<<endl;
        }
    }
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
