#include<bits/stdc++.h>
using namespace std;

#define N 999
int n, a[N], B[N], len[N];
///For Longest decreasing subsequenc, reverse the input array!! then find LIS

int find_lis()
{
    int ans=0;
    for(int i=1; i<=n; i++)
    {
        len[i]=lower_bound(B+1, B+ans+1, a[i])-B;  ///Incresing...
        //len[i]=upper_bound(B+1, B+ans+1, a[i])-B; ///Non-decresing...
        ans=max(ans, len[i]);
        B[len[i]]=a[i];
    }
    return ans;
}
void print_lis(int ans)
{
    vector<int> seq;
    for(int i=n; i>=1; i--)
    {
        if(len[i]==ans)
        {
            seq.push_back(a[i]);
            ans--;
        }
    }
    int i=(int)seq.size();
    while(i--)
        cout<<seq[i]<<" \n"[!i];
}
void init()
{
    memset(B,-1,sizeof B);
    memset(len,0,sizeof len);
}
void test() 
{
    cout<<"------------\n";
    for(int i=1; i<=n; i++) cout<<a[i]<<" ";cout<<endl;
    for(int i=1; i<=n; i++) cout<<B[i]<<" ";cout<<endl;
    for(int i=1; i<=n; i++) cout<<len[i]<<" ";cout<<endl;
    cout<<"------------\n";
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        init();
        cin>>n;
        for(int i=1; i<=n; i++) cin>>a[i];
        int answer = find_lis();
        printf("LIS lenght: %d\n", answer);
        print_lis(answer);
        test();
    }
    return 0;
}
