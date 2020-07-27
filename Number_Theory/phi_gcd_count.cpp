/**
    count pair(x,y) such that
    gcd(x,y)=g, 1<=x,y<=N
*/

#include<bits/stdc++.h>
#define ll long long
#define MAX 1000006
using namespace std;

ll phi[MAX],sumPhi[MAX];
void Euler()
{
    ll i,j;

    for(i=0; i<MAX; i++)
        phi[i]=i;
    for(i=2; i<MAX; i++)
    {
        if(phi[i]==i)
        {
            phi[i]=i-1;
            for(j=i+i; j<MAX; j+=i)
                phi[j]=phi[j]/i*(i-1); 
        }
    }
    for(i=1; i<MAX; i++)
        sumPhi[i]=sumPhi[i-1]+phi[i];
}

ll getCnt(ll n, ll g)
{
    ll k=n/g;
    return sumPhi[k];
}

int main()
{
    Euler();
    ll t,n>>g;
    cin>>t;
    while(t--)
    {
        cin>>n>>g;
        cout<<getCnt(n,g)<<endl;
    }
}
