/**
    Given a sequence of integers 
    a1,a2,...,an and q queries 
    x1,x2..., xq on it. For each
    query xi you have to count 
    the number of pairs (l, r) 
    such that 1 ≤ l ≤ r ≤ n and
    gcd(al, al+1, ..., ar)= xi.
*/
#include <bits/stdc++.h>

using namespace std;

map<int, long long> cnt;


void CountGcd(vector<int>& v)
{
    map<int, int> divisors;
    map<int, int> nextDivisors;
    int n=(int)v.size();
    for(int i=0; i<n; i++)
    {
        nextDivisors.clear();
        for(auto &p : divisors) 
        {
            nextDivisors[__gcd(p.first, v[i])] += p.second;
        }
        nextDivisors[v[i]]++;

        swap(nextDivisors, divisors);
        for (auto &p : divisors)
            cnt[p.first] += p.second;
    }
}

int main() 
{
    ios_base::sync_with_stdio(false);
    
    int n,i; 
    cin >> n;
    vector<int> v;

    for(i=0; i<n; ++i)
    {
        int xx;
        cin>>xx;
        v.push_back(xx);
    }
    CountGcd(v);
    int q; 
    cin >> q;
    while(q --> 0) 
    {
        int x; cin >> x;
        cout << cnt[x] << endl;
    }
}
