#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int INF = 2147483647;
const int INF2 = 0x3f3f3f3f;
typedef long long ll;

struct Edge {
    int fr, to, cap, flow, cost;
    Edge() = default;
    Edge(int from, int to, int capacity, int flow)
        : fr(from), to(to), cap(capacity), flow(flow), cost(0) {}
    Edge(int from, int to, int capacity, int flow, int w)
        : fr(from), to(to), cap(capacity), flow(flow), cost(w) {}
};
struct Dinic {
    int n, m;
    static const int MAXN = 10005;

    vector<Edge> edges;
    vector<int> G[MAXN];
    bool vis[MAXN];
    int layer[MAXN];
    int cur[MAXN];
    int s, t;

    inline void clear(int x) {
        for (int i = 0; i <= x; i++) {
            G[i].clear();
        }
        edges.clear();
    }

    inline void addedge(int u, int v, int cap) {
        edges.push_back(Edge(u, v, cap, 0));
        edges.push_back(Edge(v, u, 0, 0));
        m = edges.size();
        G[u].push_back(m - 2);
        G[v].push_back(m - 1);
    }

    inline bool layerize() {
        queue<int> Q;
        memset(vis, 0, sizeof(vis[0]) * (n + 1));
        Q.push(s);
        layer[s] = 0;
        vis[s] = true;
        while (!Q.empty()) {
            auto u = Q.front();
            Q.pop();
            for (auto e : G[u]) {
                Edge& edge = edges[e];
                if (!vis[edge.to] && edge.cap > edge.flow) {
                    vis[edge.to] = true;
                    layer[edge.to] = layer[u] + 1;
                    Q.push(edge.to);
                }
            }
        }
        return vis[t];
    }

    int dfs(int x, int a) {
        if (x == t || !a) return a;
        int flow = 0, f;
        int sz = G[x].size();
        for (int i = cur[x]; i < sz; i++) {
            Edge& e = edges[G[x][i]];
            if (layer[x] + 1 == layer[e.to] &&
                (f = dfs(e.to, min(a, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (!a) break;
            }
        }
        return flow;
    }

    int maxflow(int s, int t) {
        this->s = s;
        this->t = t;
        int flow = 0;
        while (layerize()) {
            memset(cur, 0, sizeof(cur[0]) * (n + 1));
            flow += dfs(s, INF);
        }
        return flow;
    }
};
