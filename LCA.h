vector<int> G[MAXN];
int parent[MAXN][20], dep[MAXN];
void dfs(int u, int p) {
    parent[u][0] = p;
    for (int i = 1; i <= 18; i++)
        parent[u][i] = parent[parent[u][i - 1]][i - 1];
    for (auto v : G[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}
int LCA(int u, int v) {
    if (dep[u] < dep[v]) std::swap(u, v);
    for (int i = 18; i >= 0; i--)
        if (dep[parent[u][i]] >= dep[v]) u = parent[u][i];
    if (u == v) return u;
    for (int i = 18; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i], v = parent[v][i];
        }
    }
    return parent[u][0];
}