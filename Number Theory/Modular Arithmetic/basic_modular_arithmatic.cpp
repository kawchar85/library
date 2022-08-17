#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
using namespace std;

//a^p % M
ll BigMod(ll a, ll p, ll M=MOD){
    if(!p) return (1%M);
    ll x=BigMod(a, p/2, M);
    x=(x*x)%M;//Overflow?
    if(p&1) x=(x*a)%M;
    return x;
}

ll Big_Mod(ll a, ll p, ll M=MOD){
    ll result=1;
    while(p>0){
        if(p&1){
            result*=a;
            if(result>M)
                result%=M;
        }
        p>>=1;
        a*=a;
        if(a>M)
            a%=M;
    }
    return result%M;
}

//inv of n % M
ll inv(ll n, ll M=MOD){
    return BigMod(n, M-2, M);
}

ll mul(ll x, ll y, ll M=MOD){
    return (((x%M)*(y%M))%M);
}

ll add(ll A, ll B, ll M=MOD){
    return (A%M + B%M)%M;
}

ll dvd(ll A, ll B, ll M=MOD){
    return mul(A, inv(B, M), M);
}

ll sub(ll A, ll B, ll M=MOD){
    return (A%M-B%M+M)%M;
}

int main(){

    cout<<BigMod(2,5,10)<<endl;
    cout<<BigMod(2,5)<<endl;
}
