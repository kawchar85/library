#include<bits/stdc++.h>
using namespace std;
#define MAX 100005

//If the size of palindrome centered at i is x, then d1[i] stores (x+1)/2.
//If the size of palindrome centered at i is x, then d2[i] stores x/2

int d[2][MAX]; //d[0]-->even len, d[1]-->odd len

void manachar(string s)
{
    int n=(int)s.size();
    for(int t=0; t<2; t++)
    {
        for(int i=0, l=0, r=-1; i<n; i++)
        {
            int k=(i>r)? 0:min(d2[l+r-i+t], r-i+1);
            while(0<=i-k-t && i+k<n && s[i-k-t]==s[i+k]) 
                k++;
            d[t][i]=k--;
            if(i+k>r) 
            {
                l=i-k-t;
                r=i+k;
            }
        }
    }
    
}

int main()
{
    //string s="ababcccba";
    string s="aabb";
    manachar(s);
    for(int i=0; i<s.size(); i++)
        cout<<d[0][i]<<" "<<d[1][i]<<endl;
}
