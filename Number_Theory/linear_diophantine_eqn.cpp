//Ax+By=C
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

void shift_solution(int &x,int &y, int a,int b,int cnt)
{
    //x=x0+k*(b/g)
    //y=y0-k*(a/g)
    x+=cnt*b;
    y-=cnt*a;
}
void find_positive_solution(int a,int b,int &x,int &y,int g)
{
    a/=g;
    b/=g;
    int mov;

    if(x<0)
    {
        mov=(0-x+b-1)/b; //taking ceil
        shift_solution(x,y,a,b,mov);
    }
    if(y<0)
    {
        mov=(-y)/a;
        if((-y)%a) mov++; //taking ceil
        shift_solution(x,y,a,b,-mov);
    }
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
int main()
{
    /**
    if a=b=0
        if c=0
        sol=inf;
        else
        no sol
    if c=g or a=0 or b=0
        one sol

    */
    int a,b,c,g,x,y;
    cin>>a>>b>>c;
    if(find_any_solution(a,b,c,x,y,g))
    {
        cout<<x<<" "<<y<<endl;
    }
    else
        cout<<"No solution\n";

}
