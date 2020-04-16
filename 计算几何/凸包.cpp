#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int INF = 2147483647;
const int INF2 = 0x3f3f3f3f;
const ll INF64 = 1e18;
const double INFD = 1e30;
const double PI = 3.14159265;
const ll MOD = 1e9 + 7;
const double EPS = 1e-9;

template <typename T>
inline T read() {
    T X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch)) {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}

const int MAXN = 10005;
int n, m, k;
int CASE = 1;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

struct Point2 {
    double x, y;
    Point2() {}
    Point2(double x, double y) : x(x), y(y) {}

    void print() const { printf("%f %f", x, y); }
};

typedef Point2 Vector2;

void scanPoint(Point2& point) { scanf("%lf%lf", &point.x, &point.y); }

// 二维向量基本运算
Vector2 operator+(const Vector2& a, const Vector2& b) {
    return Vector2(a.x + b.x, a.y + b.y);
}
Vector2 operator-(const Vector2& a, const Vector2& b) {
    return Vector2(a.x - b.x, a.y - b.y);
}
Vector2 operator*(const Vector2& a, double b) {
    return Vector2(a.x * b, a.y * b);
}
Vector2 operator/(const Vector2& a, double b) {
    return Vector2(a.x / b, a.y / b);
}

// 浮点数精度比较
int dcmp(double x) {
    if (fabs(x) < EPS) return 0;
    return x < 0 ? -1 : 1;
}

bool operator<(const Point2& a, const Point2& b) {
    return dcmp(a.x - b.x) < 0 || (!dcmp(a.x - b.x) && dcmp(a.y - b.y) < 0);
}
bool operator==(const Point2& a, const Point2& b) {
    return !dcmp(a.x - b.x) && !dcmp(a.y - b.y);
}
double dot(const Vector2& a, const Vector2& b) { return a.x * b.x + a.y * b.y; }
double length(const Vector2& a) { return sqrt(dot(a, a)); }
double lengthSq(const Vector2& a) { return dot(a, a); }
double angle(const Vector2& a, const Vector2& b) {
    return acos(dot(a, b) / length(a) / length(b));
}
double cross(const Vector2& a, const Vector2& b) {
    return a.x * b.y - a.y * b.x;
}
double trianglearea2(const Vector2& a, const Vector2& b, const Vector2& c) {
    return cross(b - a, c - a);
}
Vector2 rotate(const Vector2& a, double rad) {
    return Vector2(a.x * cos(rad) - a.y * sin(rad),
                   a.x * sin(rad) + a.y * cos(rad));
}
double getRad(const Vector2& a) { return atan2(a.y, a.x); }
double getK(const Vector2& a) {
    if (!dcmp(a.x)) return 1.0 / 0.0;
    return a.y / a.x;
}
Vector2 radToUnit(double rad) { return Vector2(cos(rad), sin(rad)); }
Vector2 normalize(const Vector2& a) {
    double len = length(a);
    return a / len;
}
Vector2 normal(const Vector2& a) { return normalize(Vector2(-a.y, a.x)); }

Point2 st[MAXN];
Point2 points[MAXN];
int main() {
#ifdef LOCALLL
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int stp = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanPoint(points[i]);
    }
    sort(points, points + n);
    for (int i = 0; i < n; i++) {
        while (stp > 1 && dcmp(cross(st[stp - 1] - st[stp - 2],
                                     points[i] - st[stp - 1])) >= 0)
            stp--;
        st[stp++] = points[i];
    }
    stp = 0;
    for (int i = n - 1; i >= 0; i--) {
        while (stp > 1 && dcmp(cross(st[stp - 1] - st[stp - 2],
                                     points[i] - st[stp - 1])) >= 0)
            stp--;
        st[stp++] = points[i];
    }
    printf("%.2lf", ans);
    return 0;
}