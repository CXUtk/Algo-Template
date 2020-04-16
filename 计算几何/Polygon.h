#include <vector>
#include "Line.h"
#include "Vector2.h"
using namespace std;

struct Polygon {
    vector<Point2> points;
};

double polygonArea(const Point2* p, int size) {
    double area = 0;
    for (int i = 1; i < size - 1; i++) {
        area += cross(p[i] - p[0], p[i + 1] - p[0]);
    }
    return area / 2.0;
}

int isPointInPolygon(const Point2& p, Polygon& polygon) {
    int wn = 0;
    int sz = polygon.points.size();
    for (int i = 0; i < sz; i++) {
        Point2& cur = polygon.points[i];
        Point2& nxt = polygon.points[(i + 1) % sz];
        if (onSegment(p, Segment(cur, nxt))) return -1;
        // 判断线段方向，正右负左
        int k = dcmp(cross(nxt - cur, p - cur));
        int d1 = dcmp(cur.y - p.y);
        int d2 = dcmp(nxt.y - p.y);
        if (k > 0 && d1 <= 0 && d2 > 0) wn++;
        if (k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    return !wn;
}