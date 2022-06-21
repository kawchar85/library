//https://www.spoj.com/problems/MKTHNUM/

#include<bits/stdc++.h>
using namespace std;

#define maxN 200005
#define MAXV 100005
#define MINV 1
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

int main()
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);

    int i,n,k,j,q,l,r,type;
    set<int> s;
    map<int,int> val,rVal;

    cin>>n>>q;
    //1-based
    for(i=1; i<=n; i++){
        cin>>A[i];
        s.insert(A[i]);
    }
    k=1;
    for(auto it : s)
    {
        val[it]=k;
        rVal[k]=it;
        k++;
    }

    for(i=1; i<=n; i++){
        A[i]=val[A[i]];
    }

    wavelet_tree wt(A+1, A+n+1);

    while(q--)
    {
        cin >> l >> r >> k;
        cout << rVal[wt.kth(l, r, k)] << endl;
        
    }
    return 0;
}
