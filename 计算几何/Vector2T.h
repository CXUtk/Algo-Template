#include <cmath>
#include <cstdio>

template <typename T>
struct Vector2 {
    T x, y;
    Vector2() {}
    Vector2(T x, T y) : x(x), y(y) {}

    Vector2 operator+(const Vector2& o) { return Vector2(x + o.x, y + o.y); }
    Vector2 operator-(const Vector2& o) { return Vector2(x - o.x, y - o.y); }
    Vector2 operator*(double val) { return Vector2(x * val, y * val); }
    Vector2 operator*(int val) { return Vector2(x * val, y * val); }
    Vector2 operator/(double val) { return Vector2(x / val, y / val); }
    Vector2 operator/(int val) { return Vector2(x * val, y * val); }

    // 浮点数精度比较
    int dcmp(T x) {
        if (fabs(x) < EPS) return 0;
        return x < 0 ? -1 : 1;
    }

    // 坐标顺序
    bool operator<(const Vector2& b) const {
        return x < b.x || ((x == b.x) && (y < b.y));
    }

    bool operator==(const Vector2& b) {
        return !dcmp(x - b.x) && !dcmp(y - b.y);
    }

    T dot(const Vector2& b) const { return x * b.x + y * b.y; }
    T cross(const Vector2& b) const { return x * b.y - y * b.x; }
    double length() const { return sqrt(dot(*this)); }
    double lengthSq() const { return dot(*this); }
    Vector2 rotateBy(double rad) const {
        return Vector2(x * cos(rad) - y * sin(rad),
                       x * sin(rad) + y * cos(rad));
    }
    double getRad() const { return atan2(y, x); }
    double getK() {
        if (!dcmp(x)) return 1.0 / 0.0;
        return y / x;
    }

    Vector2 normalize() const {
        double len = this->length();
        return (*this) / len;
    }
    Vector2 normal(const Vector2& a) { return normalize(Vector2(-y, x)); }
};
template <>
int Vector2<int>::dcmp(int x) {
    if (x == 0) return 0;
    return x > 0 ? 1 : -1;
}
template <typename T>
double angle(const Vector2<T>& a, const Vector2<T>& b) {
    return acos(a.dot(b) / a.length() / b.length());
}
template <typename T>
double trianglearea2(const Vector2<T>& a, const Vector2<T>& b,
                     const Vector2<T>& c) {
    return (b - a).cross(c - a);
}

Vector2<double> radToUnit(double rad) {
    return Vector2<double>(cos(rad), sin(rad));
}