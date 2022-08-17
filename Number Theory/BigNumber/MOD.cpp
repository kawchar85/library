#include<bits/stdc++.h>
#include<string>
using namespace std;
typedef long long ll;

ll mod(string a, ll b)
{
    ll temp=0,idx=0;

    while(idx<a.size())
    {
        temp=(temp*10+a[idx++]-'0')%b;
    }
    return temp;
}

int main()
{


}
