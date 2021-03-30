#include<bits/stdc++.h>
#define ll long long
#define MAXN 505
#define MAXM 505

using namespace std;

int arr[MAXN][MAXM],N,M;

struct info 
{
    int sum,mn,mx;
    info(){
        mn=INT_MAX/100;
        mx=INT_MIN/100;
        sum=0;
    }
    info(int x, int y, int z){
        mn=x;
        mx=y;
        sum=z;
    }
    info(int x){
        mn=mx=sum=x;
    }
}tree[3*MAXN][3*MAXM];

info leaf(int i, int j){
    return info(arr[i][j]);
}
info Set(ll x){
    return info(x);
}
info outOfRange(){
    return info();
}
info merge(info x, info y){
    info ans;
    ans.mn=min(x.mn, y.mn);
    ans.mx=max(x.mx, y.mx);
    ans.sum=x.sum+y.sum;
    return ans;
}

void build_y(int vx, int lx, int rx, int vy, int ly, int ry)
{
    if(ly == ry)
    {
        if(lx == rx)
            tree[vx][vy] = leaf(lx,ly);
        else
            tree[vx][vy] = merge(tree[vx*2][vy], tree[vx*2+1][vy]);
    }
    else
    {
        int my = (ly + ry) / 2;
        build_y(vx, lx, rx, vy*2, ly, my);
        build_y(vx, lx, rx, vy*2+1, my+1, ry);
        tree[vx][vy] = merge(tree[vx][vy*2], tree[vx][vy*2+1]);
    }
}

void build_x(int vx, int lx, int rx)
{
    if(lx != rx)
    {
        int mx = (lx + rx) / 2;
        build_x(vx*2, lx, mx);
        build_x(vx*2+1, mx+1, rx);
    }
    build_y(vx, lx, rx, 1, 0, M-1);
}

info query_y(int vx, int vy, int tly, int try_, int ly, int ry)
{
    if(ly > ry) 
        return outOfRange();
    if(ly == tly && try_ == ry)
        return tree[vx][vy];

    int tmy = (tly + try_) / 2;
    auto x = query_y(vx, vy*2, tly, tmy, ly, min(ry, tmy));
    auto y = query_y(vx, vy*2+1, tmy+1, try_, max(ly, tmy+1), ry); 
    return merge(x,y); 
}

info query_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry)
{
    if(lx > rx)
        return outOfRange();
    if(lx == tlx && trx == rx)
        return query_y(vx, 1, 0, M-1, ly, ry);
    
    int tmx = (tlx + trx) / 2;
    auto x=query_x(vx*2, tlx, tmx, lx, min(rx, tmx), ly, ry);
    auto y=query_x(vx*2+1, tmx+1, trx, max(lx, tmx+1), rx, ly, ry);
    return merge(x,y);
}

void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int val)
{
    if(ly == ry)
    {
        if(lx == rx)
            tree[vx][vy] = val;
        else
            tree[vx][vy] = merge(tree[vx*2][vy], tree[vx*2+1][vy]);
    } 
    else
    {
        int my = (ly + ry) / 2;
        if(y <= my)
            update_y(vx, lx, rx, vy*2, ly, my, x, y, val);
        else
            update_y(vx, lx, rx, vy*2+1, my+1, ry, x, y, val);
        tree[vx][vy] = merge(tree[vx][vy*2] , tree[vx][vy*2+1]);
    }
}

void update_x(int vx, int lx, int rx, int x, int y, int val)
{
    if(lx != rx)
    {
        int mx = (lx + rx) / 2;
        if(x <= mx)
            update_x(vx*2, lx, mx, x, y, val);
        else
            update_x(vx*2+1, mx+1, rx, x, y, val);
    }
    update_y(vx, lx, rx, 1, 0, M-1, x, y, val);
}

void build(int n, int m){
    N=n;M=m;
    build_x(1,0,N-1);
}
void update(int i, int j, int val){ //arr[i][j]=val
    update_x(1,0,N-1,i,j,val);
}
info query(int x1, int y1, int x2, int y2){
    auto x = query_x(1, 0, N-1, x1, x2, y1, y2);
   return x; 
}
void solve(){
    
    int i,j,k,n,m,x,y,z;
    char ch;

    scanf("%d", &n);

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            scanf("%d", &arr[i][j]);
    }
    build(n,n);

    scanf("%d", &m);
    while(m--)
    {
        scanf(" %c", &ch);
        if(ch=='q')
        {
            int x1,x2,y1,y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            x1--,y1--,x2--,y2--;

            auto ans=query(x1,y1,x2,y2);
            printf("%d %d %d\n", ans.mx, ans.mn, ans.sum);
        }
        else
        {
            scanf("%d %d %d", &x, &y, &z);
            x--,y--;
            update(x,y,z);
        }
    }
}
int main()
{
    int tc=1;
    //scanf("%d", &tc);
    while(tc--)
    {
        solve();
    }
    return 0;
}
/*

5
1 2 3 4 5
0 9 2 1 3
0 2 3 4 1
0 1 2 4 5
8 5 3 1 4
4
q 1 1 2 3
c 2 3 10
q 1 1 5 5
q 1 2 2 2
*/
