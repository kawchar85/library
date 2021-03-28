#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#define INF 1<<27
using namespace std;

int n,p[222][222];
void init()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			p[i][j]=(i==j?0:INF);
		}
	}
}

void warshall()
{
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				p[i][j]=min(p[i][j],(p[i][k]+p[k][j]));
			}
		}
	}
}
void Neg_warshall()
{
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
                if(p[i][k]<INF && p[k][k]<0 && p[k][j]<INF)
                p[i][j] = - INF; ///i to j no path
			}
		}
	}
}

int main()
{
	int cas;
	return 0;
 }
