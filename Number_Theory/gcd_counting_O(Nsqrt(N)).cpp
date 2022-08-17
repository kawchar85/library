/**
    Given N positive integers, not
    necessarily distinct, how many
    ways you can take 4 integers 
    from the N numbers such that their GCD is 1
*/

#include<bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define MAX 10004


typedef long long ll;


ll cnt[MAX];
ll nC4(ll n)
{
    return n*(n-1)*(n-2)*(n-3)/24LL;
}
void syntex_error()
{
    memset(cnt, 0, sizeof cnt);
    ll n,x,i,j;
    cin>>n;
    for(i=0; i<n; i++)
    {
        cin>>x;
        for(j=1; j*j<=x; j++)
        {
            if(x%j==0)
            {
                cnt[j]++;
                if(j*j!=x)
                    cnt[x/j]++;
            }
            //cnt[i]=total number such that gcd=i*k,k=1,2,3...
        }
    }
    for(i=1; i<MAX; i++)
    {
        cnt[i]=nC4(cnt[i]);
        //cnt[i]=total number of group of 4 element such that gcd=i*k
    }
    for(i=MAX-1; i>0; i--)
    {
        for(j=i+i; j<MAX; j+=i)
            cnt[i]-=cnt[j];//multiple bad dilam
        //cnt[i]=total number of group of 4 element such that gcd=i
    }
  
    cout<<cnt[1]<<endl;
}

int main()
{
    //FAST
    
    ll TC=1LL;

    cin>>TC;

    while(TC--){
        syntex_error();
    }

    return 0;
}
