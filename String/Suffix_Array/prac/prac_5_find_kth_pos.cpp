/**
    https://vjudge.net/contest/512222#problem/H
*/
#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 200005

#define CS(i) cout<<"Case "<<i<<": "

typedef long long ll;

#define maxN 200005
#define MAXV (int)200005
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

    //swap A[i] with A[i+1], if A[i]!=A[i+1] call swapadjacent(i)
    void swapadjacent(int i)
    {
        if(lo == hi)
            return ;
        b[i]= b[i-1] + b[i+1] - b[i];
        c[i]= c[i-1] + c[i+1] - c[i];
        if( b[i+1]-b[i] == b[i]-b[i-1])
        {
            if(b[i]-b[i-1])
                return this->l->swapadjacent(b[i]);
            else
                return this->r->swapadjacent(i-b[i]);
        }
        else
            return;
    }

    //kth smallest element in [l, r]
    int kth(int l, int r, int k)
    {
        if(l>r) return 0;
        if(lo == hi) return lo;

        int inLeft = b[r] - b[l-1];//number of elements from subarray [L..R] that go to left subtree
        int lb = b[l-1];//amt of nos in first (l-1) nos that go in left
        int rb = b[r]; //amt of nos in first (r) nos that go in left
        if(k <= inLeft)
            return this->l->kth(lb+1, rb, k);
        return this->r->kth(l-lb, r-rb, k-inLeft);
    }

    //count of nos in [l, r] Less than or equal to k
    int LTE(int l, int r, int k)
    {
        if( (l>r) || (k<lo) ) return 0;//outside
        if(hi <= k) return (r-l+1);//full

        int lb = b[l-1], rb = b[r];
        return this->l->LTE(lb+1, rb, k) + this->r->LTE(l-lb, r-rb, k);
    }
 
    //count of nos in [l, r] equal to k
    int count(int l, int r, int k)
    {
        if( (l>r) || (k<lo) || (k>hi) ) return 0;
        if(lo == hi) return (r-l+1);
        
        int lb = b[l-1], rb = b[r], mid = (lo+hi)/2;
        if(k <= mid)
            return this->l->count(lb+1, rb, k);
        return this->r->count(l-lb, r-rb, k);
    }
 
    //sum of nos in [l ,r] less than or equal to k
    int sumk(int l, int r, int k)
    {
        if( (l>r) || (k<lo) ) return 0;
        if(hi <= k) return c[r] - c[l-1];

        int lb = b[l-1], rb = b[r];
        return this->l->sumk(lb+1, rb, k) + this->r->sumk(l-lb, r-rb, k);
    }
 
    ~wavelet_tree()
    {
        delete l;
        delete r;
    }

};


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

string s,t;

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
    //cout<<low-1<<" "<<p[low-1]<<endl;
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
    //cout<<low-1<<" ? "<<p[low-1]<<endl;
    return low;
}


void solve()
{
    ll n,m,i,j,k,a,b,c,x,y,z;
    ll sum=0LL, mn=LLONG_MAX, mx=LLONG_MIN;
    
    cin>>s>>m;

    s+="$";
    vector<int> v=build_suffix_array(s);
    vector<ll> pos;

    n = v.size();
    for(i=1; i<=n; i++)
    {
        A[i] = v[i-1];
    }

    wavelet_tree wt(A+1, A+n+1);

    while(m--){
        cin>>t>>k;

        x = Lower(v);
        y = Uppwer(v);

        if((y-x)<k){
            cout<<-1<<endl;
            continue;
        }
        //cout<<x<<" to "<<y<<endl;

        // pos.clear();
        // for(i=x; i<y; i++){
        //     //cout<<v[i]<<", ";cout<<endl;
        //     pos.push_back(v[i]);
        // }

        // sort(ALL(pos));
        // cout<<1+pos[k-1]<<endl;

        cout<< 1 + wt.kth(x+1, y, k) << endl;
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
