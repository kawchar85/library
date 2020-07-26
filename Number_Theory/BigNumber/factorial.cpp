#include<stdio.h>
int main()
{
    int fact[100000],n,i,j,k,total,carry,digit;
    while(scanf("%d",&n)!=EOF)
    {
        carry=0;
        fact[0]=1;
        total=1;
        for(i=2;i<=n;i++)
        {
            for(j=0;j<total;j++)
            {
                k=fact[j]*i+carry;
                fact[j]=k%10;
                carry=k/10;
            }
            while(carry>0)
            {
                fact[total]=carry%10;
                carry/=10;
                total++;
            }
        }
        printf("%d!=\n",n);
        for(j=total-1;j>=0;j--)
        printf("%d",fact[j]);
        printf("\n");
    }
    return 0;
}
