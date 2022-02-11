/*
Somebody rotated(shifted) a sorted
array. Find the smalles element.

6,7,9,15,19,2,3;
actually lower bound of false of our
condition { a[mid]>a[R]}.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll smallest(ll a[],ll n)
{
    ll low=0, high=n-1, mid;
    ll ans=0;
    while(low<=high)
    {
        mid=low+(high-low)/2; //skip overflow
        if(a[mid]>a[high])
        {
            low=mid+1;
        }
        else
        {
            ans=mid;
            high=mid-1;
        }
    }
    return a[ans];
}

int main()
{
    ll a[5]={3,4,5,1,2};
    ll n=5;
    cout<<smallest(a,n)<<endl;
    return 0;
}
