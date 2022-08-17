//Characteristics of phi:
phi=n*MULof(1-1/p)
init by i, phi[j]=phi[j]/i*(i-1);

gcd(i,N)=g --> phi(N/g);
gcd(x,y)=g, 1<=x,y<=N --> sumPhi(N/g);
phi(lcm(a,b))*phi(gcd(a,b))=phi(a)*phi(b)
sum of co-prime → phi(n)*n/2;
sum of gcd(i,N), for i= 1 to N --> sum of (d*phi(n/d)) for all d|N;
sum of LCM(i,N) for i=1 to N --> (N/2) *( x +1) where x=sum of (d* phi(d) ) for all d|N;
sum of gcd(k-1,N), for k=1 to N and gcd(k,N)=1 --> phi(N)*NOD(N) 

//Preity
generalization of Euler’s theorem:
x^n = x^( phi(m)+n mod phi(m)) mod m
LCM sum: 2(SUM-n)=n*(sum of d*phi(d),s.t d|n and d is npt 1)