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
    //int endHere[N],total=0;
    int occ[N];
    //int stop[N];//right id of pal, need for printing
    string s="#";

    Palindromic_Tree(){
        for(int i=0; i<N; i++)
        {
            occ[i]=len[i]=link[i]=0;
            for(int j=0; j<t_sz; j++)
                tree[i][j]=0;
        }
        
        len[1] = -1, link[1] = 1;
        len[2] = 0, link[2] = 1;
        //endHere[1]=endHere[2]=0;
        idx = t = 2;
    }

    void add(int p)
    {
        while(s[p-len[t]-1] != s[p]) t = link[t];
        int x = link[t], c = s[p]-'a';
        while(s[p-len[x]-1] != s[p]) x = link[x];
        
        if(!tree[t][c])
        {
            tree[t][c] = ++idx;
            len[idx] = len[t] + 2;
            link[idx] = len[idx] == 1 ? 2 : tree[x][c];
            //endHere[idx]=1+endHere[link[idx]];
        }
        
        t = tree[t][c];

        occ[t]++;
        //stop[t]=p;
    }

    void init(string &ss)
    {
        s+=ss;
        n=(int)s.size();
        
        for(int i=1; i<n; i++){
            add(i);
            //total+=endHere[t];
            //palindrom end in pos i=endHere[t]
            //cout<<i<<"-->"<<endHere[t]<<endl;
        }
        for(int i = idx; i > 2; i--){
            occ[link[i]] += occ[i];

            //print palindrom
            //int r=stop[i],l=stop[i]-len[i]+1;
            //cout<<s.substr(l,len[i])<<endl;
        }

        //print();
    }
    void print(){
        for(int i=3; i<=idx; i++)
            cout<<"len="<<len[i]<<",cnt="<<occ[i]<<endl;
        
    }
    void clear(){
        for(int i=0; i<=idx; i++)
        {
            occ[i]=0;
            len[i]=link[i]=0;
            for(int j=0; j<t_sz; j++)
                tree[i][j]=0;
        }

        len[1] = -1, link[1] = 1;
        len[2] = 0, link[2] = 1;
        //endHere[1]=endHere[2]=0;
        idx = t = 2;
        //total=0;
        s="#"; 
    }
    int cntDistinct(){
        return idx-2;
    }
};

ll cnt[N][2];
Palindromic_Tree p;
ll commonPalindrom(string &s, string &s2)
{
    
    p.clear();
    p.init(s);
    for(int i=3; i<=p.idx; i++)
        cnt[i][0]=p.occ[i];

    p.clear();
    //s=s+"#"+s2;
    s+=char('a'+26);//invalid
    s+=s2;
    p.init(s);
    for(int i=3; i<=p.idx; i++)
        cnt[i][1]=p.occ[i];

    ll total=0LL,diff;
    for(int i=3; i<=p.idx; i++)
    {
        //i'th node jei palindrom represent
        //kore, oita 2nd string a koyta ache?
        diff=cnt[i][1]-cnt[i][0];

        //cntIn1st*cntIn2nd
        total+=cnt[i][0]*diff;
        //cout<<cnt[i][0]<<" "<<diff<<" for "<<i<<endl;

        //clr for next test
        cnt[i][1]=cnt[i][0]=0;

    }
    return total;
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
