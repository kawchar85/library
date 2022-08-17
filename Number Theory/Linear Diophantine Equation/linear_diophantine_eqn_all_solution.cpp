#include<bits/stdc++.h>
using namespace std;

#define ERROR 0
#define int long long

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
    //find_positive_solution(a,b,x0,y0,g);
    return 1;
}

int find_all_solutions(int a, int b, int c, int minX, int maxX, int minY, int maxY)
{
    if(!a && !b)
    {
        if(c) return 0LL;
        return (maxX-minX+1LL)*(maxY-minY+1LL);
    }
    if(!a)
    {
        if(c%b) return 0LL;
        int y=c/b;
        if(minY<=y && y<=maxY) return (maxX-minX+1LL);
        return 0LL;
    }
    if(!b)
    {
        if(c%a) return 0LL;
        int x=c/a;
        if(minX<=x && x<=maxX) return (maxY-minY+1LL);
        return 0LL;
    }
    int x, y, g;
    if (!find_any_solution(a, b, c, x, y, g))
        return 0;
    
    a/=g;
    b/=g;

    int sign_a = a > 0 ? +1 : -1;
    int sign_b = b > 0 ? +1 : -1;

    if(ERROR) cout<<x<<" "<<y<<"\n";

    shift_solution(x, y, a, b,(minX-x)/b);
    if(x<minX)
        shift_solution(x, y, a, b, sign_b);
    if(ERROR) cout<<x<<" "<<y<<"\n";
    
    if(x>maxX)  return 0;
    int lx1 = x;

    shift_solution(x, y, a, b, (maxX-x)/b);
    if(x>maxX)
        shift_solution(x, y, a, b, -sign_b);
    if(ERROR) cout<<x<<" "<<y<<"\n";
    int rx1 = x;

    shift_solution(x, y, a, b, -(minY-y)/a);
    if(y<minY)
        shift_solution(x, y, a, b, -sign_a);
    if(ERROR) cout<<x<<" "<<y<<"\n";
    if(y>maxY)  return 0;
    int lx2 = x;

    shift_solution(x, y, a, b, -(maxY-y)/a);
    if(ERROR) cout<<x<<" "<<y<<"\n";
    int rx2 = x;

    if(lx2>rx2)
        swap(lx2, rx2);
    int lx = max(lx1, lx2);
    int rx = min(rx1, rx2);

    if(lx>rx)
        return 0;
    return (rx - lx) / abs(b) + 1;
    /**
    Once we have lx and rx, it is also 
    simple to enumerate through all the 
    solutions. Just need to iterate through
    x=lx+k*b/g for all k≥0 until x=rx, 
    and find the corresponding y values 
    using the equation ax+by=c.
    */
}

int32_t main()
{
    int a,b,c,x1,x2,y1,y2,T;
    
    cin>>T;
    for(int cs=1; cs<=T; cs++)
    {
        cin>>a>>b>>c>>x1>>x2>>y1>>y2;
        c=-c;
        int ans=find_all_solutions(a,b,c,x1,x2,y1,y2);
        cout<<"Case "<<cs<<": "<<ans<<"\n";
    }

    return 0;
}
