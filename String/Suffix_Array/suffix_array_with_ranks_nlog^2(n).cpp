///nLog^2(n)
#include<bits/stdc++.h>
using namespace std;
const int MAX =400004;
const int LG =18; //log2(n)+1

struct info{
    int tup[2], indx;
}arr[MAX];

int Rank[LG][MAX], LCP[MAX], step; /// step=log2(n)+1
string text;

bool cmp(const info &a, const info &b)
{
    return a.tup[0]!= b.tup[0]? a.tup[0]<b.tup[0] : a.tup[1]<b.tup[1];
}

void build_suffix_array()
{
    int n = text.size(), jump;
    for(int j = 0; j < n; j++)
    {
        Rank[0][j] = text[j]-'A'; ///rank suffixes according to 1st char
        memset(arr[j].tup, 0,sizeof(arr[j].tup));
    }
    for(step = 1, jump = 1; jump <= n; step++, jump <<= 1)
    {
        for(int j = 0; j <=n; j++)
        {
            arr[j].indx = j;
            arr[j].tup[0] = Rank[step - 1][j];
            arr[j].tup[1] = j + jump < n? Rank[step - 1][j + jump] : -1;
        }
        sort(arr, arr + n, cmp);
        Rank[step][arr[0].indx] = 0;
        for(int j = 1; j < n; j++)
            Rank[step][arr[j].indx] = arr[j].tup[0] == arr[j - 1].tup[0] &&
            arr[j].tup[1] == arr[j - 1].tup[1] ? Rank[step][arr[j - 1].indx] : j;
    }
    cout << "Suffix Array : \n\n";
    for(int i = 0; i < n; i++)
        cout<<arr[i].indx<<' '<<text.substr(arr[i].indx)<<endl;
}

void build_LCP_array()
{
    LCP[0] = 0;
    int n = text.size(), i, j, id1, id2;
    for(i = 1; i < n; i++)
    {
        id1 = arr[i - 1].indx;
        id2 = arr[i].indx;
        LCP[i] = 0;
        for(j = step - 1; j >= 0; j--)
            if(Rank[j][id1] == Rank[j][id2] && Rank[j][id2])
            {
                LCP[i] += (1 << j);
                id1 += (1 << j);
                id2 += (1 << j);
            }
        cout << arr[i - 1].indx << ' ' << arr[i].indx << ' ' << LCP[i] << endl;
    }
    for(i = 0; i < n; i++)
        cout << i << ' ' << LCP[i] << endl;
}
int lcp(int i, int j) {
    int ans = 0;
    for (int k = step-1; k >= 0; k--) {
        if (Rank[k][i] == Rank[k][j]) {
            ans += 1 << k;
            i += 1 << k;
            j += 1 << k;
        }
    }
    return ans;
}

void init(string &s){
    text = s+"$";
    build_suffix_array();
    build_LCP_array();
}
int main()
{
    string s;
    cin>>s;
    init(s);
    return 0;
}
