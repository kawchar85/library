//https://codeforces.com/problemset/problem/159/D
/*
    Given a string S. Count number of
    quantity of tuples (a, b, x, y) 
    such that 1 ≤ a ≤ b < x ≤ y ≤ |s| 
    and substrings s[a... b], s[x... y] 
    are palindromes
*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long 

const int N = 3005;
const int t_sz= 26;
ll cum[N];

ll getSum(ll i, ll j)
{
    if(i==0) return cum[j];
    return cum[j]-cum[i-1];
}
struct Palindromic_Tree{
    
    int tree[N][t_sz], idx;
    int len[N], link[N], t,n;
    int endHere[N],occ[N],total=0;
    string s="#";

    Palindromic_Tree(){
        memset(occ, 0, sizeof(occ));
        len[1] = -1, link[1] = 1;
        len[2] = 0, link[2] = 1;
        endHere[1]=endHere[2]=0;
        idx = t = 2;
    }

    void add(int p)
    {
        while(s[p-len[t]-1] != s[p]) t = link[t];
        int x = link[t], c = s[p] - 'a';
        while(s[p-len[x]-1] != s[p]) x = link[x];
        
        if(!tree[t][c])
        {
            tree[t][c] = ++idx;
            len[idx] = len[t] + 2;
            link[idx] = len[idx] == 1 ? 2 : tree[x][c];
            endHere[idx]=1+endHere[link[idx]];
        }
        
        t = tree[t][c];
        occ[t]++;
    }

    void init(string &ss, vector<ll> &v)
    {
        s+=ss;
        n=(int)s.size();
        
        for(int i=1; i<n; i++){
            add(i);
            total+=endHere[t];
            //palindrom end in pos i=endHere[t]
            //cout<<i<<"-->"<<endHere[t]<<endl;
            v.push_back(endHere[t]);
        }
        for(int i = idx; i > 2; i--) 
            occ[link[i]] += occ[i];

        //print();
    }
    void print(){
        for(int i=3; i<=idx; i++)
            cout<<"len="<<len[i]<<",cnt="<<occ[i]<<endl;
        
    }
    void clear(){
        for(int i=0; i<=idx; i++)
        {
            occ[i]=endHere[i]=len[i]=link[i]=0;
            for(int j=0; j<t_sz; j++)
                tree[i][j]=0;
        }

        len[1] = -1, link[1] = 1;
        len[2] = 0, link[2] = 1;
        endHere[1]=endHere[2]=0;
        idx = t = 2;
        total=0;
        s="#"; 
    }
    int cntDistinct(){
        return idx-2;
    }
    int cntTotal(){
        return total;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string s;
    Palindromic_Tree p;
    vector<ll> suf;//suf[i]=no of pali end at i
    vector<ll> pref;//pref[i]=no of pali start from i

    cin>>s;

    //cal suf[]
    p.init(s, suf);
    p.clear();

    //cal pref[]
    reverse(s.begin(), s.end());
    p.init(s,pref);
    reverse(pref.begin(), pref.end());

    ll sum=0;
    int n=(int)s.size();
    
    cum[0]=pref[0];
    for(int i=1; i<n; i++)
        cum[i]+=cum[i-1]+pref[i];

    for(int b=0; b+1<n; b++){
        sum+=suf[b]*getSum(b+1, n-1);//x=b+1 to n-1
        //cout<<suf[b]<<" "<<getSum(b+1, n-1)<<endl;
    }

    cout<<sum<<endl;

    return 0;
}
