/**
    https://www.codechef.com/problems/XORCMPNT
    
    We have a graph of 2^k nodes numbered
    from 0 to 2^k −1, 1≤k≤30. Also, we're
    given 1≤M≤10^5 integers x1,x2,…,xM within
    the range 0≤xi≤2^k−1. In the graph, 
    two vertices u and v are connected with 
    an edge iff u⊕v=xi for some i. Find the
    number of connected components in the graph.

    sol:
    From a vertex u, a vertex v is reachable iff 
    there exist a subset S of the given array X such that
    xor of all the elements in S is equal to u⊕v.
    Total distinct xor value is 2^(size of basis). So,
    each vertex belongs to a component of size 2^(size of basis).
    Hence, number of components is 2^k/2^(size of basis)
    =2^(k-size of basis)
*/
#include <bits/stdc++.h> 
using namespace std;
#define ll long long

#define getbit(n,i) ((n>>i)&1)
const int LOG_A=30;//Dimension

ll basis[LOG_A];
int sz;

void addVector(ll mask)
{
    for(int i=0; i<LOG_A; i++)
    {
        if(!getbit(mask, i)) continue;

        if(!basis[i])
        {
            basis[i]=mask;
            sz++;
            return;
        }
        mask^=basis[i];
    }
}
void clearSpace()
{
    sz=0;
    memset(basis, 0, sizeof(basis));
}

void solve()
{
    ll k,m,x;
    cin>>k>>m;

    while(m--)
    {
        cin>>x;
        addVector(x);
    }

    x=k-sz;
    cout<<(1LL<<x)<<endl;
    clearSpace();
}
int main()
{
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
