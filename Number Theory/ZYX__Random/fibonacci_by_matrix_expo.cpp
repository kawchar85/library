#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD 1000000007
#define M 2

ll A[M][M],I[M][M];

void mul(ll A[][M], ll B[][M])
{
    ll temp[M][M],i,j,k;
    for(i=0; i<2; i++)
    {
        for(j=0; j<2; j++)
        {
            temp[i][j]=0LL;
            for(k=0; k<2; k++)
            {
                temp[i][j]=(temp[i][j]+(A[i][k]*B[k][j])%MOD)%MOD;
            }
        }
    }
    for(i=0; i<2; i++)
    {
        for(j=0; j<2; j++)
            A[i][j]=temp[i][j];
    }
}

void power(ll A[][M], ll p)
{
    while(p)
    {
        if(p&1)
        {
            mul(I, A);
            p--;
        }
        else
        {
            mul(A, A);
            p/=2LL;
        }
    }

}
void print()
{
    cout<<"\n-------\n";
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        {
            cout<<I[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"-----\n";
}

void init()
{
    A[0][0]=A[0][1]=A[1][0]=1LL;
    A[1][1]=0LL;

    I[0][0]=I[1][1]=1LL;
    I[0][1]=I[1][0]=0LL;
}

ll Fibo_n(ll n)
{
    if(n==0) return 0;
    init();
    power(A, n);
    //print();
    return I[1][0];
}

//n,f0,f1
ll Fibo_n(ll n, ll f, ll s)
{
    if(n==0LL) return f%MOD;
    if(n==1LL) return s%MOD;
    init();
    power(A, n-1);
    //print();
    return (((s%MOD)*I[0][0])%MOD + ((f%MOD)*I[1][0])%MOD)%MOD;
}

int main()
{
    ll n;
    cin>>n;
    cout<<"Fibo("<<n<<") = "<<Fibo_n(n)<<endl;
    
    return 0;
}
