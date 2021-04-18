/**
    Given a set S of size 1≤n≤10^5 with elements 0≤ai<2^20.
    What is the maximum possible xor of the elements of some
    subset of S?

    sol:
    In this problem, we need to slightly alter the definition
    of f(b⃗). Instead of f() being the first position with a set
    bit, let it be the last position with a set bit. [iterate Log_A-1 to 0]

    Now, to get the maximum, we initialize our answer at 0 and 
    we start iterating the basis vectors starting with the one 
    that has the highest value of f(). Suppose, we're at basis 
    vector b⃗  and we find that answer doesn't have the f(b⃗)'th 
    bit set, then we add b⃗ with answer. This greedy solution 
    works because f(b⃗ ) is the most significant bit at the 
    moment, and we must set it; doesn't matter if all the
    following bits turn to 0

*/
#include <bits/stdc++.h> 
using namespace std;
#define ll long long

#define getbit(n,i) ((n>>i)&1)
const int LOG_A=20;//Dimension

ll basis[LOG_A];
int sz;

void addVector(ll mask)
{
    //for(int i=0; i<LOG_A; i++)
    for(int i=LOG_A-1; ~i; i--)
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
    ll n,x;
    cin>>n;

    while(n--)
    {
        cin>>x;
        addVector(x);
    }

    ll ans=0;
    for(int i=LOG_A-1; ~i; i--)
    {
        if(!basis[i] || getbit(ans,i))
            continue;
        ans^=basis[i];
    }
    cout<<ans<<endl;
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
