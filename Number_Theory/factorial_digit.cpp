#include<bits/stdc++.h>
#define eps 1e-9
using namespace std;

//number of digit of N! in B base
int factDigit(int n,int base)
{
    double x=0.0;
    for(int i=1; i<=n; i++)
    {
        x+=log10(i);
        //x+=(log10(i)/log10(base));
    }

    x/=log10(base);
    int res=1+x+eps;
    return res;
}

int main()
{
    int n,b;
    cin>>n>>b;
    cout<<factDigit(n,b);
}
