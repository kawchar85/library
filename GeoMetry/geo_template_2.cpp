//Origin: https://github.com/ShahjalalShohag/code-library/blob/master/Geometry/Geometry%202D.cpp
 
#include<bits/stdc++.h>
using namespace std;

typedef long double ld;
//typedef long long T;
typedef long double T;
 
#define PI acos(-1.0)
#define eps 1e-9
#define inf (1e100)
int sign(T x) {return (x>eps)-(x<-eps);}
 
struct PT {
    T x, y;
    PT() { x = 0, y = 0; }
    PT(T x, T y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    PT operator * (const T a) const { return PT(x * a, y * a); }
    friend PT operator * (const T &a, const PT &b) { return PT(a * b.x, a * b.y); }
    PT operator / (const T a) const { return PT(x / a, y / a); }
    PT operator*(PT p) {return {x*p.x-y*p.y, x*p.y+y*p.x};}
    PT operator/(PT p) {return {((*this)*p.conj())/(p*p.conj()).x};}
    bool operator == (PT a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
    bool operator != (PT a) const { return !(*this == a); }
    bool operator < (PT a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator > (PT a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
    ld norm() { return sqrt(x * x + y * y); }
    T norm2() { return x * x + y * y; } //squared dis
    PT perp() { return PT(-y, x); }
    PT unit() {return (*this)/norm();}
    PT conj() {return {x,-y};}
    ld arg() { return atan2(y, x); }
    PT truncate(T r) { // returns a vector with norm r and having same direction
        ld k = norm();
        if (!sign(k)) return *this;
        r /= k;
        return PT(x * r, y * r);
    }
};
T dot(PT a, PT b) { return a.x * b.x + a.y * b.y; }
T dist2(PT a, PT b) { return dot(a - b, a - b); }
ld dist(PT a, PT b) { return sqrt(dot(a - b, a - b)); }
T cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
T cross2(PT a, PT b, PT c) { return cross(b - a, c - a); }
int orientation(PT a, PT b, PT c) { return sign(cross(b - a, c - a)); }
PT perp(PT a) { return PT(-a.y, a.x); }
PT rotate_ccw90(PT a) { return PT(-a.y, a.x); }
PT rotate_cw90(PT a) { return PT(a.y, -a.x); }
PT rotate_ccw(PT a, T t) { return PT(a.x * cos(t) - a.y * sin(t), a.x * sin(t) + a.y * cos(t)); }
PT rotate_cw(PT a, T t) { return PT(a.x * cos(t) + a.y * sin(t), -a.x * sin(t) + a.y * cos(t)); }
//O er sapekke A ke radian kune CCW
PT rotate(PT O, PT A, T radian){ return O + rotate_ccw(A - O, radian); }
T SQ(T x) { return x * x; }
ld rad_to_deg(T r) { return (r * 180.0 / PI); }
ld deg_to_rad(T d) { return (d * PI / 180.0); }
T get_angle(PT a, PT b) {
    T costheta = dot(a, b) / a.norm() / b.norm();
    return acos(max((T)-1.0, min((T)1.0, costheta)));
}
// does point p lie in angle <bac
bool is_point_in_angle(PT b, PT a, PT c, PT p) {
    assert(orientation(a, b, c) != 0);
    if (orientation(a, c, b) < 0) swap(b, c);
    return orientation(a, c, p) >= 0 && orientation(a, b, p) <= 0;
}
bool half(PT p) {
    return p.y > 0.0 || (p.y == 0.0 && p.x < 0.0);
}
// sort points in counterclockwise
void polar_sort(vector<PT> &v) {
    sort(v.begin(), v.end(), [](PT a,PT b) {
        return make_tuple(half(a), (T)0.0, a.norm2()) < make_tuple(half(b), cross(a, b), b.norm2());
    });
}
 
struct line {
    PT a, b;// goes through points a and b
    PT v; T c;//line form: direction vec [cross] (x, y) = c 
    line() {}
    //direction vector v and offset c
    line(PT v, T c) : v(v), c(c) {
        auto p = get_points();
        a = p.first; b = p.second;
    }
    // equation ax + by + c = 0
    line(T _a, T _b, T _c) : v({_b, -_a}), c(-_c) {
        auto p = get_points();
        a = p.first; b = p.second;
    }
    // goes through points p and q
    line(PT p, PT q) : v(q - p), c(cross(v, p)), a(p), b(q) {}
        pair<PT, PT> get_points() { //extract any two points from this line
        PT p, q; T a = -v.y, b = v.x; // ax + by = c
        if (sign(a) == 0) {
            p = PT(0, c / b);
            q = PT(1, c / b);
        }
        else if (sign(b) == 0) {
            p = PT(c / a, 0);
            q = PT(c / a, 1);
        }
        else {
            p = PT(0, c / b);
            q = PT(1, (c - a) / b);
        }
        return {p, q};
        }
    //ax + by + c = 0
    array<T, 3> get_abc() {
        T a = -v.y, b = v.x;
        return {a, b, c};
    }
    //1 if on the left, -1 if on the right, 0 if on the line
    int side(PT p) { return sign(cross(v, p) - c); }
    //line that is perpendicular to this and goes through point p
    line perpendicular_through(PT p) { return {p, p + perp(v)}; }
    //translate the line by vector t i.e. shifting it by vector t
    line translate(PT t) { return {v, c + cross(v, t)}; }
    //compare two points by their orthogonal projection on this line
    //a projection point comes before another if it comes first according to vector v
    bool cmp_by_projection(PT p, PT q) { return dot(v, p) < dot(v, q); }
    line shift_left(T d) {
        PT z = v.perp().truncate(d);
        return line(a + z, b + z);
    }
};
//find a point from A through B with distance d
PT point_along_line(PT a, PT b, T d) {
    return a + (((b - a) / (b - a).norm()) * d);
}
//projection point c onto line through a and b  assuming a != b
PT project_from_point_to_line(PT a, PT b, PT c) {
    return a + (b - a) * dot(c - a, b - a) / (b - a).norm2();
}
//reflection point c onto line through a and b  assuming a != b
PT reflection_from_point_to_line(PT a, PT b, PT c) {
    PT p = project_from_point_to_line(a,b,c);
    return point_along_line(c, p, (T)2 * dist(c, p));
}
//minimum distance from point c to line through a and b
ld dist_from_point_to_line(PT a, PT b, PT c) {
    return fabs(cross(b - a, c - a) / (b - a).norm());
}
//returns true if  point p is on line segment ab
bool is_point_on_seg(PT a, PT b, PT p) {
    if (abs(cross(p - b, a - b)) < eps) {
        if (p.x < min(a.x, b.x) || p.x > max(a.x, b.x)) return false;
        if (p.y < min(a.y, b.y) || p.y > max(a.y, b.y)) return false;
        return true;
    }
    return false;
}
//minimum distance point from point c to segment ab that lies on segment ab
PT project_from_point_to_seg(PT a, PT b, PT c) {
    T r = dist2(a, b);
    if (abs(r) < eps) return a;
    r = dot(c - a, b - a) / r;
    if (r < 0) return a;
    if (r > 1) return b;
    return a + (b - a) * r;
}
//minimum distance from point c to segment ab
ld dist_from_point_to_seg(PT a, PT b, PT c) {
    return dist(c, project_from_point_to_seg(a, b, c));
}
//0 if not parallel, 1 if parallel, 2 if collinear
int is_parallel(PT a, PT b, PT c, PT d) {
    T k = abs(cross(b - a, d - c));
    if (k < eps){
        if (abs(cross(a - b, a - c)) < eps && abs(cross(c - d, c - a)) < eps) return 2;
        else return 1;
    }
    else return 0;
}
//check if two lines are same
bool are_lines_same(PT a, PT b, PT c, PT d) {
    if (abs(cross(a - c, c - d)) < eps && abs(cross(b - c, c - d)) < eps) return true;
    return false;
}
//bisector vector of <abc
PT angle_bisector(PT &a, PT &b, PT &c){
    PT p = a - b, q = c - b;
    return p + q * sqrt(dot(p, p) / dot(q, q));
}
//1 if point is ccw to the line, 2 if point is cw to the line, 3 if point is on the line
int point_line_relation(PT a, PT b, PT p) {
    int c = sign(cross(p - a, b - a));
    if (c < 0) return 1;
    if (c > 0) return 2;
    return 3;
}
//intersection point between ab and cd assuming unique intersection exists
bool line_line_intersection(PT a, PT b, PT c, PT d, PT &ans) {
    T a1 = a.y - b.y, b1 = b.x - a.x, c1 = cross(a, b);
    T a2 = c.y - d.y, b2 = d.x - c.x, c2 = cross(c, d);
    T det = a1 * b2 - a2 * b1;
    if (det == 0) return 0;
    ans = PT((b1 * c2 - b2 * c1) / det, (c1 * a2 - a1 * c2) / det);
    return 1;
}
//intersection point between segment ab and segment cd assuming unique intersection exists
bool seg_seg_intersection(PT a, PT b, PT c, PT d, PT &ans) {
    T oa = cross2(c, d, a), ob = cross2(c, d, b);
    T oc = cross2(a, b, c), od = cross2(a, b, d);
    if (oa * ob < 0 && oc * od < 0){
        ans = (a * ob - b * oa) / (ob - oa);
        return 1;
    }
    else return 0;
}
//intersection point between segment ab and segment cd assuming unique intersection may not exists
//se.size()==0 means no intersection
//se.size()==1 means one intersection
//se.size()==2 means range intersection
set<PT> seg_seg_intersection_inside(PT a,  PT b,  PT c,  PT d) {
    PT ans;
    if (seg_seg_intersection(a, b, c, d, ans)) return {ans};
    set<PT> se;
    if (is_point_on_seg(c, d, a)) se.insert(a);
    if (is_point_on_seg(c, d, b)) se.insert(b);
    if (is_point_on_seg(a, b, c)) se.insert(c);
    if (is_point_on_seg(a, b, d)) se.insert(d);
    return se;
}
//intersection  between segment ab and line cd
//0 if do not intersect, 1 if proper intersect, 2 if segment intersect
int seg_line_relation(PT a, PT b, PT c, PT d) {
    T p = cross2(c, d, a);
    T q = cross2(c, d, b);
    if (sign(p) == 0 && sign(q) == 0) return 2;
    else if (p * q < 0) return 1;
    else return 0;
}
//intersection between segament ab and line cd assuming unique intersection exists
bool seg_line_intersection(PT a, PT b, PT c, PT d, PT &ans) {
    bool k = seg_line_relation(a, b, c, d);
    assert(k != 2);
    if (k) line_line_intersection(a, b, c, d, ans);
    return k;
}
//minimum distance from segment ab to segment cd
ld dist_from_seg_to_seg(PT a, PT b, PT c, PT d) {
    PT dummy;
    if (seg_seg_intersection(a, b, c, d, dummy)) return (T)0.0;
    else return min({dist_from_point_to_seg(a, b, c), dist_from_point_to_seg(a, b, d), 
        dist_from_point_to_seg(c, d, a), dist_from_point_to_seg(c, d, b)});
}
//minimum distance from point c to ray [a,b)
ld dist_from_point_to_ray(PT a, PT b, PT c) {
    b = a + b;
    T r = dot(c - a, b - a);
    if (r < 0.0) return dist(c, a);
    return dist_from_point_to_line(a, b, c);
}
//starting point as and direction vector ad
bool ray_ray_intersection(PT as, PT ad, PT bs, PT bd) {
    T dx = bs.x - as.x, dy = bs.y - as.y;
    T det = bd.x * ad.y - bd.y * ad.x;
    if (abs(det) < eps) return 0;
    T u = (dy * bd.x - dx * bd.y) / det;
    T v = (dy * ad.x - dx * ad.y) / det;
    if (sign(u) >= 0 && sign(v) >= 0) return 1;
    else return 0;
}
ld ray_ray_distance(PT as,PT ad,PT bs,PT bd){
    if(ray_ray_intersection(as, ad, bs, bd)) return 0.0;
    ld ans = dist_from_point_to_ray(as, ad, bs);
    ans = min(ans, dist_from_point_to_ray(bs, bd, as));
    return ans;
}
struct circle {
    PT p; T r;
    circle() {}
    circle(PT _p, T _r): p(_p), r(_r) {};
    //center (x, y) and radius r
    circle(T x, T y, T _r): p(PT(x, y)), r(_r) {};
    //circumcircle of a triangle
    //the three points must be unique
    circle(PT a, PT b, PT c) {
        b = (a + b) * 0.5;
        c = (a + c) * 0.5;
        line_line_intersection(b, b + rotate_cw90(a - b), c, c + rotate_cw90(a - c), p);
        r = dist(a, p);
    }
    //inscribed circle of a triangle
    circle(PT a, PT b, PT c, bool t) {
        line u, v;
        ld m = atan2(b.y - a.y, b.x - a.x);
        ld n = atan2(c.y - a.y, c.x - a.x);
        u.a = a;
        u.b = u.a + (PT(cos((n + m)/2.0), sin((n + m)/2.0)));
        v.a = b;
        m = atan2(a.y - b.y, a.x - b.x);
        n = atan2(c.y - b.y, c.x - b.x);
        v.b = v.a + (PT(cos((n + m)/2.0), sin((n + m)/2.0)));
        line_line_intersection(u.a, u.b, v.a, v.b, p);
        r = dist_from_point_to_seg(a, b, p);
    }
    bool operator == (circle v) { return p == v.p && sign(r - v.r) == 0; }
    ld area() { return PI * r * r; }
    ld circumference() { return 2.0 * PI * r; }
};
//0 if outside, 1 if on circumference, 2 if inside circle
int circle_point_relation(PT p, T r, PT b) {
    ld d = dist(p, b);
    if (sign(d - r) < 0) return 2;
    if (sign(d - r) == 0) return 1;
    return 0;
}
//0 if outside, 1 if on circumference, 2 if inside circle
int circle_line_relation(PT p, T r, PT a, PT b) {
    double d = dist_from_point_to_line(a, b, p);
    if (sign(d - r) < 0) return 2;
    if (sign(d - r) == 0) return 1;
    return 0;
}
//compute intersection of line through points a and b with
//circle centered at c with radius r > 0
vector<PT> circle_line_intersection(PT c,T r,PT a,PT b){
    vector<PT> ret;
    b = b - a; a = a - c;
    T A = dot(b, b), B = dot(a, b);
    T C = dot(a, a) - r * r, D = B * B - A * C;
    if(D < -eps) return ret;
    ret.push_back(c + a + b * (-B + sqrt(D + eps)) / A);
    if (D > eps) ret.push_back(c + a + b * (-B - sqrt(D)) / A);
    return ret;
}
//5 - outside and do not intersect
//4 - intersect outside in one point
//3 - intersect in 2 points
//2 - intersect inside in one point
//1 - inside and do not intersect
int circle_circle_relation(PT a, T r, PT b, T R) {
    ld d = dist(a, b);
    if (sign(d - r - R) > 0)  return 5;
    if (sign(d - r - R) == 0) return 4;
    ld l = fabs(r - R);
    if (sign(d - r - R) < 0 && sign(d - l) > 0) return 3;
    if (sign(d - l) == 0) return 2;
    if (sign(d - l) < 0) return 1;
    assert(0); return -1;
}
vector<PT> circle_circle_intersection(PT a,T r,PT b,T R){
    if(a == b && sign(r-R) == 0) return {PT(1e18, 1e18)};
    vector<PT> ret;
    ld d = sqrt(dist2(a,  b));
    if(d > r + R || d + min(r,R) < max(r,R)) return ret;
    ld x = (d * d - R * R + r * r) / (2 * d);
    ld y = sqrt(r * r - x * x);
    PT v = (b - a) / d;
    ret.push_back(a + v * x  +  rotate_ccw90(v) * y);
    if(y>0) ret.push_back(a + v * x - rotate_ccw90(v) * y);
    return ret;
}
//returns two circle c1, c2 through points a, b and of radius r
//0 if there is no such circle, 1 if one circle, 2 if two circle
int get_circle(PT a, PT b, T r, circle &c1, circle &c2){
    vector<PT> v = circle_circle_intersection(a, r, b, r);
    int t = v.size();
    if (!t) return 0;
    c1.p = v[0], c1.r = r;
    if (t == 2) c2.p = v[1], c2.r = r;
    return t;
}
// returns two circle c1, c2 which is tangent to line u,  goes through
// point q and has radius r1; 0 for no circle, 1 if c1 = c2 , 2 if c1 != c2
int get_circle(line u, PT q, T r1, circle &c1, circle &c2) {
    double d = dist_from_point_to_line(u.a, u.b, q);
    if (sign(d - r1 * 2.0) > 0) return 0;
    if (sign(d) == 0) {
        cout << u.v.x << ' ' << u.v.y << '\n';
        c1.p = q + rotate_ccw90(u.v).truncate(r1);
        c2.p = q + rotate_cw90(u.v).truncate(r1);
        c1.r = c2.r = r1;
        return 2;
    }
    line u1 = line(u.a + rotate_ccw90(u.v).truncate(r1), u.b + rotate_ccw90(u.v).truncate(r1));
    line u2 = line(u.a + rotate_cw90(u.v).truncate(r1), u.b + rotate_cw90(u.v).truncate(r1));
    circle cc = circle(q, r1);
    PT p1, p2; vector<PT> v;
    v = circle_line_intersection(q, r1, u1.a, u1.b);
    if (!v.size()) v = circle_line_intersection(q, r1, u2.a, u2.b);
    v.push_back(v[0]);
    p1 = v[0], p2 = v[1];
    c1 = circle(p1, r1);
    if (p1 == p2) {
        c2 = c1;
        return 1;
    }
    c2 = circle(p2, r1);
    return 2;
}
// returns area of intersection between two circles
ld circle_circle_area(PT a, T r1, PT b, T r2){
    ld d = (a - b).norm();
    if(r1 + r2 < d + eps) return 0;
    if(r1 + d < r2 + eps) return PI * r1 * r1;
    if(r2 + d < r1 + eps) return PI * r2 * r2;
    double theta_1 = acos((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d)), theta_2 = acos((r2 * r2 + d * d - r1 * r1)/(2 * r2 * d));
    return r1 * r1 * (theta_1 - sin(2 * theta_1)/2.) + r2 * r2 * (theta_2 - sin(2 * theta_2)/2.);
}
// tangent lines from point q to the circle
int tangent_lines_from_point(PT p, T r, PT q, line &u, line &v) {
    int x = sign(dist2(p, q) - r * r);
    if (x < 0) return 0; // point in cricle
    if (x == 0) { // point on circle
        u = line(q, q + rotate_ccw90(q - p));
        v = u;
        return 1;
    }
    ld d = dist(p, q);
    ld l = r * r / d;
    ld h = sqrt(r * r - l * l);
    u = line(q, p + ((q - p).truncate(l) + (rotate_ccw90(q - p).truncate(h))));
    v = line(q, p + ((q - p).truncate(l) + (rotate_cw90(q - p).truncate(h))));
    return 2;
}
// returns outer tangents line of two circles
// if inner == 1 it returns inner tangent lines
int tangents_lines_from_circle(PT c1, T r1, PT c2, T r2, bool inner, line &u, line &v) {
    if (inner) r2 = -r2;
    PT d = c2 - c1;
    T dr = r1 - r2, d2 = d.norm(), h2 = d2 - dr * dr;
    if (d2 == 0 || h2 < 0) {
        assert(h2 != 0);
        return 0;
    }
    vector<pair<PT, PT>>out;
    for (int tmp: {- 1, 1}) {
        PT v = (d * dr + rotate_ccw90(d) * sqrt(h2) * tmp) / d2;
        out.push_back({c1 + v * r1, c2 + v * r2});
    }
    u = line(out[0].first, out[0].second);
    if (out.size() == 2) v = line(out[1].first, out[1].second);
    return 1 + (h2 > 0);
}
//O(n^2 log n)
struct CircleUnion {
    int n;
    T x[2020], y[2020], r[2020];
    int covered[2020];
    vector<pair<T, T> > seg, cover;
    T arc, pol;
    int sign(T x) {return x < -eps ? -1 : x > eps;}
    int sign(T x, T y) {return sign(x - y);}
    T SQ(const T x) {return x * x;}
    ld dist(T x1, T y1, T x2, T y2) {return sqrt(SQ(x1 - x2) + SQ(y1 - y2));}
    ld angle(T A, T B, T C) {
        ld val = (SQ(A) + SQ(B) - SQ(C)) / (2 * A * B);
        if (val < -1) val = -1;
        if (val > +1) val = +1;
        return acos(val);
    }
    CircleUnion() {
        n = 0;
        seg.clear(), cover.clear();
        arc = pol = 0;
    }
    void init() {
        n = 0;
        seg.clear(), cover.clear();
        arc = pol = 0;
    }
    void add(T xx, T yy, T rr) {
        x[n] = xx, y[n] = yy, r[n] = rr, covered[n] = 0, n++;
    }
    void getarea(int i, T lef, T rig) {
        arc += 0.5 * r[i] * r[i] * (rig - lef - sin(rig - lef));
        ld x1 = x[i] + r[i] * cos(lef), y1 = y[i] + r[i] * sin(lef);
        ld x2 = x[i] + r[i] * cos(rig), y2 = y[i] + r[i] * sin(rig);
        pol += x1 * y2 - x2 * y1;
    }
    ld solve() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (!sign(x[i] - x[j]) && !sign(y[i] - y[j]) && !sign(r[i] - r[j])) {
                    r[i] = 0.0;
                    break;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && sign(r[j] - r[i]) >= 0 && sign(dist(x[i], y[i], x[j], y[j]) - (r[j] - r[i])) <= 0) {
                    covered[i] = 1;
                    break;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (sign(r[i]) && !covered[i]) {
                seg.clear();
                for (int j = 0; j < n; j++) {
                    if (i != j) {
                        ld d = dist(x[i], y[i], x[j], y[j]);
                        if (sign(d - (r[j] + r[i])) >= 0 || sign(d - abs(r[j] - r[i])) <= 0) {
                            continue;
                        }
                        ld alpha = atan2(y[j] - y[i], x[j] - x[i]);
                        ld beta = angle(r[i], d, r[j]);
                        pair<ld,ld> tmp(alpha - beta, alpha + beta);
                        if (sign(tmp.first) <= 0 && sign(tmp.second) <= 0) {
                            seg.push_back(pair<ld, ld>(2 * PI + tmp.first, 2 * PI + tmp.second));
                        }
                        else if (sign(tmp.first) < 0) {
                            seg.push_back(pair<ld, ld>(2 * PI + tmp.first, 2 * PI));
                            seg.push_back(pair<ld, ld>(0, tmp.second));
                        }
                        else {
                            seg.push_back(tmp);
                        }
                    }
                }
                sort(seg.begin(), seg.end());
                ld rig = 0;
                for (vector<pair<ld,ld> >::iterator iter = seg.begin(); iter != seg.end(); iter++) {
                    if (sign(rig - iter->first) >= 0) {
                        rig = max(rig, iter->second);
                    }
                    else {
                        getarea(i, rig, iter->first);
                        rig = iter->second;
                    }
                }
                if (!sign(rig)) {
                    arc += r[i] * r[i] * PI;
                }
                else {
                    getarea(i, rig, 2 * PI);
                }
            }
        }
        return pol / 2.0 + arc;
    }
} CU;
ld area_of_triangle(PT a, PT b, PT c) {
    return fabs(cross(b - a, c - a) * 0.5);
}
//-1 if strictly inside, 0 if on the polygon, 1 if strictly outside
int is_point_in_triangle(PT a, PT b, PT c, PT p) {
    if (sign(cross(b - a,c - a)) < 0) swap(b, c);
    int c1 = sign(cross(b - a,p - a));
    int c2 = sign(cross(c - b,p - b));
    int c3 = sign(cross(a - c,p - c));
    if (c1<0 || c2<0 || c3 < 0) return 1;
    if (c1 + c2 + c3 != 3) return 0;
    return -1;
}
T perimeter(vector<PT> &p) {
    T ans=0; int n = p.size();
    for (int i = 0; i < n; i++) ans += dist(p[i], p[(i + 1) % n]);
    return ans;
}
ld area(vector<PT> &p) {
    ld ans = 0; int n = p.size();
    for (int i = 0; i < n; i++) ans += cross(p[i], p[(i + 1) % n]);
    return fabs(ans) * 0.5;
}
// centroid of a (possibly non-convex) polygon, 
// assuming that the coordinates are listed in a clockwise or
// counterclockwise fashion.  Note that the centroid is often known as
// the "center of gravity" or "center of mass".
PT centroid(vector<PT> &p) {
    int n = p.size(); PT c(0, 0);
    ld sum = 0;
    for (int i = 0; i < n; i++) sum += cross(p[i], p[(i + 1) % n]);
    ld scale = 3.0 * sum;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        c = c + (p[i] + p[j]) * cross(p[i], p[j]);
    }
    return c / scale;
}
// 0 if cw, 1 if ccw
bool get_direction(vector<PT> &p) {
    ld ans = 0; int n = p.size();
    for (int i = 0; i < n; i++) ans += cross(p[i], p[(i + 1) % n]);
    if (sign(ans) > 0) return 1;
    return 0;
}
// it returns a point such that the sum of distances
// from that point to all points in p  is minimum
// O(n log^2 MX)
PT geometric_median(vector<PT> p) {
    auto tot_dist = [&](PT z) {
    T res = 0;
        for (int i = 0; i < p.size(); i++) res += dist(p[i], z);
        return res;
    };
    auto findY = [&](T x) {
        T yl = -1e5, yr = 1e5;
        for (int i = 0; i < 60; i++) {
            T ym1 = yl + (yr - yl) / 3;
            T ym2 = yr - (yr - yl) / 3;
            T d1 = tot_dist(PT(x, ym1));
            T d2 = tot_dist(PT(x, ym2));
            if (d1 < d2) yr = ym2;
            else yl = ym1;
        }
        return pair<double, double> (yl, tot_dist(PT(x, yl)));
    };
    T xl = -1e5, xr = 1e5;
    for (int i = 0; i < 60; i++) {
        T xm1 = xl + (xr - xl) / 3;
        T xm2 = xr - (xr - xl) / 3;
        T y1, d1, y2, d2;
        auto z = findY(xm1); y1 = z.first; d1 = z.second;
        z = findY(xm2); y2 = z.first; d2 = z.second;
        if (d1 < d2) xr = xm2;
        else xl = xm1;
    }
    return {xl, findY(xl).first };
}
vector<PT> convex_hull(vector<PT> &p) {
    if (p.size() <= 1) return p;
    vector<PT> v = p;
    sort(v.begin(), v.end());
    vector<PT> up, dn;
    for (auto& p : v) {
        while (up.size() > 1 && orientation(up[up.size() - 2], up.back(), p) >= 0) {
            up.pop_back();
        }
        while (dn.size() > 1 && orientation(dn[dn.size() - 2], dn.back(), p) <= 0) {
            dn.pop_back();
        }
        up.push_back(p);
        dn.push_back(p);
    }
    v = dn;
    if (v.size() > 1) v.pop_back();
    reverse(up.begin(), up.end());
    up.pop_back();
    for (auto& p : up) {
        v.push_back(p);
    }
    if (v.size() == 2 && v[0] == v[1]) v.pop_back();
    return v;
}
//checks if convex or not
bool is_convex(vector<PT> &p) {
    bool s[3]; s[0] = s[1] = s[2] = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        int k = (j + 1) % n;
        s[sign(cross(p[j] - p[i], p[k] - p[i])) + 1] = 1;
        if (s[0] && s[2]) return 0;
    }
    return 1;
}
// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
// it must be strictly convex, otherwise make it strictly convex first
int is_point_in_convex(vector<PT> &p, const PT& x) { // O(log n)
    int n = p.size(); assert(n >= 3);
    int a = orientation(p[0], p[1], x), b = orientation(p[0], p[n - 1], x);
    if (a < 0 || b > 0) return 1;
    int l = 1, r = n - 1;
    while (l + 1 < r) {
        int mid = l + r >> 1;
        if (orientation(p[0], p[mid], x) >= 0) l = mid;
        else r = mid;
    }
    int k = orientation(p[l], p[r], x);
    if (k <= 0) return -k;
    if (l == 1 && a == 0) return 0;
    if (r == n - 1 && b == 0) return 0;
    return -1;
}
bool is_point_on_polygon(vector<PT> &p, const PT& z) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (is_point_on_seg(p[i], p[(i + 1) % n], z)) return 1;
    }
    return 0;
}
// returns 1e9 if the point is on the polygon 
int winding_number(vector<PT> &p, const PT& z) { // O(n)
    if (is_point_on_polygon(p, z)) return 1e9;
    int n = p.size(), ans = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        bool below = p[i].y < z.y;
        if (below != (p[j].y < z.y)) {
            auto orient = orientation(z, p[j], p[i]);
            if (orient == 0) return 0;
            if (below == (orient > 0)) ans += below ? 1 : -1;
        }
    }
    return ans;
}
// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
int is_point_in_polygon(vector<PT> &p, const PT& z) { // O(n)
    int k = winding_number(p, z);
    return k == 1e9 ? 0 : k == 0 ? 1 : -1;
}
// id of the vertex having maximum dot product with z
// polygon must need to be convex
// top - upper right vertex
// for minimum dot prouct negate z and return -dot(z, p[id])
int extreme_vertex(vector<PT> &p, const PT &z, const int top) { // O(log n)
    int n = p.size();
    if (n == 1) return 0;
    T ans = dot(p[0], z); int id = 0;
    if (dot(p[top], z) > ans) ans = dot(p[top], z), id = top;
    int l = 1, r = top - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (dot(p[mid + 1], z) >= dot(p[mid], z)) l = mid + 1;
        else r = mid;
    }
    if (dot(p[l], z) > ans) ans = dot(p[l], z), id = l;
    l = top + 1, r = n - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (dot(p[(mid + 1) % n], z) >= dot(p[mid], z)) l = mid + 1;
        else r = mid;
    }
    l %= n;
    if (dot(p[l], z) > ans) ans = dot(p[l], z), id = l;
    return id;
}
ld diameter(vector<PT> &p) {
    int n = (int)p.size();
    if (n == 1) return 0;
    if (n == 2) return dist(p[0], p[1]);
    T ans = 0;
    int i = 0, j = 1;
    while (i < n) {
        while (cross(p[(i + 1) % n] - p[i], p[(j + 1) % n] - p[j]) >= 0) {
            ans = max(ans, dist2(p[i], p[j]));
            j = (j + 1) % n;
        }
        ans = max(ans, dist2(p[i], p[j]));
        i++;
    }
    return sqrt(ans);
}
ld width(vector<PT> &p) {
    int n = (int)p.size();
    if (n <= 2) return 0;
    ld ans = inf;
    int i = 0, j = 1;
    while (i < n) {
        while (cross(p[(i + 1) % n] - p[i], p[(j + 1) % n] - p[j]) >= 0) j = (j + 1) % n;
        ans = min(ans, dist_from_point_to_line(p[i], p[(i + 1) % n], p[j]));
        i++;
    }
    return ans;
}
// minimum perimeter
ld minimum_enclosing_rectangle(vector<PT> &p) {
    int n = p.size();
    if (n <= 2) return perimeter(p);
    int mndot = 0; T tmp = dot(p[1] - p[0], p[0]);
    for (int i = 1; i < n; i++) {
        if (dot(p[1] - p[0], p[i]) <= tmp) {
            tmp = dot(p[1] - p[0], p[i]);
            mndot = i;
        }
    }
    ld ans = inf;
    int i = 0, j = 1, mxdot = 1;
    while (i < n) {
        PT cur = p[(i + 1) % n] - p[i];
        while (cross(cur, p[(j + 1) % n] - p[j]) >= 0) j = (j + 1) % n;
        while (dot(p[(mxdot + 1) % n], cur) >= dot(p[mxdot], cur)) mxdot = (mxdot + 1) % n;
        while (dot(p[(mndot + 1) % n], cur) <= dot(p[mndot], cur)) mndot = (mndot + 1) % n;
        ans = min(ans, 2.0 * ((dot(p[mxdot], cur) / cur.norm() - dot(p[mndot], cur) / cur.norm()) + dist_from_point_to_line(p[i], p[(i + 1) % n], p[j])));
        i++;
    }
    return ans;
}
// given n points, find the minimum enclosing circle of the points
// call convex_hull() before this for faster solution
// expected O(n)
circle minimum_enclosing_circle(vector<PT> &p) {
    random_shuffle(p.begin(), p.end());
    int n = p.size();
    circle c(p[0], 0);
    for (int i = 1; i < n; i++) {
        if (sign(dist(c.p, p[i]) - c.r) > 0) {
            c = circle(p[i], 0);
            for (int j = 0; j < i; j++) {
                if (sign(dist(c.p, p[j]) - c.r) > 0) {
                    c = circle((p[i] + p[j]) / 2, dist(p[i], p[j]) / 2);
                    for (int k = 0; k < j; k++) {
                        if (sign(dist(c.p, p[k]) - c.r) > 0) {
                            c = circle(p[i], p[j], p[k]);
                        }
                    }
                }
            }
        }
    }
    return c;
}
// returns a vector with the vertices of a polygon with everything 
// to the left of the line going from a to b cut away.
vector<PT> cut(vector<PT> &p, PT a, PT b) {
    vector<PT> ans;
    int n = (int)p.size();
    for (int i = 0; i < n; i++) {
        T c1 = cross(b - a, p[i] - a);
        T c2 = cross(b - a, p[(i + 1) % n] - a);
        if (sign(c1) >= 0) ans.push_back(p[i]);
        if (sign(c1 * c2) < 0) {
            if (!is_parallel(p[i], p[(i + 1) % n], a, b)) {
                PT tmp; line_line_intersection(p[i], p[(i + 1) % n], a, b, tmp);
                ans.push_back(tmp);
            }
        }
    }
    return ans;
}
// not necessarily convex, boundary is included in the intersection
// returns total intersected length
ld polygon_line_intersection(vector<PT> &p, PT a, PT b) {
    int n = p.size();
    p.push_back(p[0]);
    line l = line(a, b);
    ld ans = 0.0;
    vector< pair<ld, int> > vec;
    for (int i = 0; i < n; i++) {
        int s1 = sign(cross(b - a, p[i] - a));
        int s2 = sign(cross(b - a, p[i+1] - a));
        if (s1 == s2) continue;
        line t = line(p[i], p[i + 1]);
        PT inter = (t.v * l.c - l.v * t.c) / cross(l.v, t.v);
        ld tmp = dot(inter, l.v);
        int f;
        if (s1 > s2) f = s1 && s2 ? 2 : 1;
        else f = s1 && s2 ? -2 : -1;
        vec.push_back(make_pair(tmp, f));
    }
    sort(vec.begin(), vec.end());
    for (int i = 0, j = 0; i + 1 < (int)vec.size(); i++){
        j += vec[i].second;
        if (j) ans += vec[i + 1].first - vec[i].first;
    }
    ans = ans / sqrt(dot(l.v, l.v));
    p.pop_back();
    return ans;
}
pair<PT, PT> convex_line_intersection(vector<PT> &p, PT a, PT b) {
    return {{0, 0}, {0, 0}};
}
pair<PT, int> point_poly_tangent(vector<PT> &p, PT Q, int dir, int l, int r) {
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        bool pvs = orientation(Q, p[mid], p[mid - 1]) != -dir;
        bool nxt = orientation(Q, p[mid], p[mid + 1]) != -dir;
        if (pvs && nxt) return {p[mid], mid};
        if (!(pvs || nxt)) {
            auto p1 = point_poly_tangent(p, Q, dir, mid + 1, r);
            auto p2 = point_poly_tangent(p, Q, dir, l, mid - 1);
            return orientation(Q, p1.first, p2.first) == dir ? p1 : p2;
        }
        if (!pvs) {
            if (orientation(Q, p[mid], p[l]) == dir)  r = mid - 1;
            else if (orientation(Q, p[l], p[r]) == dir) r = mid - 1;
            else l = mid + 1;
        }
        if (!nxt) {
            if (orientation(Q, p[mid], p[l]) == dir)  l = mid + 1;
            else if (orientation(Q, p[l], p[r]) == dir) r = mid - 1;
            else l = mid + 1;
        }
    }
    pair<PT, int> ret = {p[l], l};
    for (int i = l + 1; i <= r; i++) ret = orientation(Q, ret.first, p[i]) != dir ? make_pair(p[i], i) : ret;
    return ret;
}
// minimum distance from a point to a convex polygon
// it assumes point does not lie strictly inside the polygon
// O(log n)
ld dist_from_point_to_polygon(vector<PT> &p, PT z) {
    ld ans = inf;
    int n = p.size();
    if (n <= 3) {
        for(int i = 0; i < n; i++) ans = min(ans, dist_from_point_to_seg(p[i], p[(i + 1) % n], z));
        return ans;
    }
    auto [r, l] = tangents_from_point_to_polygon(p, z);
    if(l > r) r += n;
    while (l < r) {
        int mid = (l + r) >> 1;
        ld left = dist2(p[mid % n], z), right= dist2(p[(mid + 1) % n], z);
        ans = min({ans, left, right});
        if(left < right) r = mid;
        else l = mid + 1;
    }
    ans = sqrt(ans);
    ans = min(ans, dist_from_point_to_seg(p[l % n], p[(l + 1) % n], z));
    ans = min(ans, dist_from_point_to_seg(p[l % n], p[(l - 1 + n) % n], z));
    return ans;
}
// minimum distance from convex polygon p to line ab
// returns 0 is it intersects with the polygon
// top - upper right vertex
ld dist_from_polygon_to_line(vector<PT> &p, PT a, PT b, int top) { //O(log n)
    PT orth = (b - a).perp();
    if (orientation(a, b, p[0]) > 0) orth = (a - b).perp();
    int id = extreme_vertex(p, orth, top);
    if (dot(p[id] - a, orth) > 0) return 0.0; //if orth and a are in the same half of the line, then poly and line intersects
    return dist_from_point_to_line(a, b, p[id]); //does not intersect
}
// minimum distance from a convex polygon to another convex polygon
// the polygon doesnot overlap or touch
ld dist_from_polygon_to_polygon(vector<PT> &p1, vector<PT> &p2) { // O(n log n)
    ld ans = inf;
    for (int i = 0; i < p1.size(); i++) {
        ans = min(ans, dist_from_point_to_polygon(p2, p1[i]));
    }
    for (int i = 0; i < p2.size(); i++) {
        ans = min(ans, dist_from_point_to_polygon(p1, p2[i]));
    }
    return ans;
}
// maximum distance from a convex polygon to another convex polygon
ld maximum_dist_from_polygon_to_polygon(vector<PT> &u, vector<PT> &v){ //O(n)
    int n = (int)u.size(), m = (int)v.size();
    ld ans = 0;
    if (n < 3 || m < 3) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) ans = max(ans, dist2(u[i], v[j]));
        }
        return sqrt(ans);
    }
    if (u[0].x > v[0].x) swap(n, m), swap(u, v);
    int i = 0, j = 0, step = n + m + 10;
    while (j + 1 < m && v[j].x < v[j + 1].x) j++ ;
    while (step--) {
        if (cross(u[(i + 1)%n] - u[i], v[(j + 1)%m] - v[j]) >= 0) j = (j + 1) % m;
        else i = (i + 1) % n;
        ans = max(ans, dist2(u[i], v[j]));
    }
    return sqrt(ans);
}
// (cw, ccw) tangents from a point that is outside this convex polygon
// returns indexes of the points
pair<int, int> tangents_from_point_to_polygon(vector<PT> &p, PT Q){
    int cw = point_poly_tangent(p, Q, 1, 0, (int)p.size() - 1).second;
    int ccw = point_poly_tangent(p, Q, -1, 0, (int)p.size() - 1).second;
    return make_pair(cw, ccw);
}
// calculates the area of the union of n polygons (not necessarily convex). 
// the points within each polygon must be given in CCW order.
// complexity: O(N^2), where N is the total number of points
ld rat(PT a, PT b, PT p) {
        return !sign(a.x - b.x) ? (p.y - a.y) / (b.y - a.y) : (p.x - a.x) / (b.x - a.x);
 };
