#include <algorithm>
#include <bitset>
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
using namespace std;
typedef long long ll;

const int INF = 2147483647;
const int INF2 = 0x3f3f3f3f;
const ll INF64 = 1e18;
const double INFD = 1e30;
const double EPS = 1e-6;
const double PI = 3.1415926;
const ll MOD = 1e9;
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

struct Edge {
    int to;
    int dis;
    Edge() = default;
    Edge(int to, int dis) : to(to), dis(dis) {}
    bool operator>(const Edge& b) const { return this->dis > b.dis; }
};

struct MinPQ {
   public:
    void push(const Edge& item) {
        heap[n + 1].to = item.to;
        heap[n + 1].dis = item.dis;
        n++;
        swim(n);
    }
    Edge top() const { return heap[1]; }
    void pop() {
        if (empty()) return;
        swap(heap[1], heap[n--]);
        sink(1);
    }
    bool empty() const { return n == 0; }
    MinPQ() { n = 0; }
    ~MinPQ() {}

    Edge heap[300005];
    int n;

    inline void swim(int k) {
        while (k > 1 && heap[k / 2] > heap[k]) {
            swap(heap[k / 2], heap[k]);
            k >>= 1;
        }
    }

    inline void sink(int k) {
        while ((k << 1) <= n) {
            int j = k << 1;
            if (j < n && heap[j] > heap[j + 1]) j++;
            if (!(heap[k] > heap[j])) break;
            swap(heap[k], heap[j]);
            k = j;
        }
    }
};

int n, m, k;
int CASE;
const int MAXN = 100005;
vector<Edge> edges[MAXN];
int dist[MAXN];
bool vis[MAXN];
MinPQ Q;
int main() {
#ifdef LOCALLL
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int s;
    scanf("%d %d %d", &n, &m, &s);
    for (int i = 0; i < m; i++) {
        int u = read();
        int v = read();
        int d = read();
        edges[u].push_back({v, d});
    }

    Q.push({s, 0});
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[s] = 0;
    while (!Q.empty()) {
        auto a = Q.top();
        Q.pop();
        if (vis[a.to]) continue;
        vis[a.to] = true;
        for (auto e : edges[a.to]) {
            int nextd = dist[a.to] + e.dis;
            if (dist[e.to] > nextd) {
                dist[e.to] = nextd;
                Q.push({e.to, dist[e.to]});
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", dist[i]);
    }
    return 0;
}