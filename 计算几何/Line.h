#include "Vector2.h"

struct Line {
    Point2 p;
    Vector2 d;
    Line() {}
    Line(Point2 p1, Point2 p2) : p(p1) { d = p2 - p1; }
};
struct Segment {
    Point2 p1;
    Point2 p2;
    Segment() {}
    Segment(Point2 p1, Point2 p2) : p1(p1), p2(p2) {}
};

bool hasIntersection(const Line& l1, const Line& l2) {
    return dcmp(cross(l1.d, l2.d));
}

// 调用前确保两直线有交点，cross != 0
Point2 getIntersection(const Line& l1, const Line& l2) {
    Vector2 u = l1.p - l2.p;
    double t = cross(l2.d, u) / cross(l1.d, l2.d);
    return l1.p + l1.d * t;
}

double distanceToLine(const Point2& p, const Line& line) {
    Vector2 v = p - line.p;
    return fabs(cross(line.d, v) / length(line.d));
}

// 如果超过端点就是端点到点p的距离
double distanceToSegment(const Point2& p, const Segment& segment) {
    if (segment.p1 == segment.p2) {
        return length(segment.p1 - p);
    }
    Vector2 v1 = segment.p2 - segment.p1, v2 = p - segment.p1,
            v3 = p - segment.p2;
    if (dcmp(dot(v1, v2)) < 0)
        return length(v2);
    else if (dcmp(dot(v1, v3)) > 0)
        return length(v3);
    return fabs(cross(v1, v2) / length(v1));
}

Point2 getLineProjection(const Point2& p, const Line& line) {
    return line.p + line.d * (dot(line.d, p - line.p) / dot(line.d, line.d));
}

bool segmentProperIntersection(const Segment& s1, const Segment& s2) {
    double c1 = cross(s1.p2 - s1.p1, s2.p1 - s1.p1),
           c2 = cross(s1.p2 - s1.p1, s2.p2 - s1.p1);
    if (dcmp(c1) * dcmp(c2) >= 0) return false;
    double c3 = cross(s2.p2 - s2.p1, s1.p1 - s2.p1),
           c4 = cross(s2.p2 - s2.p1, s1.p2 - s2.p1);
    return dcmp(c3) * dcmp(c4) < 0;
}

bool onSegment(const Point2& p, const Segment& seg) {
    return !dcmp(cross(seg.p1 - p, seg.p2 - p)) &&
           dcmp(dot(seg.p1 - p, seg.p2 - p)) < 0;
}
