#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

typedef unsigned long long ll;
using namespace std;
const int INF = 2147483647;
const int INF2 = 0x3f3f3f3f;
const ll INF64 = 1e18;
const double INFD = 1e30;
const double EPS = 1e-6;
const double PI = 3.14159265;
const ll MOD = 1e9 + 7;
// 读入优化
inline int read() {
    int X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch)) {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}

const int MAXN = 1005;

int n, m, k;

int fact[9];
int dx[] = {1, 0, 0, -1};
int dy[] = {0, -1, 1, 0};

int CASE = 1;

struct Line {
    int x;
    bool end;
    int y1, y2;
    bool operator<(const Line& b) const { return x < b.x; }
    Line(int x, bool end, int y1, int y2) : x(x), end(end), y1(y1), y2(y2) {}
};

struct Query {
    int x, y, h;
    Query() {}
    Query(int x, int y, int o) : x(x), y(y), h(o) {}
    bool operator<(const Query& q) const { return h < q.h; }
};

bool G[MAXN][MAXN];
int match[MAXN];
bool vis[MAXN];
int s, t;
bool dfs(int v) {
    for (int i = 1; i <= m; i++) {
        if (G[v][i] && !vis[i]) {
            vis[i] = true;
            if (match[i] == -1 || dfs(match[i])) {
                match[i] = v;
                return true;
            }
        }
    }
    return false;
}

int main() {
#ifdef LOCALLL
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int e;
    scanf("%d %d %d", &n, &m, &e);
    for (int i = 0; i < e; i++) {
        int u = read(), v = read();
        if (u <= 0 || v <= 0 || u > n || v > m) continue;
        G[u][v] = true;
    }
    int sum = 0;
    for (int i = 1; i <= m; i++) match[i] = -1;
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis[0]) * (m + 1));
        if (dfs(i)) sum++;
    }
    printf("%d", sum);
    return 0;
}
