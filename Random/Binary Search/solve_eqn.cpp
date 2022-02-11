#include<bits/stdc++.h>
using namespace std;
#define EPS 1e-9

int a,b,c;

double F(double x)
{
    return a*x+b*sin(x);
}

bool isEqual(double x, double y)
{
    return abs(x-y)<EPS;
}
void solveEqn()
{
    double l=0, h=2e5,mid;
    while(l<=h)
    {
        mid=(l+h)/2.0;
        if(isEqual(F(mid),c+0.0))
            break;
        if(F(mid)>c)
            h=mid;
        else
            l=mid;
        //cout<<l<<" "<<h<<endl;
    }

    printf("%.6lf\n", mid);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d %d",&a,&b,&c);
        solveEqn();
    }
}