#include<bits/stdc++.h>
#define MAX 1000001
using namespace std;

int BIT[MAX],N;

void update(int x, int val)
{
    while(x<=N)
    {
        BIT[x]+=val;
        x+=x&(-x);
    }
}

int query(int x)
{
    int sum=0;
    while(x>0)
    {
        sum+=BIT[x];
        x-=x&(-x);
    }
    return sum;
}


int main()
{
    int i,a;
    cin>>N;
    for(i=1;i<=N;i++)
    {
        cin>>a;
        update(i,a);
    }
    cout<<query(5)<<endl;
}