ld polygon_union(vector<vector<PT>> &p) {
    int n = p.size();
    ld ans=0;
    for(int i = 0; i < n; ++i) {
        for (int v = 0; v < (int)p[i].size(); ++v) {
            PT a = p[i][v], b = p[i][(v + 1) % p[i].size()];
            vector<pair<ld, int>> segs;
            segs.emplace_back(0,  0), segs.emplace_back(1,  0);
            for(int j = 0; j < n; ++j) {
                if(i != j) {
                    for(size_t u = 0; u < p[j].size(); ++u) {
                        PT c = p[j][u], d = p[j][(u + 1) % p[j].size()];
                        int sc = sign(cross(b - a, c - a)), sd = sign(cross(b - a, d - a));
                        if(!sc && !sd) {
                            if(sign(dot(b - a, d - c)) > 0 && i > j) {
                                segs.emplace_back(rat(a, b, c), 1), segs.emplace_back(rat(a, b, d),  -1);
                            }
                        } 
                        else {
                            ld sa = cross(d - c, a - c), sb = cross(d - c, b - c);
                            if(sc >= 0 && sd < 0) segs.emplace_back(sa / (sa - sb), 1);
                            else if(sc < 0 && sd >= 0) segs.emplace_back(sa / (sa - sb),  -1);
                        }
                    }
                }
            }
            sort(segs.begin(),  segs.end());
            double pre = min(max(segs[0].first, 0.0), 1.0), now, sum = 0;
            int cnt = segs[0].second;
            for(int j = 1; j < segs.size(); ++j) {
                now = min(max(segs[j].first, 0.0), 1.0);
                if (!cnt) sum += now - pre;
                cnt += segs[j].second;
                pre = now;
            }
            ans += cross(a, b) * sum;
        }
    }
    return ans * 0.5;
}
//contains all points p such that: cross(b - a, p - a) >= 0
struct HP {
    PT a, b;
    HP() {}
    HP(PT a, PT b) : a(a), b(b) {}
    HP(const HP& rhs) : a(rhs.a), b(rhs.b) {}
    int operator < (const HP& rhs) const {
        PT p = b - a;
        PT q = rhs.b - rhs.a;
        int fp = (p.y < 0 || (p.y == 0 && p.x < 0));
        int fq = (q.y < 0 || (q.y == 0 && q.x < 0));
        if (fp != fq) return fp == 0;
        if (cross(p, q)) return cross(p, q) > 0;
        return cross(p, rhs.b - a) < 0;
    }
    PT line_line_intersection(PT a, PT b, PT c, PT d) {
        b = b - a; d = c - d; c = c - a;
        return a + b * cross(c, d) / cross(b, d);
    }
    PT intersection(const HP &v) {
        return line_line_intersection(a, b, v.a, v.b);
    }
};
int check(HP a, HP b, HP c) {
    return cross(a.b - a.a, b.intersection(c) - a.a) > -eps; //-eps to include polygons of zero area (straight lines, points)
}
// consider half-plane of counter-clockwise side of each line
// if lines are not bounded add infinity rectangle
// returns a convex polygon, a point can occur multiple times though
// complexity: O(n log(n))
vector<PT> half_plane_intersection(vector<HP> h) {
    sort(h.begin(), h.end());
    vector<HP> tmp;
    for (int i = 0; i < h.size(); i++) {
        if (!i || cross(h[i].b - h[i].a, h[i - 1].b - h[i - 1].a)) {
            tmp.push_back(h[i]);
        }
    }
    h = tmp;
    vector<HP> q(h.size() + 10);
    int qh = 0, qe = 0;
    for (int i = 0; i < h.size(); i++) {
        while (qe - qh > 1 && !check(h[i], q[qe - 2], q[qe - 1])) qe--;
        while (qe - qh > 1 && !check(h[i], q[qh], q[qh + 1])) qh++;
        q[qe++] = h[i];
    }
    while (qe - qh > 2 && !check(q[qh], q[qe - 2], q[qe - 1])) qe--;
    while (qe - qh > 2 && !check(q[qe - 1], q[qh], q[qh + 1])) qh++;
    vector<HP> res; 
    for (int i = qh; i < qe; i++) res.push_back(q[i]);
    vector<PT> hull;
    if (res.size() > 2) {
        for (int i = 0; i < res.size(); i++) {
             hull.push_back(res[i].intersection(res[(i + 1) % ((int)res.size())]));
        }
    }
    return hull;
}
// a and b are strictly convex polygons of DISTINCT points
// returns a convex hull of their minkowski sum with distinct points
vector<PT> minkowski_sum(vector<PT> &a, vector<PT> &b) {
    int n = (int)a.size(), m = (int)b.size();
    int i = 0, j = 0; //assuming a[i] and b[j] both are (left, bottom)-most points
    vector<PT> c;
    c.push_back(a[i] + b[j]);
    while (1){
        PT p1 = a[i] + b[(j + 1) % m];
        PT p2 = a[(i + 1) % n] + b[j];
        int t = orientation(c.back(), p1, p2);
        if (t >= 0) j = (j + 1) % m;
        if (t <= 0) i = (i + 1) % n, p1 = p2;
        if (t == 0) p1 = a[i] + b[j];
        if (p1 == c[0]) break;
        c.push_back(p1);
    }
    return c;
}
// system should be translated from circle center
ld triangle_circle_intersection(PT c, T r, PT a, PT b) {
    ld sd1 = dist2(c, a), sd2 = dist2(c, b);
    if(sd1 > sd2) swap(a, b), swap(sd1, sd2);
    ld sd = dist2(a, b);
    ld d1 = sqrtl(sd1), d2 = sqrtl(sd2), d = sqrt(sd);
    ld x = abs(sd2 - sd - sd1) / (2 * d);
    ld h = sqrtl(sd1 - x * x);
    if(r >= d2) return h * d / 2;
    ld area = 0;
    if(sd + sd1 < sd2) {
        if(r < d1) area = r * r * (acos(h / d2) - acos(h / d1)) / 2;
        else {
            area = r * r * ( acos(h / d2) - acos(h / r)) / 2;
            ld y = sqrtl(r * r - h * h);
            area += h * (y - x) / 2;
        }
    } 
    else {
        if(r < h) area = r * r * (acos(h / d2) + acos(h / d1)) / 2;
        else {
            area += r * r * (acos(h / d2) - acos(h / r)) / 2;
            ld y = sqrtl(r * r - h * h);
            area += h * y / 2;
            if(r < d1) {
                area += r * r * (acos(h / d1) - acos(h / r)) / 2;
                area += h * y / 2;
            } 
            else area += h * x / 2;
        }
    }
    return area;
}
// intersection between a simple polygon and a circle
ld polygon_circle_intersection(vector<PT> &v, PT p, T r) {
    int n = v.size();
    ld ans = 0.00;
    PT org = {0, 0};
    for(int i = 0; i < n; i++) {
        int x = orientation(p, v[i], v[(i + 1) % n]);
        if(x == 0) continue;
        ld area = triangle_circle_intersection(org, r, v[i] - p, v[(i + 1) % n] - p);
        if (x < 0) ans -= area;
        else ans += area;
    }
    return ans * 0.5;
}
// find a circle of radius r that contains as many points as possible
// O(n^2 log n);
double maximum_circle_cover(vector<PT> p, T r, circle &c) {
    int n = p.size();
    int ans = 0;
    int id = 0; double th = 0;
    for (int i = 0; i < n; ++i) {
        // maximum circle cover when the circle goes through this point
        vector<pair<double, int>> events = {{-PI, +1}, {PI, -1}};
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;
            double d = dist(p[i], p[j]);
            if (d > r * 2) continue;
            double dir = (p[j] - p[i]).arg();
            double ang = acos(d / 2 / r);
            double st = dir - ang, ed = dir + ang;
            if (st > PI) st -= PI * 2;
            if (st <= -PI) st += PI * 2;
            if (ed > PI) ed -= PI * 2;
            if (ed <= -PI) ed += PI * 2;
            events.push_back({st, +1});
            events.push_back({ed, -1});
            if (st > ed) {
                events.push_back({-PI, +1});
                events.push_back({+PI, -1});
            }
        }
        sort(events.begin(), events.end());
        int cnt = 0;
        for (auto &&e: events) {
            cnt += e.second;
            if (cnt > ans) {
                ans = cnt;
                id = i; th = e.first;
            }
        }
    }
    PT w = PT(p[id].x + r * cos(th), p[id].y + r * sin(th));
    c = circle(w, r); //best_circle
    return ans;
}
// radius of the maximum inscribed circle in a convex polygon
ld maximum_inscribed_circle(vector<PT> p) {
    int n = p.size();
    if (n <= 2) return 0;
    ld l = 0, r = 20000;
    while (r - l > eps) {
        ld mid = (l + r) * 0.5;
        vector<HP> h;
        const int L = 1e9;
        h.push_back(HP(PT(-L, -L), PT(L, -L)));
        h.push_back(HP(PT(L, -L), PT(L, L)));
        h.push_back(HP(PT(L, L), PT(-L, L)));
        h.push_back(HP(PT(-L, L), PT(-L, -L)));
        for (int i = 0; i < n; i++) {
            PT z = (p[(i + 1) % n] - p[i]).perp();
            z = z.truncate(mid);
            PT y = p[i] + z, q = p[(i + 1) % n] + z;
            h.push_back(HP(p[i] + z, p[(i + 1) % n] + z));
        }
        vector<PT> nw = half_plane_intersection(h);
        if (!nw.empty()) l = mid;
        else r = mid;
    }
    return l;
}
int32_t main()
{
    cout << "hello"<<endl;
 
    PT p1 = PT(0,0);
    PT p2 = PT(0,5);
    PT p3 = PT(5,0);
    cout<<orientation(p1,p2,p3)<<endl;
 
    return 0;
}
