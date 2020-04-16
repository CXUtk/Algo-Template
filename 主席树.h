

#define chi(p, d) nodes[p].ch[d]
#define chd(p, d) nodes[nodes[p].ch[d]]
#define szp(p) nodes[p].sz
struct PSegTree {
    struct Node {
        int sz;
        int ch[2];
        Node() {}
        Node(int left, int right) : sz(0) { ch[0] = left, ch[1] = right; }
    };
    int roots[MAXN];
    Node nodes[MAXN * 20];
    int L, R, tot;

    int newNode(int l, int r) {
        ++tot;
        nodes[tot].ch[0] = l, nodes[tot].ch[1] = r;
        return tot;
    }
    void build(int l, int r) { L = l, R = r, tot = 0; }

    void insert(int pre, int cur, int v) {
        _insert(roots[pre], roots[cur], L, R, v);
    }
    void _insert(int pre, int& cur, int l, int r, int v) {
        cur = newNode(chi(pre, 0), chi(pre, 1));
        szp(cur) = szp(pre) + 1;
        if (l == r) return;
        int mid = (l + r) / 2;
        if (v <= mid)
            _insert(chi(pre, 0), chi(cur, 0), l, mid, v);
        else
            _insert(chi(pre, 1), chi(cur, 1), mid + 1, r, v);
    }

    int query(int l, int r, int k) {
        return _query(roots[l - 1], roots[r], L, R, k);
    }
    int _query(int lp, int rp, int l, int r, int k) {
        if (l == r) return l;
        int rank = szp(chi(rp, 0)) - szp(chi(lp, 0));
        int mid = (l + r) / 2;
        if (k <= rank)
            return _query(chi(lp, 0), chi(rp, 0), l, mid, k);
        else
            return _query(chi(lp, 1), chi(rp, 1), mid + 1, r, k - rank);
    }
};
struct PSegTree {
    struct Node {
        int sz;
        Node* ch[2];
        Node() : sz(0) { ch[0] = ch[1] = null; }
        Node(Node* left, Node* right) : sz(0) { ch[0] = left, ch[1] = right; }
    };
    static Node* null;
    Node* roots[MAXN];
    int L, R;

    void build(int l, int r) {
        null->ch[0] = null->ch[1] = null;
        L = l, R = r;
        for (int i = l - 1; i <= r; i++) roots[i] = null;
    }

    void insert(int pre, int cur, int v) {
        _insert(roots[pre], roots[cur], L, R, v);
    }
    void _insert(Node* pre, Node*& cur, int l, int r, int v) {
        cur = new Node(pre->ch[0], pre->ch[1]);
        cur->sz = pre->sz + 1;
        if (l == r) return;
        int mid = (l + r) / 2;
        if (v <= mid)
            _insert(pre->ch[0], cur->ch[0], l, mid, v);
        else
            _insert(pre->ch[1], cur->ch[1], mid + 1, r, v);
    }

    int query(int l, int r, int k) {
        return _query(roots[l - 1], roots[r], L, R, k);
    }
    int _query(Node* lp, Node* rp, int l, int r, int k) {
        if (l == r) return l;
        int rank = rp->ch[0]->sz - lp->ch[0]->sz;
        int mid = (l + r) / 2;
        if (k <= rank)
            return _query(lp->ch[0], rp->ch[0], l, mid, k);
        else
            return _query(lp->ch[1], rp->ch[1], mid + 1, r, k - rank);
    }
};
PSegTree::Node* PSegTree::null = new PSegTree::Node();