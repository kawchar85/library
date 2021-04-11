/**
    A convex lattice polygon with coordinates in [0, N] has at most O(N2 / 3) vertices
    https://algo.codemarshal.org/contests/icpc-dhaka-20-preli/problems/A
*/

#include<bits/stdc++.h>
using namespace std;
#define PI acos(-1.0)
#define EPS 1e-9
#define ll long long 

typedef long double T;
//typedef long long T;

struct PT{
    T x,y;
    PT() {}
    PT(T x, T y): x(x),y(y) {}
    
    PT operator+(PT p) {return {x+p.x, y+p.y};}
    PT operator-(PT p) {return {x-p.x, y-p.y};}
    PT operator*(T d) {return {x*d, y*d};}
    PT operator/(T d) {return {x/d, y/d};}
    PT operator*(PT p) {return {x*p.x-y*p.y, x*p.y+y*p.x};}
    PT operator/(PT p) {return {((*this)*p.conj())/(p*p.conj()).x};} 

    T sq() {return x*x + y*y;}
    T abs() {return sqrt(sq());}
    PT unit() {return (*this)/abs();}
    PT conj() {return {x,-y};}
    PT perp() {return {-y,x};}
    T angle() {return atan2(y,x);}
};

struct EQN{
    //ax+by=c
    //direction: PT(b,-a)
    //position: c
    T a,b,c;
    EQN() {}
    EQN(T a, T b, T c): a(a),b(b),c(c) {}
    EQN(PT A, PT B){
        a=B.y-A.y;
        b=A.x-B.x;
        c=a*A.x+b*A.y;
    }
    EQN(PT p, T slp){
        a=slp;
        b=-1;
        c=slp*p.x-p.y;
    }
    T slop(){
        return -1.0*(a/b);
    }
    T val(PT p){
        return a*p.x+b*p.y-c;
    }
};

ostream& operator<<(ostream& os, PT p) {
    return os << "("<< p.x << "," << p.y << ")";
}
ostream& operator<<(ostream& os, EQN E) {
    return os << "("<<E.a << "," << E.b <<","<<E.c<<")";
}

bool operator<(PT p1, PT p2){
    if(fabs(p1.x-p2.x)<EPS)
        return p1.y<p2.y;
    return p1.x<p2.x;
} 
int sgn(T x){
    if(abs(x)<EPS) return 0;
    if(x<0) return -1; return 1;
}

T dis(PT a, PT b){
    return (b-a).abs();
}
//perpendicular distance
T dis(EQN I, PT p){
    return fabs(I.val(p)/PT(I.a,I.b).abs());
}
T dot(PT a, PT b){
    return a.x*b.x+a.y*b.y;
}
T cross(PT a, PT b){
    return (a.x*b.y-a.y*b.x);
}
bool eql(PT a, PT b){
    return fabs(a.x-b.x)<EPS && fabs(a.y-b.y)<EPS;
}
EQN paraEqn(EQN I, PT p){
    T x=I.a*p.x+I.b*p.y;
    I.c=x;
    return I;
}
EQN perpEqn(EQN I, PT p){
    swap(I.a,I.b);
    if(I.a<0) I.a*=-1.0;
    else I.b*=-1.0;
    I.c=I.a*p.x+I.b*p.y;
    return I;
}

//between vector A,B
T angle(PT a, PT b){
    T cosTheta=dot(a,b)/a.abs()/b.abs();
    return acos(max((T)-1.0,min((T)1.0,cosTheta)));
}
//betwen point B,A,C
T angle(PT b, PT a, PT c){
    return angle(b-a, c-a);
}
T toRadian(T x){
    return PI*x/180.0;
}
T toDegree(T x){
    return 180.0/PI*x;
}
PT mid(PT a, PT b){
    return {(a.x+b.x)/2, (a.y+b.y)/2};
}

