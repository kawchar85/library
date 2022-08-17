//pick theorem: area=In+(on_boundary/2)-1
//in=strictly inside the polygon
T point(PT a, PT b){
    T x=abs(a.x-b.x);
    T y=abs(a.y-b.y);
    return __gcd(x,y)-1;
}
main(){
	ll on_boundary=n,area=0LL;
    for(i=0; i<n; i++){
        area+=cross(p[i],p[(i+1)%n]);
        on_boundary+=point(p[i],p[(i+1)%n]);
    }
}