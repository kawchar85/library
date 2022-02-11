/**
Problem: Given a string and a positive number K,find
the longest substring of given string containing K
distinct characters.If K is more than number of distinct
chars in the string, return the whole string.

*/

#include<bits/stdc++.h>
using namespace std;

#define CHAR_Range 128

string longestSubStr(string s, int k)
{
	int n=(int)s.size();
	int cnt[CHAR_Range]={0};
	int size=0,start=0,mx=INT_MIN;

	for(int L=0, R=0; R<n; R++)
	{
		cnt[s[R]]++;
		if(cnt[s[R]]==1) size++;

		//make stable
		while(size>k)
		{
			if(--cnt[s[L]]==0)
				size--;
			L++;
		}

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
	string s="abcbdbdbbdcdabd";
	int k=2;
	cout<<longestSubStr(s,k)<<endl;
}