//get point from polar co-ordi
PT pol(T r, T radian){ 
    return {(T)(r*cos(radian)),(T)(r*sin(radian))};
}
//AB line borabor d durotte bindhu
PT ab_to_d(PT a,PT b, T d){
    return a+(b-a).unit()*d;
}
//Line I er A point teke d dist a point
PT walk(EQN I, PT A, T d){
    return ab_to_d(A,PT(I.b,-I.a),-d);
}
//duita equation solve/ Ax+By=C
PT solve_eqn(EQN one, EQN two)
{
    PT ans;
    T d=(one.a*two.b)-(two.a*one.b);
    if(fabs(d)<EPS){
        cout<<"Parallel!!!"<<endl;
        return {0,0};
    }
    ans.x=(two.b*one.c-one.b*two.c)/d;
    ans.y=(one.a*two.c-two.a*one.c)/d;
    return ans;
}
//Projection of a onto b
T proj(PT a, PT b){
    return dot(a,b)/b.abs();
}
//P teke line l er upor projection
PT proj(EQN l, PT p){
    PT temp={l.a,l.b};
    return p-temp*l.val(p)/temp.sq();
}
PT refl(EQN l, PT p){
    PT temp={l.a,l.b};
    return p-temp*2.0*l.val(p)/temp.sq();
}
//translate p by a vector V
PT translate(PT v, PT p){
    return p+v;
}
PT scale(PT c, T factor, PT p){
    return c+(p-c)*factor;
}
PT rotate(PT A, T radian){
    return A*pol(1.0, radian);
}
//O er sapekke A ke radian kune CCW
PT rotate(PT O, PT A, T radian){
    return O+(A-O)*pol(1.0, radian);
}
PT CCW90(PT p){
    return {-p.y,p.x};
}
PT CW90(PT p){
    return {p.y,-p.x};
}
PT CCW90(PT o,PT p){
    p=p-o;
    return o+PT(-p.y,p.x);
}
PT CW90(PT o,PT p){
    p=p-o;
    return o+PT(p.y,-p.x);
}
//co-linear-->0
//CCW-->1
//CW-->-1
int orientation(PT A, PT B, PT C) {
    T x=cross(B-A, C-B); //ABxBC
    if(fabs(x)<EPS)
        return 0;
    if(x>0)
        return 1;
    return -1;
}

//P lies in the angle formed by lines AB and AC ?
bool inAngle(PT a, PT b, PT c, PT p) {
    assert(orientation(a,b,c) != 0);
    if(orientation(a,b,c)<0) swap(b,c);
    return orientation(a,b,p) >= 0 && orientation(a,c,p) <= 0;
}
//P lies on the disk of diameter [AB]?
bool inDisk(PT a, PT p,PT b){
    return dot(a-p, b-p)<=0.0;
}
//p on segment [AB]?
bool onSegment(PT a, PT p, PT b){
    return orientation(a,p,b)==0 && inDisk(a,p,b);
}
//q on segment pr ??
bool onSegment2(PT p,PT q,PT  r)
{
    if(q.x<=max(p.x,r.x) && q.x>=min(p.x,r.x) && q.y<=max(p.y,r.y) && q.y>=min(p.y,r.y))
       return 1;
    return 0;
}
//line segment 'p1q1' and 'p2q2' intersect.
bool segmentIntersect(PT p1,PT q1,PT p2,PT q2)
{
    int o1 = orientation(p1,q1,p2);
    int o2 = orientation(p1,q1,q2);
    int o3 = orientation(p2,q2,p1);
    int o4 = orientation(p2,q2,q1);

    if(o1!=o2 && o3!=o4)
        return 1; //direct
    //touching?
    if(o1==0 && onSegment(p1,p2,q1))
        return 1;
    if(o2==0 && onSegment(p1,q2,q1))
        return 1;
    if(o3==0 && onSegment(p2,p1,q2))
        return 1;
    if(o4==0 && onSegment(p2,q1,q2))
        return 1;

    return 0;
}

T betweenAngle(EQN I, EQN II){
    T m1 = I.slop();
    T m2 = II.slop();
    T x = fabs((m1 - m2)/(1.0 + m1*m2));
    return atan(x); //or atan(-x)
}

