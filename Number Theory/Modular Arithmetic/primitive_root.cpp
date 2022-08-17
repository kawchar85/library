#include<bits/stdc++.h>
using namespace std;

int powmod (int a, int b, int p) {
    int res = 1;
    while (b)
        if (b & 1)
            res = int (res * 1ll * a % p),  --b;
        else
            a = int (a * 1ll * a % p),  b >>= 1;
    return res;
}

/**
    returns the primitive root modulo p. g is a 
    primitive root modulo p if and only if for
    any integer a such that gcd(a,p)=1, 
    there exists an integer k such that:
        g^k = a(mod p).
 
    this code assumes p is prime
    so phi=p-1;
    if p is not prime, calculate phi(p)

*/
int PrimitiveRoot (int p)
{
    vector<int> fact;
    int phi = p-1,  n = phi;
    for (int i=2; i*i<=n; ++i)
    {
        if (n % i == 0)
        {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        fact.push_back (n);

    for (int res=2; res<=p; ++res)
    {
        bool ok = true;
        for (size_t i=0; i<fact.size() && ok; ++i)
            ok &= powmod (res, phi / fact[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}

int main()
{
    int p=7;
    cout<<PrimitiveRoot(p)<<endl;
}
