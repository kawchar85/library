#include<bits/stdc++.h>
using namespace std;

#define MAX 200005
#define LVL 20 //ceil(log_2(MAXN))+1
int arr[MAX];
int dst[MAX][LVL];

int merge(int x, int y)
{
    return __gcd(x,y);
}
//0 based
void build(int n){
    for(int i=0; i<n; ++i) dst[i][0] = arr[i];
    for(int k=1; k<LVL; ++k)
        for(int i=0; (i+(1<<k)-1)<n; ++i)
            dst[i][k] = merge(dst[i][k-1], dst[i+(1<<(k-1))][k-1]);
}

int query(int l, int r){
    int k=31-__builtin_clz(r-l+1);
    return merge(dst[l][k], dst[r-(1<<k)+1][k]);
}

int main()
{
    int n,q,l,r,i;
    cin>>n;
    for(i=0; i<n; i++) cin>>arr[i];
    build(n);
    cin>>q;
    while(q--)
    {
        cin>>l>>r;
        cout<<query(l,r)<<endl;
    }

    return 0;
}
