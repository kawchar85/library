#include<bits/stdc++.h>
#define MAX 10001
#define pii pair< int, int >
using namespace std;
int x4[]={+1,-1,+0,+0}; int y4[]={+0,+0,+1,-1};
///int x8[]={+0,+0,+1,-1,-1,+1,-1,+1}; int y8[]={-1,+1,+0,+0,+1,+1,-1,-1};
///int xk[]={1,1,2,2,-1,-1,-2,-2}; int yk[]={2,-2,1,-1,2,-2,1,-1};
#define valid(nx,ny) nx>=1 && nx<=row && ny>=1 && ny<=col

char grid[MAX][MAX];
int row,col;

///O(V+E)
void BFS(int x, int y)
{
    queue< pii > q;
    q.push({x,y});
    while(!q.empty())
    {
        x=q.front().first;
        y=q.front().second;
        q.pop();
        for(int i=0; i<4; i++)
        {
            int u=x+x4[i];
            int v=y+y4[i];
            if(valid(u,v))
            {
                q.push({u,v});
            }
        }
    }
}

int main()
{


    return 0;
}
