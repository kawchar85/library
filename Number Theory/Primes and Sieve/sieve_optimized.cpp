#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define MAX 1000006
using namespace std;

bool siv[MAX];
vector<ll>prime;

///O(n*lg(lg(n)))
void sieve()
{
    ll i,j;
    for(i=3; i*i<MAX; i+=2)
        if(!siv[i])
            for(j=i*i; j<MAX; j+=i+i)
                siv[j]=1;
    prime.pb(2);
    for(i=3; i<MAX; i+=2)
        if(!siv[i]) prime.pb(i);
}

int main()
{
    sieve();
    cout<<prime.size()<<" "<<prime.back()<<endl;
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
