/*
    CF: 281D
*/
#include<bits/stdc++.h>
using namespace std;

#define MAX 200005
typedef long long ll;

ll arr[MAX];
stack<ll>st;//big to small store korbo

void print(ll i)
{
    if(st.empty())
        cout<<"No element in left";
    else
        cout<<st.top();
    cout<<" > "<<arr[i]<<endl;
}

ll get(ll mxx)
{
    if(st.empty())
        return 0LL;
    return mxx^st.top();
}
ll twoMax(ll n)
{
    ll ans=0LL;
    st.push(arr[0]);
    for(ll i=1; i<n; i++)
    {
        while(!st.empty() && arr[i]>=st.top())
        {
            //max_1st=arr[i]
            //max_2nd=top()
            ans=max(ans, get(arr[i]));
            st.pop();
        }
        print(i);
        //max_1st=top()
        //max_2nd=arr[i]
        ans=max(ans, get(arr[i]));
        st.push(arr[i]);
    }
    return ans;
}

void syntex_error()
{
    ll i,n;
    vl v;
    
    cin>>n;
    for(i=0; i<n; i++) cin>>arr[i];

    cout<<twoMax(n)<<endl;
}

int main()
{
    FAST
    
    ll TC=1LL;

    //cin>>TC;

    while(TC--){
        syntex_error();
    }

    return 0;
}