//p in above/down of [AB]?
bool inSegArea(PT a, PT p, PT b){
    return angle(p,a,b)<=(PI/2.0) && angle(p,b,a)<=(PI/2.0);
}
//min dis of [AB] from p
T segPoint(PT a, PT b, PT p){
    T ans=min((p-a).abs(), (p-b).abs());
    if(inSegArea(a,p,b))
        ans=min(ans,dis(EQN(a,b),p));
    return ans;
}
//min dis of[AB) from p
T rayPoint(PT a, PT b, PT p){
    b=ab_to_d(a,b,dis(a,p));
    return segPoint(a,b,p);
}
//min dis [AB] [CD]
T segSeg(PT a, PT b, PT c, PT d){
    if(segmentIntersect(a,b,c,d))
        return 0.0;
    return min({segPoint(a,b,c), segPoint(a,b,d), segPoint(c,d,a), segPoint(c,d,b)});
}
ll areaPolygon(vector<PT> &p){
    if((int)p.size()<3) return 0LL;
    ll area = 0;
    for(int i=0, n=p.size(); i<n; i++)
        area += cross(p[i], p[(i+1)%n]);
    return abs(area);
}
//for convex poly
bool pointInPolygon(vector<PT> &p, PT k)
{
    //Edge er upor hole 0 return korbe.
    // if need a<0||b<0, c>=0
    int n=(int)p.size();
    if(n<3) return 0;
    int l=1, r=n-1,mid;
    int a=orientation(p[1],p[0],k);
    int b=orientation(p[0], p[n-1], k);

    if(a<0 || b<0)
        return 0;

    while(r-l>1)
    {
        mid=(l+r)/2;
        if(orientation(p[mid], p[0], k)>0)
            l=mid;
        else
            r=mid;
    }
    int c=orientation(p[r],p[l],k);
    return c>=0;
}
bool polyInPoly(vector<PT> &p, vector<PT> &q)
{
    bool ok=1;
    for(auto now : q)
    {
        if(!pointInPolygon(p, now))
        {
            ok=0;
            break;
        }
    }
    return ok;
}
bool isConvex(vector<PT> &p) {
    bool hasPos=false, hasNeg=false;
    for(int i=0, n=p.size(); i<n; i++){
        int o=orientation(p[i], p[(i+1)%n], p[(i+2)%n]);
        if(o>0) hasPos=true;
        if(o<0) hasNeg=true;
    }
    return !(hasPos && hasNeg);
}

bool cw(PT a, PT b, PT c){
    return orientation(a,b,c)==-1;
}
bool ccw(PT a, PT b, PT c){
    return orientation(a,b,c)==1;
}
void convex_hull(vector<PT> &v){
    int n=v.size();
    if(n<3) return;

    sort(v.begin(), v.end());
    PT p1=v[0], p2=v.back();
    vector<PT> up,down;
    up.push_back(p1);
    down.push_back(p1);

    for(int i=1; i<n; i++)
    {
        if(i+1==n || cw(p1, v[i], p2))
        {
            while(up.size()>1 && !cw(up[up.size()-2], up[up.size()-1], v[i]))
                up.pop_back();
            up.push_back(v[i]);
        }

        if(i+1==n || ccw(p1, v[i], p2))
        {
            while(down.size()>1 && !ccw(down[down.size()-2], down[down.size()-1], v[i]))
                down.pop_back();
            down.push_back(v[i]);
        }
    }

    v.clear();
    for(int i=0; i<(int)up.size(); i++)
        v.push_back(up[i]);
    for(int i=down.size()-2; i>0; i--)
        v.push_back(down[i]);
}

bool circleLine(PT o, T r, EQN I,vector<PT> &v){
    T d=dis(I,o);
    if(d>r) return 0;
    T x=sqrt(r*r-d*d);
    PT p=proj(I,o);
    v.push_back(walk(I,p,x));
    v.push_back(walk(I,p,-x));
}

long long int seed1, seed2;
int get_random() {
    seed1 = (seed1 * 1103515243LL + 12345)%(2012345671);
    seed2 = (seed2 * 1092104927LL + 54321)%(2094828103);
    int r = (seed1 * seed2) % 100000;
    return r;
}
int main(){

    int t, cs, i, n;
    scanf("%d",&t);
    for(cs = 1; cs<=t; cs++){
        printf("Case %d: ", cs);

        scanf("%d %lld %lld",&n,&seed1,&seed2);
        vector< PT > v;
        PT p;
        ll sum=0LL;
        ll last=0LL;
        for(i = 1; i<=n; i++){
            p.x = get_random();
            p.y = get_random();
            
            if(!pointInPolygon(v, p))
            {
                v.push_back(p);
                convex_hull(v);
                last=areaPolygon(v);
            }
            sum+=last;
        }
        printf("%lld\n", sum);
    }
    return 0;
}
