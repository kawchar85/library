#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define MAX 1000006
using namespace std;

bool siv[MAX];
unordered_map<int,int> fact;

///O(n*lg(lg(n)))
void sieve()
{
    ll i,j;
    for(i=3; i*i<MAX; i+=2)
        if(!siv[i])
            for(j=i*i; j<MAX; j+=i+i)
                siv[j]=1;
}

bool isPrime(int n)
{
    if(n<2) return 0;
    if(n==2) return 1;
    if(n%2==0) return 0;
    return !siv[n];
}

int pollard_rho(int n)
{
    if(n%2==0)
        return 2;

    int x = rand()%n+1;
    int c = rand()%n+1;
    int y = x;
    int g = 1;

    while(g==1)
    {
        x = ((x*x)%n + c)%n;
        y = ((y*y)%n + c)%n;
        y = ((y*y)%n + c)%n;
        g = __gcd(abs(x-y),n);
    }
    return g;
}

//O(N^1/4)
void factorize(int n)
{
    if(n == 1)
        return;

    if(isPrime(n))
    {
        fact[n]++;
        return;
    }
    int divisor = pollard_rho(n);
    factorize(divisor);
    factorize(n/divisor);
}

int NOD(int n)
{
    int cnt=1;
    fact.clear();
    factorize(n);

    for(auto p : fact)
    {
        cout<<p.first<<"-->"<<p.second<<endl;
        cnt*=(p.second+1);
    }
    return cnt;
}
int main()
{
    srand(time(NULL));
    sieve();

    cout<<NOD(10);
    return 0;
}
