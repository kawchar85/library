void Compress(vector<ll> &v)
{
    int n=(int)v.size();
    ll temp[n];
    for(int i=0; i<n; i++)
        temp[i]=v[i];
    sort(temp,temp+n);
    int c=0;
    map<ll,int>mp;
    mp[temp[0]]=++c;
    for(int i=1; i<n; i++)
    {
        if(temp[i]!=temp[i-1])
            mp[temp[i]]=++c;
    }
    for(int i=0; i<n; i++)
        v[i]=mp[v[i]];
}