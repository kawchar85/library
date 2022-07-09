#include<bits/stdc++.h>
#define ull __int128
//they are fast
#define getchar _getchar_nolock
#define putchar _putchar_nolock
ull read()
{
    ull x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(ull x) 
{
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
bool cmp(ull x, ull y)
{ 
	return x > y;
}
int main()
{
	ull a,b;
	a=read();
	b=read();
	print(a+b);

    return 0;
}
