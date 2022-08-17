#include<bits/stdc++.h>
using namespace std;

/* Finds longest strictly increasing subsequence. O(n log k) algorithm. */
void find_lis(vector<int> &a, vector<int> &id)
{
	vector<int> p(a.size());
	int u, v,i;

	if(a.empty()) return;

	id.push_back(0);

	for(i=1; i<a.size(); i++)
    {
        // If next element a[i] is greater than last element of
        // current longest subsequence a[id.back()], just push it at back of "id" and continue
		if(a[id.back()]<a[i])
        {
			p[i] = id.back();
			id.push_back(i);
			continue;
		}

        // Binary search to find the smallest element referenced by id which is just bigger than a[i]
        // Note : Binary search is performed on id (and not a).
        // Size of id is always <=k and hence contributes O(log k) to complexity.
		for(u = 0, v = id.size()-1; u < v;)
        {
			int c = (u + v) / 2;
			if (a[id[c]] <a[i]) u=c+1; else v=c;
		}

        // Update id if new value is smaller then previously referenced value
		if (a[i] <a[id[u]])
        {
			if(u > 0) p[i] = id[u-1];
			id[u] = i;
		}
	}

	for(u=id.size(), v=id.back(); u--; v=p[v]) id[u] = v;
}

int main()
{
	int n,i,x;
	vector<int> seq,lis;
	cin>>n;
	for(i=0; i<n; i++)
    {
        cin>>x;
        seq.push_back(x);
    }
    find_lis(seq, lis);

    cout<<lis.size()<<endl;
	for(i=0; i<lis.size(); i++)
        cout<<seq[lis[i]]<<" ";

	return 0;
}
