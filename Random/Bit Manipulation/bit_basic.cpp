#include<bits/stdc++.h>
using namespace std;
#define setbit(n) (n&-n)
#define bitOn(n,i) ((1LL<<i)|n)
#define bitOn2(n,i,j) ((((1LL<<(j-i+1))-1)<<i)|n)
#define bitOff(n,i) (~(1LL<<i)&n)
#define bitOff2(n,i,j) (~(((1LL<<(j-i+1))-1)<<i)&n)
#define bitToggle(n,i) ((1LL<<i)^n)
#define bitToggle2(n,i,j) ((((1LL<<(j-i+1))-1)<<i)^n)
#define bitOnAll(n) (n=-1)
#define bitOffAll(n) (n=0)
//#define getbit(n,i) ((n&(1<<i))!=0)
#define getbit(n,i) ((n>>i)&1)
#define last1cng(n) (n)&((n)-1)
#define last0cng(n) ~(last1cng(~(n)))


int And(int L, int R)
{
    //L&(L+1)&(L+2)&....&(R-1)&R
    int d=R-L;
    int res=0;

    for(int i=0; i<32; i++)
    {
        if(d>(1<<i)) continue;
        if(getbit(L,i) && getbit(R,i))
            ret+=(1<<i);
    }

    return res;
}

int main()
{
    int n=10;
    cout<<getbit(n,0)<<endl;
    n=bitOn(n,1);
    cout<<getbit(n,1)<<endl;
    n=bitToggle(n,5);
    cout<<getbit(n,5)<<endl;
    n=bitOff(n,5);
    cout<<getbit(n,5)<<endl;
    n=bitOn2(n,10,15);
    cout<<getbit(n,10)<<endl;
    n=bitOff2(n,12,15);
    cout<<getbit(n,15)<<endl;
    n=bitOffAll(n);
    cout<<getbit(n,0)<<endl;

    n=7;
    last1cng(n);
    cout<<n<<endl;

}
