#include<bits/stdc++.h>
using namespace std;

int NOD(int n)
{
    int cnt=0;
    for(long long i=1; i*i<=n; i++)
    {
        if(i*i==n)
            cnt++;
        else if(n%i==0)
            cnt+=2;
    }
    return cnt;
}

int main()
{
    int t,x,y;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&x);
        x=NOD(x);
        printf("%d\n",x);
    }
}
