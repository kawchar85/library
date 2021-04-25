/**
    https://cses.fi/problemset/task/1144/
    count the number of values in range [a..b]
    
    Query:
    ! set[a]=b
    ? count [a..b]
*/
#include<bits/stdc++.h>
using namespace std;
 
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 200005

typedef long long ll;


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>

//find_by_order(),order_of_key()
//greater<int>,
/**
    less_equal<int> -->multiset
    order_of_key will return 1st pos
*/

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
        s.insert(arr[i]);
    }
    
    while(q--)
    {
        cin>>ch>>a>>b;
        if(ch=='!') //update: set arr[a]=b
        {
            //s.erase(arr[a]) dile sob arr[a] delete hoye jabe
            x = s.order_of_key(arr[a]);
            auto it = s.find_by_order(x);
            s.erase(it);
            
            //Another way
            /*
                auto it = s.upper_bound(arr[a]);
                s.erase(it);
                //multiset er jonno upper_bound-->lower_bound hisebe kaj kore.
            */
            
            arr[a]=b;
            s.insert(arr[a]);
        }
        else
        {
            cout<<(s.order_of_key(b+1)-s.order_of_key(a))<<endl;
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
