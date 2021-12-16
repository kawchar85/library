#include<bits/stdc++.h>
using namespace std;
#define PI acos(-1.0)
#define EPS 1e-9

typedef long double T;
//typedef long long T;

int sign(T x) {return (x>EPS)-(x<-EPS);}
struct PT{
    T x,y;
    PT() {x=0, y=0; }
    PT(T x, T y): x(x),y(y) {}
    
    PT operator+(PT p) {return {x+p.x, y+p.y};}
    PT operator-(PT p) {return {x-p.x, y-p.y};}
    PT operator*(T d) {return {x*d, y*d};}
    PT operator/(T d) {return {x/d, y/d};}
    PT operator*(PT p) {return {x*p.x-y*p.y, x*p.y+y*p.x};}
    PT operator/(PT p) {return {((*this)*p.conj())/(p*p.conj()).x};} 
    bool operator == (PT p) const { return sign(p.x-x)==0 && sign(p.y-y)==0;}
    bool operator != (PT p) const { return !(*this == p);}
    bool operator < (PT p) const { return sign(p.x-x) == 0 ? (y<p.y) : (x<p.x);}
    bool operator > (PT p) const { return sign(p.x-x) == 0 ? y>p.y : x>p.x;}

    T sq() {return x*x + y*y;}
    T abs() {return sqrt(sq());}
    PT unit() {return (*this)/abs();}
    PT conj() {return {x,-y};}
    PT perp() {return {-y,x};}
    T angle() {return atan2(y,x);}
    PT truncate(T r) { // returns a vector with norm r and having same direction
        T k = abs();
        if (!sign(k)) return *this;
        r /= k;
        return PT(x*r, y*r);
    }
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
    T slop(){ return -1.0*(a/b); }
    T val(PT p){ return a*p.x+b*p.y-c; }
    int side(PT p){ return sign(val(p)); }
};

ostream& operator<<(ostream& os, PT p) {
    return os << "("<< p.x << "," << p.y << ")";
}
ostream& operator<<(ostream& os, EQN E) {
    return os << "("<<E.a << "," << E.b <<","<<E.c<<")";
}


int quad(PT p)
{
  if(p.x< 0 && p.y < 0) return 0;
  if (p.x >= 0 && p.y < 0) return 1;
  if (p.x >= 0 && p.y >= 0) return 2;
  if (p.x < 0 && p.y >= 0) return 3;
}

bool polar_sort(PT a, PT b){ //compare by angle
  return quad(a) == quad(b) ? a.x * b.y > a.y * b.x : quad(a) < quad(b);
};

T dot(PT a, PT b){ return a.x*b.x+a.y*b.y; }
T cross(PT a, PT b){ return (a.x*b.y-a.y*b.x); }
T dis(PT a, PT b){ return (b-a).abs(); }
T dis2(PT a, PT b){ return dot(b-a, b-a); }
T dis(EQN I, PT p){ return fabs(I.val(p)/PT(I.a,I.b).abs()); }
//distance from p to line (a,b)
long double dis(PT p, PT a, PT b){ return fabs(cross(b-a, p-a)/(b-a).abs()); }
//between vector A,B
T angle(PT a, PT b){ T cosTheta=dot(a,b)/a.abs()/b.abs();
    return acos(max((T)-1.0,min((T)1.0,cosTheta))); }
//betwen point B,A,C
T angle(PT b, PT a, PT c){ return angle(b-a, c-a); }
//p lies in above/down of [AB]?
// bisector vector of <abc
PT angle_bisector(PT &a, PT &b, PT &c){
    PT p = a - b, q = c - b;
    return p + q * sqrt(dot(p, p) / dot(q, q));
}
bool inSegArea(PT a, PT p, PT b){ return angle(p,a,b)<=(PI/2.0) && angle(p,b,a)<=(PI/2.0); }
T toRadian(T x){ return PI*x/180.0; }
T toDegree(T x){ return 180.0/PI*x; }
PT mid(PT a, PT b){ return {(a.x+b.x)/2, (a.y+b.y)/2}; }
//get point from polar co-ordi
PT pol(T r, T radian){ return {(T)(r*cos(radian)),(T)(r*sin(radian))}; }
//AB line borabor d durotte bindhu
PT ab_to_d(PT a,PT b, T d){ return a+(b-a).unit()*d; }
//Line I er A point teke d dist a point
PT walk(EQN I, PT A, T d){ return ab_to_d(A,PT(I.b,-I.a),-d); }
//Projection of a onto b
T proj(PT a, PT b){ return dot(a,b)/b.abs(); }
//P teke line l er upor projection
PT proj(EQN l, PT p){ PT temp={l.a,l.b}; return p-temp*l.val(p)/temp.sq(); }
PT refl(EQN l, PT p){ PT temp={l.a,l.b}; return p-temp*2.0*l.val(p)/temp.sq(); }
//translate p by a vector V
PT translate(PT v, PT p){ return p+v; }
PT scale(PT c, T factor, PT p){ return c+(p-c)*factor; }
PT rotate(PT A, T radian){ return A*pol(1.0, radian); }
//O er sapekke A ke radian kune CCW
PT rotate(PT O, PT A, T radian){ return O+(A-O)*pol(1.0, radian); }
PT CCW90(PT p){ return {-p.y,p.x}; }
PT CW90(PT p){ return {p.y,-p.x}; }
PT CCW90(PT o,PT p){ p=p-o; return o+PT(-p.y,p.x); }
PT CW90(PT o,PT p){ p=p-o; return o+PT(p.y,-p.x); }
//co-linear-->0,CCW-->1,CW-->-1
int orientation(PT A, PT B, PT C) { return sign( cross(B-A, C-B) ); }

