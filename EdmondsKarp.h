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

struct EdmondsKarp {
    int n, m;
    static const int MAXN = 10005;

    vector<Edge> edges;
    vector<int> G[MAXN];
    int minV[MAXN];
    int p[MAXN];
    bool inq[MAXN];
    int dist[MAXN];

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

    inline void addedgeC(int u, int v, int cap, int cost) {
        edges.push_back(Edge(u, v, cap, 0, cost));
        edges.push_back(Edge(v, u, 0, 0, -cost));
        m = edges.size();
        G[u].push_back(m - 2);
        G[v].push_back(m - 1);
    }

    bool bfs(int s, int t) {
        memset(minV, 0, sizeof(minV[0]) * (n + 1));
        queue<int> Q;
        Q.push(s);
        minV[s] = INF2;
        while (!Q.empty()) {
            auto u = Q.front();
            Q.pop();
            for (auto v : G[u]) {
                Edge& e = edges[v];
                if (!minV[e.to] && e.cap - e.flow) {
                    p[e.to] = v;
                    minV[e.to] = min(minV[u], e.cap - e.flow);
                    Q.push(e.to);
                }
            }
            if (minV[t]) break;
        }
        return minV[t];
    }

    bool BellmanFord(int s, int t) {
        memset(dist, 0x3f, sizeof(dist[0]) * (n + 1));
        memset(inq, 0, sizeof(inq[0]) * (n + 1));
        dist[s] = 0;
        inq[s] = true;
        p[s] = -1;
        minV[s] = INF2;
        queue<int> Q;
        Q.push(s);
        while (!Q.empty()) {
            auto u = Q.front();
            Q.pop();
            inq[u] = false;
            for (auto v : G[u]) {
                Edge& e = edges[v];
                if (e.cap > e.flow && dist[e.to] > dist[u] + e.cost) {
                    dist[e.to] = dist[u] + e.cost;
                    p[e.to] = v;
                    minV[e.to] = min(minV[u], e.cap - e.flow);
                    if (!inq[e.to]) {
                        Q.push(e.to);
                        inq[e.to] = true;
                    }
                }
            }
        }
        // 无法到达t点
        return dist[t] < INF2;
    }

    int maxflow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            int val = minV[t];
            for (int u = t; u != s; u = edges[p[u]].fr) {
                edges[p[u]].flow += val;
                edges[p[u] ^ 1].flow -= val;
            }
            flow += val;
        }
        return flow;
    }

    int minCostMaxFlow(int s, int t, ll& cost) {
        cost = 0;
        int flow = 0;
        while (BellmanFord(s, t)) {
            int f = minV[t];
            cost += (ll)f * (ll)dist[t];
            for (int u = t; u != s; u = edges[p[u]].fr) {
                edges[p[u]].flow += f;
                edges[p[u] ^ 1].flow -= f;
            }
            flow += f;
        }
        return flow;
    }
};