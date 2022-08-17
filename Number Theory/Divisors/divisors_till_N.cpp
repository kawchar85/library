#include<stdio.h>
#include<bits/stdc++.h>
#define sz 1000001
#define mod 1000002
using namespace std;

vector <int> divisors[sz];

//O(NLogN)
void all_divisors(int n)
{
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j+=i)
            divisors[j].push_back(i);
}
int main()
{
    int n,i,j;
    cin>>n;

    all_divisors(n);
    
    for(i=1;i<=n;i++)
    {
        for(j=0;j<divisors[i].size();j++)
            cout<<divisors[i][j]<<" ";
            cout<<endl;
    }
}
