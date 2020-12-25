#include<bits/stdc++.h>
#define MAX 101
using namespace std;

vector<int>d;
int m[MAX][MAX],s[MAX][MAX];

int MCM(int n)
{
    int i,j,k,lvl,x;

    for(i=0; i<MAX; i++)
        m[i][i]=s[i][i]=0;

    for(lvl=1; lvl<n; lvl++)
    {
        for(i=1; i<=n-lvl; i++)
        {
            j=i+lvl;
            m[i][j]=INT_MAX;

            for(k=i; k<j; k++)
            {
                x=m[i][k]+m[k+1][j]+d[i-1]*d[k]*d[j];
                if(x<m[i][j])
                {
                    m[i][j]=x;
                    s[i][j]=k;
                }
            }
        }
    }

    return m[1][n];
}

void print(int i, int j)
{
    if(i==j)
    {
        cout<<"A"<<i;
        return;
    }
    cout<<"(";
    print(i,s[i][j]);
    print(s[i][j]+1,j);
    cout<<")";
}
int main()
{
    int n,i,x,cost;
    cin>>n;
    for(i=0; i<n; i++)
    {
        cin>>x;
        d.push_back(x);
    }
    cost=MCM(d.size()-1);
    cout<<"Min Cost = "<<cost<<endl;
    print(1, d.size()-1);
}

/**
7
30 20 15 5 10  5 10
*/
