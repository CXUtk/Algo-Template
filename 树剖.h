#define foreach(G, u, i) for (int i = G.head[u]; i; i = G.pool[i].next)
struct AdjList {
    struct LLNode {
        int to, next;
    };
    int ndcnt;
    LLNode pool[MAXN << 1];
    int head[MAXN];
    inline void add(int u, int v) {
        pool[++ndcnt].to = v;
        pool[ndcnt].next = head[u];
        head[u] = ndcnt;
    }

    inline void clear() {
        ndcnt = 0;
        for (int i = 0; i <= n; i++) {
            head[i] = 0;
        }
    }
};

AdjList G;
int parent[MAXN], sz[MAXN], dep[MAXN], son[MAXN], top[MAXN];
int id[MAXN];
int w[MAXN];
int times;
void dfs1(int u, int pp) {
    parent[u] = pp;
    sz[u] = 1;
    int maxx = -1;
    foreach (G, u, i) {
        int v = G.pool[i].to;
        if (v != pp) {
            dep[v] = dep[u] + 1;
            dfs1(v, u);
            sz[u] += sz[v];
            if (sz[v] > maxx) {
                maxx = sz[v];
                son[u] = v;
            }
        }
    }
}

void dfs2(int u, int pp) {
    id[u] = ++times;
    w[times] = dep[u] - dep[parent[u]];
    top[u] = pp;
    if (!son[u]) return;
    dfs2(son[u], pp);
    foreach (G, u, i) {
        int v = G.pool[i].to;
        if (v != parent[u] && v != son[u]) {
            dfs2(v, v);
        }
    }
}

int LCA(int a, int b) {
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]]) swap(a, b);
        a = parent[top[a]];
    }
    int r = a;
    if (dep[a] > dep[b]) r = b;
    return r;
}