//P lies in the angle formed by lines AB and AC ?
bool inAngle(PT a, PT b, PT c, PT p) {
    assert(orientation(a,b,c) != 0);
    if(orientation(a,b,c)<0) swap(b,c);
    return orientation(a,b,p) >= 0 && orientation(a,c,p) <= 0;
}
//P lies on the disk of diameter [AB]?
bool inDisk(PT a, PT p,PT b){ return dot(a-p, b-p)<=0.0; }
//p on segment [AB]?
bool onSegment(PT a, PT p, PT b){ return orientation(a,p,b)==0 && inDisk(a,p,b); }
//q on segment pr ??
bool onSegment2(PT p,PT q,PT  r){ return (q.x<=max(p.x,r.x) && q.x>=min(p.x,r.x) && q.y<=max(p.y,r.y) && q.y>=min(p.y,r.y)); }

// 0 if not parallel, 1 if parallel, 2 if collinear
int is_parallel(PT a, PT b, PT c, PT d){
    int k = sign((cross(b - a, d - c)));
    if (!k){
        if (!sign(cross(a - b, a - c)) && !sign(cross(c - d, c - a)) ) return 2;
        else return 1;
    }
    else return 0;
}
bool is_parallel(EQN one, EQN two){ return !sign(one.a*two.b)-(two.a*one.b); }
long double diameter_rotating_calipers(vector<PT> &p){ //points of convex hull
    long double mn=1e100;
    int n=p.size();

    for(int i=0,k=1; i<n; i++)
    {
        int j=(i+1)%n;
        while(fabs(cross(p[j]-p[i] , p[(k+1)%n]-p[i]))>fabs(cross(p[j]-p[i] , p[k]-p[i])))
            k=(k+1)%n;
        mn=min(mn, dis(p[k], p[i],p[j]));
    }
    return mn;
}

EQN paraEqn(EQN I, PT p){
    T x=I.a*p.x+I.b*p.y;
    I.c=x; return I; }
EQN perpEqn(EQN I, PT p){
    swap(I.a,I.b);
    if(I.a<0) I.a*=-1.0;
    else I.b*=-1.0;
    I.c=I.a*p.x+I.b*p.y;
    return I; }

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
T areaPolygon(vector<PT> &p){
    T area = 0.0;
    for(int i=0, n=p.size(); i<n; i++)
        area += cross(p[i], p[(i+1)%n]);
    return fabs(area)/2.0;
}
//for convex poly
bool pointInPolygon(vector<PT> &p, PT k)
{
    //Edge er upor hole 0 return korbe.
    // if need a<0||b<0, c>=0
    int n=(int)p.size();
    int l=1, r=n-1,mid;
    int a=orientation(p[1],p[0],k);
    int b=orientation(p[0], p[n-1], k);

    if(a<=0 || b<=0)
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
    return c>0;
}
//O(n)
int pointInSimplePolygon(vector<PT> &p, PT k)
{
    int n=(int)p.size();
    int cnt=0,i,j;
    bool boundary=0;

    for(i=0; i<n; i++)
    {
        j=(i+1)%n;
        if(onSegment(p[i], k, p[j]))
            boundary=1;
        if(p[i].x<=k.x && k.x<p[j].x && orientation(k,p[i],p[j])==1)
            cnt++;
        else if(p[j].x<=k.x && k.x<p[i].x && orientation(k,p[j],p[i])==1)
            cnt++;
    }

    if(boundary) return 0;
    if(cnt&1) return -1;//inside
    else return 1;//outside
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
bool circleIntersect(PT a,T r0,PT b,T r1, set<PT> &v)
{
    T d,d2,x,y,angle;
    PT one,two,k,temp;
    d=dis(a,b);
    d2=(a-b).sq();
    if(d>r0+r1 || d<abs(r0-r1))
    {
        cout<<"NO INTERSECTION\n";
        return 0;
    }
    if(fabs(r0)<EPS && fabs(r1)<EPS && fabs((a-b).abs())<EPS)
    {
        v.insert(a);//point circle
        return 1;
    }
    if(fabs(r0-r1)<EPS && fabs((a-b).abs())<EPS)
    {
        cout<<"THE CIRCLES ARE THE SAME\n";
        return 0;
    }
    
    x=r1*r1-r0*r0-b.y*b.y-b.x*b.x;
    EQN I=EQN(-2.0*b.x, -2.0*b.y, x);
    vector<PT> v2;
    circleLine(a,r0,I, v2);
    for(auto p : v2)
        v.insert(p);
    return 1;
}

/*
T Value(PT p){
    T base=2500005003LL;
    return p.x*base+p.y;
}
T slope(PT p){
    if(p.x==0)
        p=PT(0,1);
    else if(p.y==0)
        p=PT(1,0);
    else
    {
        if(p.x<0)
        {
            p.x*=-1;
            p.y*=-1;
        }
        T g=__gcd(abs(p.x), abs(p.y));
        p.x/=g;
        p.y/=g;
    }
    return Value(p);
}
T perp_slop(PT p){
    return slope(p.perp());
}
*/

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("angle1.in","r", stdin);
    //freopen("angle1.out","w", stdout);
    

}
