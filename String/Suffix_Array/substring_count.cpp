/**
    Given a string S and n queries,
    each query is a string T. For
    each request you need to determine
    whether the string T occurs as 
    a substring in S.

*/
#include<bits/stdc++.h>
using namespace std;

string s,t;

//O(NLogN)
vector<int> build_suffix_array(string s)
{
    int alphabet=256;
    int n=(int)s.size();
    int i,k,cls;

    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    vector<int> ptmp(n), ctmp(n);

    pair<int, int> cur, prev;

    for(i=0; i<n; ++i)
        cnt[s[i]]++;
    for(i=1; i<alphabet; i++)
        cnt[i]+=cnt[i-1];
    for(i=0; i<n; i++)
        p[--cnt[s[i]]]=i;

    
    c[p[0]]=0;
    cls=1;
    for(i=1; i<n; i++)
    {
        if(s[p[i]] != s[p[i-1]])
            cls++;
        c[p[i]]=cls-1;
    }
    
    for(k=0; (1<<k)<n; ++k)
    {
        for(i=0; i<n; ++i)
        {
            ptmp[i]=p[i]-(1<<k);
            if(ptmp[i]<0) ptmp[i]+=n;
        }
        fill(cnt.begin(), cnt.begin()+cls, 0);

        for(i=0; i<n; i++)
            cnt[c[ptmp[i]]]++;
        for(i=1; i<cls; i++)
            cnt[i]+=cnt[i-1];
        for(i=n-1; ~i; i--)
            p[--cnt[c[ptmp[i]]]]=ptmp[i];

        ctmp[p[0]]=0;
        cls=1;
        for(i=1; i<n; ++i)
        {
            cur={c[p[i]], c[(p[i]+(1<<k))%n]};
            prev={c[p[i-1]], c[(p[i-1]+(1<<k))%n]};

            if(cur!=prev)
                cls++;
            ctmp[p[i]]=cls-1;
        }
        c.swap(ctmp);
    }
    return p;
}

int isEqual(int x)
{
    int m=(int)t.size();
    for(int i=0; i<m; i++)
    {
        if(s[i+x]==t[i])
            continue;
        if(s[i+x]<t[i])
            return -1;
        else
            return 1;
    }
    return 0;
}

//O(NLogN)
int Lower(vector<int>& p)
{
    int low=0,x;
    int high=(int)p.size()-1;
    int mid;

    while(low<=high)
    {
        mid=(low+high)/2;
        x=isEqual(p[mid]);
        if(x<0)
            low=mid+1;
        else
            high=mid-1;

    }
    return low;
}

int Uppwer(vector<int>& p)
{
    int low=0,x;
    int high=(int)p.size()-1;
    int mid;

    while(low<=high)
    {
        mid=(low+high)/2;
        x=isEqual(p[mid]);
        if(x<=0)
            low=mid+1;
        else
            high=mid-1;

    }
    return low;
}

int substring_count(vector<int>& p)
{
    return Uppwer(p)-Lower(p);
}

int main()
{
    int n;
    cin>>s>>n;
    s+="$";
    vector<int> v=build_suffix_array(s);
    while(n--)
    {
        cin>>t;
        cout<<substring_count(v)<<endl;
    }
    return 0;
}
