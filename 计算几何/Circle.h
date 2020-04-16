#include <vector>
#include "Line.h"
#include "Vector2.h"
using namespace std;
struct Circle {
    Point2 c;
    double r;
    Circle() {}
    Circle(Point2 p, double r) : c(p), r(r) {}
    Point2 pointOn(double rad) const {
        return Point2(c.x + cos(rad) * r, c.y + sin(rad) * r);
    }
};

int getLineCircleIntersections(const Line& l, const Circle& c, double& t1,
                               double& t2, vector<Point2>& sol) {
    Point2 proj = getLineProjection(c.c, l);
    double dd = length(c.c - proj) - c.r;
    if (dcmp(dd) > 0) return 0;
    if (!dcmp(dd)) {
        t1 = t2 = getRad(proj - c.c);
        sol.push_back(proj);
        return 1;
    }
    double len = sqrt(c.r * c.r - lengthSq(c.c - proj));
    Point2 a = proj + l.d * len;
    t1 = getRad(a - c.c);
    sol.push_back(a);
    Point2 b = proj - l.d * len;
    t2 = getRad(b - c.c);
    sol.push_back(b);
    return 2;
}

int getCircleIntersections(const Circle& c1, const Circle& c2,
                           vector<Point2>& sol) {
    double d = length(c1.c - c2.c);
    // 重合
    if (!dcmp(d)) {
        if (dcmp(c1.r - c2.r) == 0) return -1;
        return 0;
    }
    // 外离
    if (dcmp(c1.r + c2.r - d) < 0) return 0;
    // 内含
    if (dcmp(fabs(c1.r - c2.r) - d) > 0) return 0;
    double a = getRad(c2.c - c1.c);
    double ra = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    Point2 p1 = c1.pointOn(a - ra);
    Point2 p2 = c1.pointOn(a + ra);
    sol.push_back(p1);
    if (p1 == p2) return 1;
    sol.push_back(p2);
    return 2;
}

int getTangents(const Point2& p, const Circle& c, vector<Vector2> sol) {
    Vector2 u = c.c - p;
    double dist = length(u);
    if (dist < c.r)
        return 0;
    else if (dcmp(dist - c.r) == 0) {
        sol.push_back(normal(u));
        return 1;
    } else {
        double ang = asin(c.r / dist);
        sol.push_back(rotate(u, ang));
        sol.push_back(rotate(u, -ang));
        return 2;
    }
}

int getCCTangents(const Circle* c1, const Circle* c2, vector<Point2>* a,
                  vector<Point2>* b) {
    int cnt = 0;
    if (c1->r < c2->r) {
        swap(c1, c2);
        swap(a, b);
    }
    double dist = length(c1->c - c2->c);
    // 从1到2的方向弧度
    double base = getRad(c2->c - c1->c);
    double rdiff = c1->r - c2->r;
    double rsum = c1->r + c2->r;
    // 内含
    if (dcmp(rdiff - dist) > 0) return 0;
    // 完全重合
    if (!dcmp(dist) && !dcmp(c1->r - c2->r)) return -1;
    // 内切
    if (!dcmp(rdiff - dist)) {
        a->push_back(c1->pointOn(base));
        b->push_back(c2->pointOn(base));
        return 1;
    }
    double ang = acos((c1->r - c2->r) / dist);
    a->push_back(c1->pointOn(base + ang)),
        b->push_back(c2->pointOn(base + ang));
    a->push_back(c1->pointOn(base - ang)),
        b->push_back(c2->pointOn(base - ang));
    cnt += 2;
    // 外切
    if (!dcmp(dist - rsum)) {
        a->push_back(c1->pointOn(base));
        b->push_back(c2->pointOn(PI + base));
        return cnt + 1;
    } else if (dcmp(dist - rsum) > 0) {
        ang = acos((c1->r + c2->r) / dist);
        a->push_back(c1->pointOn(base + ang)),
            b->push_back(c2->pointOn(PI + base + ang));
        a->push_back(c1->pointOn(base - ang)),
            b->push_back(c2->pointOn(PI + base - ang));
        return cnt + 2;
    }
    return cnt;
}