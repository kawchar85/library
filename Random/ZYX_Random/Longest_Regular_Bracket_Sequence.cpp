/**
    Longest Regular Bracket Sequence
    CF 5C
*/
#include<bits/stdc++.h>
using namespace std;

#define MAX 1000006
#define ll long long

ll freq[MAX];
ll dp[MAX];

int main()
{
    ll len,mx,i;
    string s;
    cin>>s;

    stack<ll> st;

    freq[0]=1;
    for(i=0; i<s.size(); i++)
    {
        if(s[i]=='(')
        {
            st.push(i);
            dp[i]=0;
        }
        else
        {
            if(st.size())
            {
                len=i-st.top()+1;
                dp[i]=len;
                if(st.top())
                {
                    dp[i]+=dp[st.top()-1];
                }
                freq[dp[i]]++;
                st.pop();
            }
        }
    }

    mx=0;
    for(i=0; i<=s.size(); i++)
    {
        mx=max(mx,dp[i]);
    }
    cout<<mx<<" "<<freq[mx]<<endl;
    return 0;
}

