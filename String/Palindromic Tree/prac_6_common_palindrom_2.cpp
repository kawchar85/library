//https://vjudge.net/problem/Gym-100548G

/**
    Given two strings A and B, what
    is the number of their common 
    palindrome substrings? The amount
    of common palindrome substrings 
    between two strings is defined 
    as the number of quadruple (p, q, s, t),
    which satisfies that:
    1. 1 ≤ p, q ≤|A|, 1 ≤ s, t ≤|B|, p ≤ q and s ≤ t.
    2. A[p...q] = B[s...t]
    3. A[p...q] is palindrome
*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long 

const int N = 1000006;
const int t_sz= 30;

struct Palindromic_Tree{
    
    int tree[N][t_sz], idx;
    int len[N], link[N], t,n;
    int occ[N][2];
    string s="#";

    Palindromic_Tree(){
        for(int i=0; i<N; i++)
        {
            occ[i][0]=occ[i][1]=len[i]=link[i]=0;
            for(int j=0; j<t_sz; j++)
                tree[i][j]=0;
        }
        
        len[1] = -1, link[1] = 1;
        len[2] = 0, link[2] = 1;

        idx = t = 2;
    }

    void add(int p, int cntId)
    {
        while(s[p-len[t]-1] != s[p]) t = link[t];
        int x = link[t], c = s[p]-'a';
        while(s[p-len[x]-1] != s[p]) x = link[x];
        
        if(!tree[t][c])
        {
            tree[t][c] = ++idx;
            len[idx] = len[t] + 2;
            link[idx] = len[idx] == 1 ? 2 : tree[x][c];
        }
        
        t = tree[t][c];
        occ[t][cntId]++;
    }

    ll init(string &s1, string &s2)
    {
        ll cp=0LL;
        s+=s1;
        n=(int)s.size();
        
        for(int i=1; i<n; i++){
            add(i, 0);
        }

        int x=n;
        s+=char('a'+26);//invalid char
        s+=s2;
        n=(int)s.size();
        for(int i=x; i<n; i++){
            add(i, 1);
        }
        for(int i = idx; i > 2; i--){
            occ[link[i]][0] += occ[i][0];
            occ[link[i]][1] += occ[i][1];

            cp+=1LL*occ[i][0]*occ[i][1];
            //cout<<i<<": "<<occ[i][0]<<" "<<occ[i][1]<<endl;
        }

        return cp;
    }
    void clear(){
        for(int i=0; i<=idx; i++)
        {
            occ[i][0]=occ[i][1]=len[i]=link[i]=0;
            for(int j=0; j<t_sz; j++)
                tree[i][j]=0;
        }

        len[1] = -1, link[1] = 1;
        len[2] = 0, link[2] = 1;
        idx = t = 2;
        s="#"; 
    }
};

Palindromic_Tree p;
ll commonPalindrom(string &s, string &s2)
{
    p.clear();
    return p.init(s, s2);
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t=1;
    string s,s2;

    cin>>t;
    for(int cs=1; cs<=t; cs++)
    {
        cin>>s>>s2;
        cout<<"Case #"<<cs<<": ";
        cout<<commonPalindrom(s,s2)<<endl;
    }
    return 0;
}
