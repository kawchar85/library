#include<bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define ALL(v) v.begin(),v.end()
#define endl "\n"

#define MAX 200005
 
typedef long long ll;
typedef vector<ll> vl;
typedef vector<int> vi;


ll arr[MAX];
stack<ll>st;//big to small store korbo

//CF281D
void print(ll i)
{
    if(st.empty())
        cout<<"No element in left";
    else
        cout<<st.top();
    cout<<" > "<<arr[i]<<endl;
}

void greaterInLeft(ll n)
{
    st.push(arr[0]);
    for(ll i=1; i<n; i++)
    {
        while(!st.empty() && arr[i]>=st.top())
            st.pop();

        print(i);
        st.push(arr[i]);
    }
}
 
int main()
{
    ll n;
    cin>>n;
    for(int i=0; i<n; ++i)
        cin>>arr[i];
    
    greaterInLeft(n);
    return 0;
}