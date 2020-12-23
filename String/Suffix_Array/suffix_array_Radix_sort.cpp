///nLog(n)
#include<bits/stdc++.h>
using namespace std;

void radix_sort(vector< pair< pair<int,int>,int > > &a)
{
    int i;
    int n=(int)a.size();
    vector<int> cnt(n,0),pos(n);
    vector< pair< pair<int,int>,int > > a_new(n);

    //counting sort for second element
    for(auto x : a)
        cnt[x.first.second]++;
    pos[0]=0;
    for(i=1; i<n; i++)
        pos[i]=pos[i-1]+cnt[i-1];
    for(auto x : a)
    {
        i=x.first.second;
        a_new[pos[i]]=x;
        pos[i]++;
    }
    a=a_new;


    fill(cnt.begin(), cnt.end(), 0);
    //counting sort for first element
    for(auto x : a)
        cnt[x.first.first]++;
    pos[0]=0;
    for(i=1; i<n; i++)
        pos[i]=pos[i-1]+cnt[i-1];
    for(auto x : a)
    {
        i=x.first.first;
        a_new[pos[i]]=x;
        pos[i]++;
    }
    a=a_new;

}

void build_suffix_array(string s)
{
    int n=(int)s.size();
    vector< pair< pair<int,int>,int > > a(n); //left,right,pos
    vector<int> p(n), c(n);
    int i,k=0;

    for(i=0; i<n; i++)
        a[i]={{(int)s[i], 1},i};
    sort(a.begin(), a.end());
    //radix_sort(a); //problem 
    
    for(i=0; i<n; i++) p[i]=a[i].second;
    c[p[0]]=0;
    for(i=1; i<n; i++)
    {
        if(a[i].first==a[i-1].first)
            c[p[i]]=c[p[i-1]];
        else
            c[p[i]]=c[p[i-1]]+1;
    }
    
    while((1<<k)<n)
    {
        for(i=0; i<n; i++)
            a[i]={{c[i],c[(i+(1<<k))%n]},i};
        radix_sort(a);

        for(i=0; i<n; i++) p[i]=a[i].second;
        c[p[0]]=0;
        for(i=1; i<n; i++)
        {
            if(a[i].first==a[i-1].first)
                c[p[i]]=c[p[i-1]];
            else
                c[p[i]]=c[p[i-1]]+1;
        }
        k++;
    }


    for(i=0; i<n; i++)
        cout<<p[i]<<" "<<s.substr(p[i], n-p[i]-1)<<"\n";


    //LCP
    vector<int> lcp(n);
    k=0;
    for(i=0; i<n-1; i++)
    {
        int pi=c[i];
        int j=p[pi-1];
        while(s[i+k]==s[j+k]) k++;
        lcp[pi]=k;
        k=max(k-1, 0);
    }
    for(i=0; i<n; i++)
        cout<<lcp[i]<<", ";

}


int main()
{
    string s;
    cin>>s;
    s+="$";
    build_suffix_array(s);
    return 0;
}
