#include<bits/stdc++.h>
#define ll long long
using namespace std;

/** C(n,k) = n!/((n-k)!k!)
      [n(n-1)...(n-k+1)][(n-k)...(1)]
    = -------------------------------
      [(n-k)...(1)][k(k-1)...(1)]

      n (n-1)     (n-k+1)
    = - ----- ... -------
      k (k-1)       (1)

    that is,

    C(n,k) = 1,            if k = 0
       = (n/k)*C(n-1, k-1), otherwise
*/

ll C(ll n, ll r)
{
    if(r>n) return 0;
    if(r==0) return 1;
    return C(n-1,r-1)*n/r;
}

int main()
{
    ll n,r;
    while(cin>>n>>r)
        cout<<C(n,r)<<endl;
}
