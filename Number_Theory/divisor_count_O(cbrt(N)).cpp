#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define MAX 1004
using namespace std;

bool siv[MAX];
bool isPrimeSq[MAX*MAX+1],isPrime[MAX];
vector<int> prime;

///O(n*lg(lg(n)))
void sieve()
{
    ll i,j;
    for(i=3; i*i<MAX; i+=2)
        if(!siv[i])
            for(j=i*i; j<MAX; j+=i+i)
                siv[j]=1;
    prime.pb(2);
    isPrime[2]=1;
    isPrimeSq[2*2]=1;
    for(i=3; i<MAX; i+=2){
        if(!siv[i]){
            prime.pb(i);
            isPrime[i]=1;
            isPrimeSq[i*i]=1;
        }
    }
}

int CB(int x)
{
    return x*x*x;
}

//O(N^1/3)
int NOD(int n)
{
    int cnt=1;
    for(int i=0; CB(prime[i])<=n; i++)
    {
        int c=1;
        while(n&prime[i]==0)
        {
            c++;
            n/=prime[i];
        }
        cnt*=c;
    }

    if(isPrime[n]) cnt*=2;
    else if(isPrimeSq[n]) cnt*=3;
    else if(n!=1) cnt*=4;
    return cnt;
}
int main()
{
    sieve(); //need prime till n^1/3
    cout<<NOD(10);
    return 0;
}
