{p^a} in prime factorization
nod=nod*(a+1)%MOD; 
sod=sod*(BigMod(p,a+1)-1+MOD)%MOD*inverse(p-1,MOD)%MOD;
pod=BigMod(pod,a+1)*BigMod(BigMod(p,(a*(a+1)/2)),tnod)%MOD;
tnod=tnod*(a+1)%(MOD-1);

//O(N^1/3),need prime till n^1/3
int CB(int x) {return x*x*x;}
int NOD(int n){
    int cnt=1;
    for(int i=0; CB(prime[i])<=n; i++){
        int c=1;
        while(n&prime[i]==0){
            c++; n/=prime[i];
        }
        cnt*=c;
    }
    if(isPrime[n]) cnt*=2;
    else if(isPrimeSq[n]) cnt*=3;
    else if(n!=1) cnt*=4;
    return cnt;
}
//O(sqrt(n)), NOD(1)+..+NOD(n)
ll CNOD(ll n) {
    ll i,cnt=0,sq=sqrt(n);
    for(i=1; i<=sq; i++)
        cnt+=(n/i)-i;
    cnt*=2; cnt+=sq;
    return cnt;
}
//O(sqrt(n))
ll CSOD(ll n){
    ll i,j,ans=0LL;
    for(i=1; i*i<=n; i++){
        j=n/i;
        ans+=(i+j)*(j-i+1)/2LL;
        ans+=i*(j-i);
    }
    return ans;
}
//O(NLogN)
void SOD(){
    for(i=1; i<MAX; i++)
        for(j=i; j<MAX; j+=i)
           sod[j]+=i;
}