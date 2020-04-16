#define foreach(G, u, i) for (int i = G.head[u]; i; i = G.pool[i].next)
struct AdjList {
    struct LLNode {
        int to, next;
    };
    int ndcnt;
    LLNode pool[MAXN << 2];
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
