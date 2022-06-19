/**
Resource: https://rezwanarefin01.github.io/posts/palindromic-tree-01/
*/

#include<bits/stdc++.h>
using namespace std;

const int N = 10004;
const int t_sz= 26;

struct Palindromic_Tree{
    
    int tree[N][t_sz], idx;
    int len[N], link[N], t,n;
    int endHere[N],occ[N],total=0;
    int stop[N];//right id of pal, need for printing
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
        stop[t]=p;
    }

    void init(string &ss)
    {
        s+=ss;
        n=(int)s.size();
        
        for(int i=1; i<n; i++){
            add(i);
            total+=endHere[t];
            //palindrom end in pos i=endHere[t]
            //cout<<i<<"-->"<<endHere[t]<<endl;
        }
        for(int i = idx; i > 2; i--)
        {
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
    int t=1;
    string s;
    Palindromic_Tree p;
    //cin>>t;
    for(int cs=1; cs<=t; cs++)
    {
        cin>>s;
        p.init(s);
        cout<<p.cntTotal()<<endl;
        //cout<<p.cntDistinct()<<endl;
        //cout<<"Case #"<<cs<<": "<<p.cntPalindrom()<<endl;
        //p.clear();
    }
    return 0;
}
