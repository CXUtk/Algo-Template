#define get(p) nodes[p]
#define child(p, c) nodes[p].ch[c]
#define fail(p) nodes[p].fail
template <typename T>
struct ACTrie {
    static const int ALPHABET_SIZE = 26;
    struct Node {
        int ch[ALPHABET_SIZE];
        int fail;
        bool leaf;
        T val;
        Node() {}
        Node(bool leaf) : leaf(leaf) {}
    };
    Node nodes[MAXN];
    int tot, root;
    ACTrie() { tot = root = 0; }
    inline int idx(char c) { return c - 'a'; }
    inline void insert(const char* str, T val) {
        int cur = root;
        for (int i = 0; str[i]; i++) {
            int c = idx(tolower(str[i]));
            if (c < 0 || c >= ALPHABET_SIZE) return;
            if (!child(cur, c)) child(cur, c) = newNode(false);
            cur = child(cur, c);
        }
        get(cur).leaf = true;
        get(cur).val += val;
    }

    inline void build() {
        queue<int> Q;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            int c = child(root, i);
            if (c) fail(c) = root, Q.push(c);
        }
        while (!Q.empty()) {
            int p = Q.front();
            Q.pop();
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                int u = child(p, i);
                if (u) {
                    fail(u) = child(fail(p), i);
                    Q.push(u);
                } else {
                    child(p, i) = child(fail(p), i);
                }
            }
        }
    }

    inline int count(const char* str) {
        int cur = root;
        int sum = 0;
        for (int i = 0; str[i]; i++) {
            int c = idx(tolower(str[i]));
            cur = child(cur, c);
            for (int t = cur; t && get(t).val != -1; t = fail(t)) {
                if (get(t).leaf) {
                    sum += get(t).val;
                    get(t).val = -1;
                }
            }
        }
        return sum;
    }

    inline void clear() {
        memset(nodes, 0, sizeof(nodes[0]) * (tot + 1));
        tot = root = 0;
    }

   private:
    int newNode(T val) { return ++tot; }
};

struct ACTrie {
    static const int ALPHABET_SIZE = 26;
    int ch[MAXN][ALPHABET_SIZE];
    int val[MAXN], fail[MAXN], last[MAXN];
    int dp[MAXN];
    int tot;

    int newNode() {
        int res = ++tot;
        val[tot] = 0;
        fail[tot] = last[tot] = 0;
        return res;
    }
    int idx(char c) { return c - 'a'; }
    void clear() {
        memset(ch, 0, sizeof(ch));
        memset(dp, 0, sizeof(dp));
        tot = 0;
    }

    void insert(const char* str, int id) {
        int u = 0;
        for (int i = 0; str[i]; i++) {
            int c = idx(str[i]);
            if (!ch[u][c]) ch[u][c] = newNode();
            u = ch[u][c];
        }
        if (val[u])
            uf.join(val[u], id);
        else
            val[u] = id;
    }

    void build() {
        queue<int> Q;
        fail[0] = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            int u = ch[0][i];
            if (u) {
                fail[u] = 0, Q.push(u), last[u] = 0;
            }
        }
        while (!Q.empty()) {
            int r = Q.front();
            Q.pop();
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                int u = ch[r][i];
                if (!u) {
                    ch[r][i] = ch[fail[r]][i];
                    continue;
                }
                Q.push(u);
                fail[u] = ch[fail[r]][i];
                last[u] = val[fail[u]] ? fail[u] : last[fail[u]];
            }
        }
    }

    void find(const char* str) {
        int u = 0;
        for (int i = 0; str[i]; i++) {
            int c = idx(str[i]);
            u = ch[u][c];
            if (val[u])
                cal(u);
            else if (last[u])
                cal(last[u]);
        }
    }

    void cal(int u) {
        if (!u) return;
        dp[val[u]]++;
        cal(last[u]);
    }
};