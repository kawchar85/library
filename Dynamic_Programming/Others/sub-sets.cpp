#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define getbit(n,i) ((n>>i)&1)
#define bitOn(n,i) ((1<<i)|n)
#define bitOff(n,i) (~(1<<i)&n)

char a[]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};

void print_sub_set(int n)
{
    int total = 1<<n;
    for(int mask=0; mask<total; mask++)
    {
        for(int i=0; i<n; i++)
        {
            if(getbit(mask, i))
                cout<<a[i]<<" ";
        }
        cout<<endl;
    }
}
int main()
{
    
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        print_sub_set(n);
    }
    return 0;
}
