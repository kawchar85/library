#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

bool b_search(ll n, ll k)
{
    ll low=1, high=n, mid;
    bool ans=0;
    while(low<=high)
    {
        mid=(low+high)>>1;
        //mid=low+(high-low)/2; //skip overflow
        if(mid==k)
        {
            ans=1;
        }
        if(mid<k)
        {
            low=mid+1;
        }
        else
        {
            high=mid-1;
        }
    }
    return ans;
}

bool b_search2(ll n, ll k)
{
    ll low=1, high=n, mid;
    bool ans=0;
    while(low<high)
    {
        mid=(low+high+1)>>1;  //+1 look at low
        if(mid==k)
        {
            ans=1;
        }
        if(mid<k)
        {
            low=mid;
        }
        else
        {
            high=mid-1;
        }
    }
    return ans;
}
int main()
{

    return 0;
}
