/*
LOJ 1269
*/
#include<bits/stdc++.h>
using namespace std;
#define setbit(n) (n&-n)
#define bitOn(n,i) ((1<<i)|n)
#define bitOn2(n,i,j) ((((1<<(j-i+1))-1)<<i)|n)
#define bitOff(n,i) (~(1<<i)&n)
#define bitOff2(n,i,j) (~(((1<<(j-i+1))-1)<<i)&n)
#define bitToggle(n,i) ((1<<i)^n)
#define bitToggle2(n,i,j) ((((1<<(j-i+1))-1)<<i)^n)
#define bitOnAll(n) (n=-1)
#define bitOffAll(n) (n=0)
#define getbit(n,i) ((n>>i)&1)
#define MAX 10000

int counter=1;
struct node{
    int next[2];
    node(){
        next[0]=next[1]=0;
    }
}data[MAX];

void ADD(int n)
{
    int i,now,cur=0;
    for(i=31; ~i; i--)
    {
        now=getbit(n,i);
        if(data[cur].next[now]==0)
            data[cur].next[now]=counter++;
        cur=data[cur].next[now];
    }

}

int find_min(int n)
{
    int i,now,ans=0;
    int cur=0;//root

    for(i=31; i>=0; i--)
    {
        now=getbit(n,i);
        ans<<=1;
        if(data[cur].next[now]!=0)
        {
            cur=data[cur].next[now];
        }
        else
        {
            cur=data[cur].next[now^1];
            ans++;
        }
    }
    return ans;
}

int find_max(int n)
{
    int cur=0; //root;
    int i,now,ans=0;

    for(i=31; i>=0; i--)
    {
        now=getbit(n,i);
        ans<<=1;
        if(data[cur].next[now^1]!=0)
        {
            cur=data[cur].next[now^1];
            ans++;
        }
        else
        {
            cur=data[cur].next[now];
        }
    }
    return ans;
}

/*
void Delete(int n)
{
    int i,now;
    int cur=0;
    for(i=31; ~i; i--)
    {
        now=getbit(n,i);
        data[cur].cnt[now]--;
        if(data[cur].cnt[now]==0)
        {
            data[cur].next[now]=0;
            break;
        }
        cur=data[cur].next[now];
    }
}

*/

void delete_trie()
{
    counter=1;
    memset(data, 0, sizeof data);
}
int main()
{
    int t,cs,n,i,mx,mn,Xor,x;
    scanf("%d",&t);
    for(cs=1; cs<=t; cs++)
    {
        scanf("%d",&n);
        Xor=mx=0;
        mn=INT_MAX;
        ADD(Xor);//insert 0
        for(i=0; i<n; i++)
        {
            scanf("%d",&x);
            Xor^=x;
            mn=min(mn,find_min(Xor));
            mx=max(mx,find_max(Xor));
            ADD(Xor);
        }
        printf("Case %d: %d %d\n",cs,mx,mn);
        delete_trie();
    }
    return 0;
}

