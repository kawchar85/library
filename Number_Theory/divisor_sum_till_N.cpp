#include<bits/stdc++.h>
#define SZ 100005
#define ll long long
using namespace std;

ll sod[SZ];
//O(NLogN)
void SOD()
{
    for(int i=1; i<SZ; i++)
    {
        for(int j=i; j<SZ; j+=i)
        {
           sod[j]+=i;
        }
    }
}
int main()
{

}
