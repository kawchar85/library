#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,i;
    cin>>n;
    vector<int> v;
    for(i=0; i<n; i++)
    {
        int xx;
        cin>>xx;
        ///use upper_bound for non-decreasing subsequence
        auto it = lower_bound(v.begin(), v.end(), xx);
        if(it==v.end())
            v.push_back(xx);
        else
            v[it-v.begin()]=xx;
    }
    cout<<"LIS : "<<v.size()<<endl;

    return 0;
}
