//https://vjudge.net/problem/URAL-2060
/*
    Given a string S. Count number of
    tuples (i,j,k) such that i≤j<k and
    s[i…j] and s[j+1…k] both are palindromes.
*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long 

const int N = 300005;
const int t_sz= 26;

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
    /**
    একটা Index j এর জন্য i এর
    সম্ভাব্য উপায় suf[j] টা, 
    আর k এর উপায় pref[j+1] টা।
    এদের গুনফলের যোগফল নিলেই 
    মোট উপায় পাওয়া যাবে
    */
    for(int j=0; j+1<n; j++)
        sum+=suf[j]*pref[j+1];

    cout<<sum<<endl;

    return 0;
}
