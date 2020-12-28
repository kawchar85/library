#include<bits/stdc++.h>
#define sz 3000106
#define t_sz 26
using namespace std;

int counter=1,data[sz][t_sz];
bool ending[sz];
void ADD(char *s)
{
    int i,now,n=0;
    for(i=0; s[i]!='\0'; i++)
    {
        now=s[i]-'a';
        if(data[n][now]==0)
            data[n][now]=counter++;
        n=data[n][now];
    }
    ending[n]=1;
}

bool SEARCH(char *s)
{
    int i,now,n=0;
    for(i=0; s[i]!='\0'; i++)
    {
        now=s[i]-'a';
        if(data[n][now]==0)
            return 0;
        n=data[n][now];
    }
    return ending[n];
}

void delete_trie()
{
    counter=1;
    memset(data, 0, sizeof data);
}

int main()
{
    int n,i;
    char s[50];
    scanf("%d",&n);
    while(n--)
    {
        scanf("%s",s);
        ADD(s);
    }
    scanf("%d",&n);
    for(i=0; i<n; i++)
    {
        scanf("%s",s);
        if(SEARCH(s))
            puts("YES");
        else
            puts("NO");
    }
    delete_trie();
    return 0;
}
