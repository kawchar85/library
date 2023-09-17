#include<bits/stdc++.h>
using namespace std;

vector<int>p,c,lcp;

///nLog(n)
void build_suffix_array(string& s)
{
    int alphabet=256;
    int n=(int)s.size();
    int i,k,cls;

    vector<int> cnt(max(alphabet, n), 0);
    vector<int> ptmp(n), ctmp(n);
    p.resize(n);
    c.resize(n);

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

    /*
    for(i=0; i<n; i++)
        cout<<p[i]<<" ";
    cout<<endl;
    */
}


//O(n)
void build_lcp_array(string& s)
{
    int i,k=0;
    int n=(int)s.size();
    lcp.resize(n);

    k=0;
    for(i=0; i<n-1; i++)
    {
        int pi=c[i];
        int j=p[pi-1];
        while(s[i+k]==s[j+k]) k++;
        lcp[pi]=k;
        k=max(k-1, 0);
    }
    /*
    for(i=0; i<n; i++)
        cout<<lcp[i]<<", ";
    cout<<"\n---------------\n";
    */
}

long long uniqueSubString(string& s)
{
    long long cnt=0;
    int n=(int)s.size();
    for(int i=1; i<n; i++)
    {
        cnt+=(n-p[i]-1LL-lcp[i]);
        //n-p[i]-1 is length.
        //lcp[i] ta ageer tar sathe same, ara unique nah
    }
    return cnt;
}

int main()
{
    string s;
    cin>>s;
    s+="$";
    build_suffix_array(s);
    build_lcp_array(s);
    cout<<uniqueSubString(s);
    return 0;
}
