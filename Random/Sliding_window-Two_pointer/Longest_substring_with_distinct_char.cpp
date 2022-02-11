/**
Problem: Given a string,find the longest substring
of given string containing distinct characters.
*/

#include<bits/stdc++.h>
using namespace std;

#define CHAR_Range 128

string longestSubStr(string s)
{
	int n=(int)s.size();
	bool vis[CHAR_Range]={0};
	int start=0,mx=INT_MIN;

	for(int L=0, R=0; R<n; R++)
	{
		if(vis[s[R]])
		{
			//make stable
			while(s[L]!=s[R])
				vis[s[L++]]=0;
			L++;
		}

		vis[s[R]]=1;

		//stable, so try to update ans
		if(mx<R-L+1)
		{
			mx=R-L+1;
			start=L;
		}
	}

	return s.substr(start, mx);
}

int main()
{
	//string s="ababca";
	string s="longestsubstr";
	cout<<longestSubStr(s)<<endl;
}