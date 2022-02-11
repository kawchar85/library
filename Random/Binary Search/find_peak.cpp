/*
The array increases and then decreases.
Find the maximum.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll Peak(ll a[],ll n)
{
    ll low=0, high=n-1, mid;
    ll ans=0;
    while(low<=high)
    {
        mid=low+(high-low)/2; //skip overflow
        if(mid==0|| a[mid]>a[mid-1])
        {
            ans=mid;
            low=mid+1;
        }
        else
        {
            high=mid-1;
        }
    }
    return a[ans];
}

int main()
{
    ll a[5]={3,4,5,4,2};
    ll n=5;
    cout<<Peak(a,n)<<endl;
    return 0;
}
