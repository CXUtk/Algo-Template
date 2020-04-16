#define ls nodes[p].ch[0]
#define rs nodes[p].ch[1]
#define fa nodes[p].father
#define get(s) nodes[s]
#define self nodes[p]
template <typename T>
struct Splay {
   public:
    struct Node {
        T val;
        int ch[2];
        int father;
        int sz;
        int cnt;
        Node() {}
        Node(T val, int f) : val(val), father(f), sz(1), cnt(1) {
            ch[0] = 0, ch[1] = 0;
        }
    };
    int tot, root;
    Node nodes[MAXN];
    Splay() { tot = 0; }

    // 插入一个数到splay平衡树中
    inline void insert(T val) { _insert(val); }
    inline void erase(T val) { _delete(root, val); }
    // 获取一个数的排名，如果这个数不在其中就输出应该处于的排名
    inline int rank(T val) {
        int r = _rank(root, val);
        splay(_lastins, 0);
        return r;
    }
    // 获取一个排名为k的数
    inline T kth(int k) {
        if (k <= 0 || k > get(root).sz) return -1;
        return get(_kth(root, k)).val;
    }
    inline T getPre(T val) { return get(_pre(root, val)).val; }
    inline T getNext(T val) { return get(_post(root, val)).val; }
    inline bool contains(T val) const { return _find(root, val); }
    inline int size() const { return root ? get(root).sz : 0; }

   private:
    int _lastins;

    inline void push_up(int p) {
        self.sz = self.cnt;
        if (ls) self.sz += get(ls).sz;
        if (rs) self.sz += get(rs).sz;
    }

    inline int newNode(T val, int f) {
        nodes[++tot] = Node(val, f);
        return tot;
    }

    inline bool _find(int p, T val) const {
        while (p && val != self.val) {
            int d = !(val < self.val);
            p = self.ch[d];
        }
        return p;
    }

    inline void erase(T val) {
        int p = root;
        while (p && self.val != val) {
            int d = !(val < self.val);
            p = self.ch[d];
        }
        if (!p) return;
        splay(p, 0);
        if (self.cnt > 1) {
            self.cnt--;
            return;
        }
        if (!ls) {
            if (rs) {
                get(rs).father = 0;
            }
            root = rs;
        } else {
            int rt = greatest(ls);
            splay(rt, p);
            get(rt).father = 0;
            get(rt).ch[1] = rs;
            if (rs) get(rs).father = rt;
            root = rt;
        }
        if (root) push_up(root);
    }

    void _insert(T val) {
        if (!root) {
            root = newNode(val, 0);
            return;
        }
        int p = root, f = 0;
        while (p && self.val != val) {
            f = p;
            p = self.ch[!(val < self.val)];
        }
        if (p) {
            self.cnt++;
        } else {
            p = newNode(val, f);
            get(f).ch[!(val < get(f).val)] = p;
        }
        splay(p, 0);
    }

    inline int greatest(int p) {
        while (rs) p = rs;
        return p;
    }

    int _pre(int p, T val) {
        int ans = p;
        while (p) {
            if (self.val < val) {
                ans = p;
                p = rs;
            } else {
                p = ls;
            }
        }
        splay(ans, 0);
        return ans;
    }

    int _post(int p, T val) {
        int ans = p;
        while (p) {
            if (self.val <= val) {
                p = rs;
            } else {
                ans = p;
                p = ls;
            }
        }
        splay(ans, 0);
        return ans;
    }

    int _rank(T val, int r) {
        int p = root, pre = 0;
        int res = 0;
        while (p) {
            pre = p;
            if (val <= self.val)
                p = ls;
            else {
                res += get(ls).sz + 1;
                p = rs;
            }
        }
        splay(pre, 0);
        return res + 1;
    }

    inline int _kth(int k, int r) {
        int p = root;
        while (p) {
            if (get(ls).sz + 1 == k) break;
            if (get(ls).sz + 1 > k)
                p = ls;
            else
                k -= get(ls).sz + 1, p = rs;
        }
        splay(p, 0);
        return p;
    }

    inline void rotate(int p) {
        int pf = fa;
        int gp = getf(fa);
        int d = identity(p);
        int d2 = identity(pf);
        int son = self.ch[!d];
        get(pf).ch[d] = son;
        if (son) {
            getf(son) = pf;
        }
        self.ch[!d] = pf;
        getf(pf) = p;
        fa = gp;
        get(gp).ch[d2] = p;
        push_up(pf);
        push_up(p);
    }
    inline int identity(int p) { return get(fa).ch[0] == p ? 0 : 1; }
    inline void splay(int p, int a) {
        while (fa != a) {
            if (getf(fa) == a) {
                rotate(p);
            } else if (identity(fa) == identity(p)) {
                rotate(fa);
                rotate(p);
            } else {
                rotate(p);
                rotate(p);
            }
        }
        if (!a) root = p;
    }
};