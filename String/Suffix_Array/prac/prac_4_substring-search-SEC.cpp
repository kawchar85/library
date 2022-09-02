//https://toph.co/arena?contest=sec-inter-university-junior-2022-r#!/p/630da521bafb30683b3d4f94

#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007

#define CS(i) cout<<"Case "<<i<<": "

typedef long long ll;

#define maxN 500005
#define MAXV 500005
#define MINV 0
//array values can be negative too, use appropriate minimum and maximum value

int A[maxN];
struct wavelet_tree{

    int lo, hi;
    wavelet_tree *l, *r;
    vector<int> b; //b[i]=how many elements from first i elements will go to the left subtree
    vector<int> c; //c holds the prefix sum of elements
 
    //nos are in range [x,y]
    //array indices are [from, to)
    //O(Log(maxV))
    wavelet_tree(int *from, int *to, int x=MINV, int y=MAXV)
    {
        lo=x, hi=y;
        if( from>=to ) return;
        if( hi==lo )
        {
            b.reserve(to-from+1);
            b.push_back(0);
            c.reserve(to-from+1);
            c.push_back(0);
            for(auto it = from; it != to; it++)
            {
                b.push_back(b.back() + 1);
                c.push_back(c.back()+*it);
            }
            return;
        }
        int mid = (lo+hi)/2;
        //lambda function
        auto f = [mid](int x)
        {
            return x <= mid;
        };
        b.reserve(to-from+1);
        b.push_back(0);
        c.reserve(to-from+1);
        c.push_back(0);
        for(auto it = from; it != to; it++)
        {
            b.push_back(b.back() + f(*it));
            c.push_back(c.back() + *it);
        }
        
        auto pivot = stable_partition(from, to, f);
        l = new wavelet_tree(from, pivot, lo, mid);
        r = new wavelet_tree(pivot, to, mid+1, hi);
    }

    //count of nos in [l, r] Less than or equal to k
    int LTE(int l, int r, int k)
    {
        if( (l>r) || (k<lo) ) return 0;//outside
        if(hi <= k) return (r-l+1);//full

        int lb = b[l-1], rb = b[r];
        return this->l->LTE(lb+1, rb, k) + this->r->LTE(l-lb, r-rb, k);
    }
 
 
    ~wavelet_tree()
    {
        delete l;
        delete r;
    }

};

vector< int > cc,lcp;

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

    cc = c;

    return p;
}

//O(n)
void build_lcp_array(string& s, vector<int> &p)
{
    int i,k=0;
    int n=(int)s.size();
    lcp.resize(n);

    //lcp[i] = lcp of suffix in position i and position i - 1
    k=0;
    for(i=0; i<n-1; i++)
    {
        int pi=cc[i];
        int j=p[pi-1];
        while(s[i+k]==s[j+k]) k++;
        lcp[pi]=k;
        k=max(k-1, 0);

       // cout << " hhhs \n";return;
    }
    
}

//lcp of suffix start from i and j
int LCP(int i, int j)
{
    //use sparse table/segment tree
    int pi=cc[i];
    int pj=cc[j];

    if(pi>pj) swap(pi,pj);

    return query(pi+1, pj);

}


int get(int a, int b){
    if(a>b) swap(a,b);
    return query(a+1, b);
}
int getPrev(int i, int len)
{
    int ans=i;
    int lo=0,hi=i-1,mid;

    while(lo<=hi)
    {
        mid=(lo+hi)/2;

        if(get(mid, i)>=len)
        {
            ans=mid;
            hi=mid-1;
        }
        else
        {
            lo=mid+1;
        }
    }
    return ans;
}
int getNext(int i, int len)
{
    int ans=i;
    int lo=i+1,hi=(int)lcp.size()-1,mid;

    while(lo<=hi)
    {
        mid=(lo+hi)/2;
        if(get(mid, i)>=len)
        {
            ans=mid;
            lo=mid+1;
        }
        else
        {
            hi=mid-1;
        }
    }

    return ans;
}

ll cum[MAX];
void solve(){
    ll n,m,i,j,x,y,l,r;
    string all="",tmp,s;
    vector< string > str;

    str.push_back("");

    cin >> n;
    for(i = 0; i < n; i++){
        cin >> tmp;

        str.push_back(tmp);
        all += tmp;
        cum[i+1] = cum[i] + tmp.size();
    }

    s = all;
    s += "$";
    //cout<<s<<" ...\n";

    vector<int> v=build_suffix_array(s);
     build_lcp_array(s, v);

     n=(ll)lcp.size();
     for(int i=0; i<n; i++)
         arr[i]=lcp[i];

     pre_calculation(n);
    n = v.size();
    for(i=1; i<=n; i++)
        A[i] = v[i-1];
    wavelet_tree wt(A+1, A+n+1);

    // for(i=0; i<n; i++)
    //  cout << v[i]<<" ";cout<<endl;

    cin >> m;
    while(m--){
        cin >> x >> l >> r >> y;


        int len = r - l + 1;
        int ls = cum[x - 1] + l - 1;

        //cout << x-1 << " " << cum[x-1]<<" "<<ls<<endl;
        int SaID = cc[ls];
        //cout << SaID <<" gbrthy  "<< ls<<endl;

        ll yy = y;

        x = getPrev(SaID, len);
        y = getNext(SaID, len);

        // cout << x <<" SA "<<y << endl;
        // for(i = x; i<=y; i++)
        //     cout<<v[i]<<",";cout<<endl;

        //ans er range
        r = cum[yy] - len;
        l = cum[yy] - str[yy].size();

        if(r < l || r < 0){
            cout << 0 << endl;
            continue;
        }

        //cout<< l << " need "<< r <<endl;

        ll cnt = wt.LTE(x+1, y+1, r);
        cnt -= wt.LTE(x+1, y+1, l-1);

        cout << cnt << endl;
    }
}

int32_t main()
{
    FAST

    ll TC=1LL,cs=1LL;

    //cin>>TC;

    while(TC--){
        //CS(cs++);
        solve();
    }

    return 0;
}
