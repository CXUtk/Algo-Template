int dcmp(double x) {
    if (fabs(x) < EPS) return 0;
    return x > 0 ? 1 : -1;
}

struct Vector2 {
    double x, y;
    Vector2() {}
    Vector2(double x, double y) : x(x), y(y) {}
    Vector2(double rad) : x(cos(rad)), y(sin(rad)) {}
    static double dot(const Vector2& a, const Vector2& b) {
        return a.x * b.x + a.y * b.y;
    }
    static double angle(const Vector2& a, const Vector2& b) {
        return acos(dot(a, b) / a.length() / b.length());
    }
    static double cross(const Vector2& a, const Vector2& b) {
        return a.x * b.y - a.y * b.x;
    }
    static double area2(const Vector2& a, const Vector2& b, const Vector2& c) {
        return cross(b - a, c - a);
    }

    double length() const { return sqrt(x * x + y * y); }
    double lengthSq() const { return x * x + y * y; }
    double getRad() const { return atan2(y, x); }
    Vector2 rotate(double rad) const {
        return Vector2(x * cos(rad) - y * sin(rad),
                       x * sin(rad) + y * cos(rad));
    }
    Vector2 unit() const {
        double l = this->length();
        return Vector2(x / l, y / l);
    }
    Vector2 normal() const {
        double l = this->length();
        return Vector2(-y / l, x / l);
    }

    bool operator<(const Vector2& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
    bool operator==(const Vector2& other) const {
        return !dcmp(x - other.x) && !dcmp(y - other.y);
    }

    Vector2& operator+=(const Vector2& vec) {
        this->x += vec.x, this->y += vec.y;
        return *this;
    }
    Vector2 operator+(const Vector2& vec) const {
        return Vector2(this->x + vec.x, this->y + vec.y);
    }
    Vector2& operator-=(const Vector2& vec) {
        this->x -= vec.x, this->y -= vec.y;
        return *this;
    }
    Vector2 operator-(const Vector2& vec) const {
        return Vector2(this->x - vec.x, this->y - vec.y);
    }
    Vector2& operator*=(double v) {
        this->x *= v, this->y *= v;
        return *this;
    }
    Vector2 operator*(double v) const {
        return Vector2(this->x * v, this->y * v);
    }
    Vector2& operator/=(double v) {
        this->x /= v, this->y /= v;
        return *this;
    }
    Vector2 operator/(double v) const {
        return Vector2(this->x / v, this->y / v);
    }
};

struct Line {
    Vector2 p, d;
    Line() {}
    Line(const Vector2& p, const Vector2& dir) : p(p), d(dir) {}

    static Vector2 lineIntersection(const Line& l1, const Line& l2) {
        double t =
            Vector2::cross(l2.d, l1.p - l2.p) / Vector2::cross(l1.d, l2.d);
        return l1.p + l1.d * t;
    }

    static double distanceToLine(const Vector2& p, const Line& line) {
        return fabs(Vector2::cross(line.d, p - line.p) / line.d.length());
    }

    static Vector2 lineProjection(const Vector2& p, const Line& l) {
        return l.p +
               l.d * (Vector2::dot(l.d, p - l.p) / Vector2::dot(l.d, l.d));
    }
};

struct Segment {
    Vector2 p1, p2;
    Segment() {}
    Segment(const Vector2& p1, const Vector2& p2) : p1(p1), p2(p2) {}
    static double distanceToSegment(const Vector2& p, const Segment& seg) {
        if (seg.p1 == seg.p2) return (p - seg.p1).length();
        Vector2 ab = seg.p2 - seg.p1, ap = p - seg.p1, bp = p - seg.p2;
        if (dcmp(Vector2::dot(ab, ap)) < 0)
            return ap.length();
        else if (dcmp(Vector2::dot(ab, bp)) > 0)
            return bp.length();
        else
            return fabs(Vector2::cross(ab, ap) / ab.length());
    }
    static bool properIntersection(const Segment& s1, const Segment& s2) {
        double c1 = Vector2::cross(s1.p2 - s1.p1, s2.p1 - s1.p1),
               c2 = Vector2::cross(s1.p2 - s1.p1, s2.p2 - s1.p1),
               c3 = Vector2::cross(s2.p2 - s2.p1, s1.p1 - s2.p1),
               c4 = Vector2::cross(s2.p2 - s2.p1, s1.p2 - s2.p1);
        return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
    }
    static bool onSegment(const Vector2& p, const Segment& s) {
        return !dcmp(Vector2::cross(s.p1 - p, s.p2 - p)) &&
               dcmp(Vector2::dot(s.p1 - p, s.p2 - p)) < 0;
    }
};