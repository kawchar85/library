///nLog^2(n)
#include<bits/stdc++.h>
using namespace std;
const int MAX =100005;


void build_suffix_array(string s)
{
    int n=(int)s.size();
    vector< pair< pair<int,int>,int > > a(n); //{left part,right part},pos
    vector<int> p(n), c(n);
    int i,k=0;

    //k=0;
    for(i=0; i<n; i++)
        a[i]={{s[i]-'a', -1},i};
    sort(a.begin(), a.end());

    for(i=0; i<n; i++) p[i]=a[i].second;
    c[p[0]]=0;
    for(i=1; i<n; i++)
        c[p[i]]=c[p[i-1]]+(a[i].first!=a[i-1].first);
    
    while((1<<k)<n)
    {
        for(i=0; i<n; i++)
            a[i]={{c[i],c[(i+(1<<k))%n]},i};
        sort(a.begin(), a.end());

        for(i=0; i<n; i++) p[i]=a[i].second;
        c[p[0]]=0;
        for(i=1; i<n; i++)
        {
            c[p[i]]=c[p[i-1]]+(a[i].first!=a[i-1].first);
        }
        k++;
    }

    //print
    for(i=0; i<n; i++) cout<<p[i]<<" "<<s.substr(p[i], n-p[i]-1)<<"\n";
}


int main()
{
    string s;
    cin>>s;
    s+="$";
    build_suffix_array(s);
    return 0;
}
