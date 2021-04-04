#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
/**
	https://vjudge.net/problem/SPOJ-QUERYSTR
	
     find longest common suffix od=f
     s[1...n],s[1...i]

     z[i]=longest common prefix between
     s[1...n], s[i...n]
*/

//O(s.size())
vector<int> z_function(string &s)
{
    int n = (int) s.length();
    vector<int> z(n);
    z[0]=n;
    for(int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

void solve()
{
	string s;
	int m, x;

	cin>>s;
	reverse(s.begin(), s.end());
	vector<int> v = z_function(s);
	reverse(v.begin(), v.end());

	cin>>m;
	while(m--)
	{
		cin>>x;
		x--;
		cout<<v[x]<<endl;
	}

}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
}
   
