#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define endl "\n" 

vector<int>p,c,lcp;

#define MAX 1000000
#define MAXPOWN 1048576     // 2^(ceil(log_2(MAXN)))
#define MAXLEV 21           // ceil(log_2(MAXN)) + 1
#define identity INT_MAX

int N, levels;
int arr[MAX];
int dst[MAXPOWN][MAXLEV+1];

int F(int x, int y)
{
    return min(x,y);
}

void build(int depth, int l, int r)
{
    if(l==r) return;

    int mid=(l+r)>>1;
    
    dst[mid][depth]=arr[mid];
    for(int i=mid-1; i>=l; i--)
    {
        dst[i][depth]=F(dst[i+1][depth], arr[i]);
    }

    if(mid+1<=r)
    {
        dst[mid+1][depth]=arr[mid+1];
        for(int i=mid+2; i<=r; i++)
            dst[i][depth]=F(dst[i-1][depth], arr[i]);
    }

    build(depth+1, l, mid);
    build(depth+1, mid+1, r);
}

//0-based
int query(int l, int r)
{
    if(l>r) return identity;
    if(l==r) return arr[l];
    unsigned int lvl = __builtin_clz(l^r) - levels -1;
    return F(dst[l][lvl], dst[r][lvl]); 
}
//nLog(n)
void pre_calculation(int n)
{
    //n-->size of arr[]
    levels=__builtin_clz(n);
    N= 1<<(31-levels);
    if(n!=N)
    {
        levels--;
        N<<=1;
    }

    while(n<N) arr[n++]=identity;
    build(0, 0, N-1);

}

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

    //print
    /*
    for(i=0; i<n; i++)
        cout<<p[i]<<" "<<s.substr(p[i], n-p[i]-1)<<"\n";
    */
    /*
    for(i=0; i<n; i++)
        cout<<i<<" "<<p[i]<<"\n";
    for(i=0; i<n; i++)
        cout<<i<<"::"<<c[i]<<"\n";
    cout<<endl;
    */
}


//O(n)
void build_lcp_array(string& s)
{
    int i,k=0;
    int n=(int)s.size();
    lcp.resize(n);

    //lcp[i] = lcp of suffix in position i and position i - 1
    k=0;
    for(i=0; i<n-1; i++)
    {
        int pi=c[i];
        int j=p[pi-1];
        while(s[i+k]==s[j+k]) k++;
        lcp[pi]=k;
        k=max(k-1, 0);
    }
    ///*
    for(i=0; i<n; i++)
        cout<<lcp[i]<<", "<<p[i]<<" "<<s.substr(p[i], n-p[i]-1)<<"\n";
    cout<<"\n---------------\n";
    //*/
}

//lcp of suffix start from i and j
int LCP(int i, int j)
{
    //use sparse table/segment tree
    int pi=c[i];
    int pj=c[j];

    if(pi>pj) swap(pi,pj);

    return query(pi+1, pj);

    /*int mn=INT_MAX;
    for(i=pi+1; i<=pj; i++)
        mn=min(mn,lcp[i]);
    return mn;*/
}

void init(string s)
{
    s+="$";
    build_suffix_array(s);
    build_lcp_array(s);

    int n=(int)lcp.size();
    for(int i=0; i<n; i++)
        arr[i]=lcp[i];
    pre_calculation(n);

}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string s;
    cin>>s;
    
    init(s);
    int m,x,y;
    cin>>m;
    while(m--)
    {
        cin>>x>>y;
        cout<<LCP(x,y)<<endl;
    }

    return 0;
}
