#include<bits/stdc++.h>
using namespace std;
 

const int LMT =1e7+7;
 
int pf[LMT]; //Smallest prime factor
vector<int> prime;

void linear_sieve()
{
    for(int i=2; i<LMT; i++)
    {
        if(pf[i]==0) pf[i]=i,prime.push_back(i);
        for(int j=0; j<(int)prime.size() && prime[j]<=pf[i] && i*prime[j]<LMT; j++) 
        	pf[i*prime[j]]=prime[j];
    }
}
 
int main()
{
    linear_sieve();
    
 
    return 0;
}
