/*
    ax=b (mod m)
*/

#include<bits/stdc++.h>
using namespace std;

int egcd(int a, int b, int &x, int &y)
{
    if(a==0)
    {
        x=0;y=1;
        return b;
    }

    int x1,y1;
    int d=egcd(b%a, a, x1, y1);
    x=y1-(b/a)*x1;
    y=x1;
    return d;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g)
{
    g=egcd(abs(a),abs(b),x0,y0);
    if(c%g) return 0;

    x0*=c/g;
    y0*=c/g;
    if(a<0) x0*=-1;
    if(b<0) y0*=-1;
    return 1;
}

int get_x(int a, int b, int m)
{
    //ax=b (mod m)
    int x,y,g;
    if(find_any_solution(a,m,b,x,y,g))
        return x;
    else return 0;
}
int main()
{
    int a=2;
    int b=2;
    int m=4;
    cout<<get_x(a,b,m)<<endl;

}
