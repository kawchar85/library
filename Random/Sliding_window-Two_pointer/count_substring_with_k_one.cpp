#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MAX 1000006

int cnt[MAX];
string s;

/**

	Given a binary string s. Your task is to find the
	number of its substrings, containing exactly k 
	characters "1".

	CF 165C
	Idea:
	variable "one" diye number of 1 count korlam.
	akta fixed position a jodi count of 1 equal x(x>=k)
	hoy, taile x-k ta 1 jei position a ache, tar tik porer
	position teke ai fixed position obdi akta sub string 
	nile tar count of 1 equal k hobe.
	cnt[i]--> count of 1 = i amon koyta position ache
	cnt[x-k] er er value joto tik totho ghula sub str possible 
*/

ll countSubStringWithK1(ll k)
{
	ll ans=0LL;
	cnt[0]=1;
	int one=0;
	for(auto ch : s)
	{
		if(ch=='1')
			one++;
		if(one>=k)
			ans+=cnt[one-k];
		cnt[one]++;
	}

	return ans;
}

int main()
{
	ll k;
	cin>>k>>s;
	cout<<countSubStringWithK1(k)<<endl;
}