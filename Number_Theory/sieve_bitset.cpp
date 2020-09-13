#include<bits/stdc++.h>
#define MAX 1000006
using namespace std;

bitset<MAX> siv;
vector<int>prime;

void sieve()
{
    int sq=sqrt(MAX)+1;

    for(int i=3; i<=sq; i+=2)
        if(!siv[i])
            for(int j=i*i; j<MAX; j+=i+i)
                siv[j]=1;

    prime.push_back(2);
    for(int i=3; i<MAX; i+=2)
        if(!siv[i]) prime.push_back(i);
}

bool isPrime(int n)
{
    if(n==2) return 1;
    if(n<2 || n%2==0) return 0;
    return siv[n]==0;
}

int main()
{
    sieve();
    cout<<"Total: "<<prime.size()<<",Last prime: "<<prime.back()<<endl;
    
    if(isPrime(499979))
    {
        cout<<"YES"<<endl;
    }
    else
    {
        cout<<"NO"<<endl;
    }
    return 0;
}

