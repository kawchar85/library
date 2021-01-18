/**
    https://codeforces.com/contest/1400/problem/F
*/
#include<bits/stdc++.h>
#define MAX 1003
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
using namespace std;
#define INF INT_MAX/10;
#define t_sz 10

struct node{
    int ending;
    int next[t_sz];
    int link,par;

    node()
    {
        ending=0;
        memset(next,-1, sizeof next);
        par=-1;
        link=-1;
    }
};

struct aho_corasick{
    vector< node > aho;
    aho_corasick(){
        aho.emplace_back();
    }
    int ID(char ch){
       return ch-'0';
    }
    void ADD(string &s)
    {
        int now,u=0;
        for(auto ch:s)
        {
            now=ID(ch);
            if(aho[u].next[now]==-1)
            {
                aho[u].next[now]=aho.size();
                aho.emplace_back();
            }
            u=aho[u].next[now];
        }

        aho[u].ending++;
    }
    int transition(int u, int i) //from,by
    {
        if(u==-1) return 0; //root
        if(~aho[u].next[i]) return aho[u].next[i];
        return aho[u].next[i]=transition(aho[u].link, i);
    }
    void push_links()
    {
        queue<int> q;
        q.push(0);
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            for(int i=0; i<t_sz; i++)
            {
                int v=aho[u].next[i];
                if(v==-1) continue;

                aho[v].par=u;
                aho[v].link=transition(aho[u].link, i);
                aho[v].ending+=aho[aho[v].link].ending;
            
                q.push(v);
            }
        }
    }
    int CNT(string &s)
    {
        int u=0,sum=0;
        for(int i=0; i<s.size(); i++)
        {
            int x=ID(s[i]);
            u=transition(u, x);
            sum+=aho[u].ending;
        }
        return sum;
    }
    void clear(){
        aho.clear();
        aho.emplace_back();
    }
};

int x;
string s;
vector<string> all_x_prime;
aho_corasick ac;
int dp[MAX][5003];

bool x_prime(string &s)
{
    //cout<<s<<"---- ok?";
    int n=s.size();
    for(int i=0; i<n; i++)
    {
        int sum=0;
        for(int j=i; j<n; j++)
        {
            sum+=ac.ID(s[j]);
            if(x!=sum && x%sum==0)
            {
                //cout<<" --- 0 :"<<sum<<endl;
                return 0;
            }
        }
    }
    return 1;
}

void back_track(string s, int rem)
{
    //cout<<s<<" --- "<<rem<<endl;
    if(rem<0) return;
    if(rem==0)
    {
        if(x_prime(s))
            all_x_prime.push_back(s);
        return;
    }
    for(char ch='1'; ch<='9'; ch++)
    {
        s+=ch;
        back_track(s, rem-(ch-'0'));
        s.pop_back();
    }
}
int solve(int pos, int state)//pos in s, state in aho-corasick
{
    if(ac.aho[state].ending) return INF;
    if(pos==s.size()) return 0;
    if(~dp[pos][state]) return dp[pos][state];
    return dp[pos][state]=min(solve(pos+1, ac.transition(state, ac.ID(s[pos]))) , 1+solve(pos+1, state));
}
int main()
{
    FAST
    vector<string> v;
    int n,i,j,k;
    memset(dp, -1, sizeof dp);

    cin>>s>>x;
    back_track("",x);
    for(auto now : all_x_prime){
        ac.ADD(now);
        //cout<<now<<",\n";
    }
    ac.push_links();
    cout<<solve(0,0)<<endl;
    return 0;
}
