#include <random>
using namespace std;

mt19937 mt(19270817);
#define self nodes[p]
#define chi(p, d) nodes[p].ch[d]
#define chd(p, d) nodes[nodes[p].ch[d]]
struct Treap {
    struct Node {
        int v, sz, ch[2], p;
        Node() {}
        Node(int v) : v(v), sz(1), p(mt()) { ch[0] = ch[1] = 0; }
    };
    int root, tot;
    Node nodes[MAXN];
    int newNode(int v) {
        ++tot;
        nodes[tot] = Node(v);
        return tot;
    }
    void push_up(int p) { self.sz = p ? (1 + chd(p, 0).sz + chd(p, 1).sz) : 0; }
    int rank(int p) { return chd(p, 0).sz + 1; }

    void rotate(int& p, int d) {
        int t = chi(p, !d);
        chi(p, !d) = chi(t, d), chi(t, d) = p;
        push_up(p), push_up(t), p = t;
    }

    void insert(int& p, int v) {
        if (!p) return (void)(p = newNode(v));
        int d = self.v < v;
        insert(chi(p, d), v);
        if (self.p < chd(p, d).p) rotate(p, !d);
        push_up(p);
    }

    void erase(int& p, int v) {
        if (!p) return;
        if (self.v != v) return erase(chi(p, (self.v < v)), v), push_up(p);
        if (chi(p, 0) && chi(p, 1)) {
            int d = chd(p, 0).p < chd(p, 1).p;
            rotate(p, !d), erase(chi(p, !d), v);
        } else {
            p = (chi(p, 0)) ? chi(p, 0) : chi(p, 1);
        }
        push_up(p);
    }

    int kth(int p, int k) {
        int rk;
        while ((rk = rank(p)) != k) {
            if (rk > k)
                p = chi(p, 0);
            else
                k -= rk, p = chi(p, 1);
        }
        return self.v;
    }

    int rank(int p, int v) {
        int res = 1;
        while (p) {
            if (self.v < v)
                res += rank(p), p = chi(p, 1);
            else
                p = chi(p, 0);
        }
        return res;
    }

    int pre(int p, int v) {
        int res = 0;
        while (p) {
            if (self.v < v)
                res = p, p = chi(p, 1);
            else
                p = chi(p, 0);
        }
        return res ? nodes[res].v : v;
    }

    int post(int p, int v) {
        int res = 0;
        while (p) {
            if (v < self.v)
                res = p, p = chi(p, 0);
            else
                p = chi(p, 1);
        }
        return res ? nodes[res].v : v;
    }
};

mt19937 mt;
template <typename T>
struct Treap {
    struct Node {
        Node* ch[2];  // 0左， 1右
        T val;
        int sz, cnt, pri;
        Node() { ch[0] = ch[1] = nullptr, sz = cnt = val = pri = 0; }
        Node(T val) : val(val), sz(1), cnt(1), pri(mt()) {
            ch[0] = ch[1] = null;
        }
        void push_up() { sz = cnt + ch[0]->sz + ch[1]->sz; }
    };
    static Node* null;
    Node* root = null;

    void insert(T val) { _insert(root, val); }
    void _insert(Node*& p, T val) {
        if (p == null) {
            p = new Node(val);
        } else {
            if (p->val == val) {
                p->cnt++, p->push_up();
                return;
            }
            int d = !(val < p->val);
            _insert(p->ch[d], val);
            if (p->ch[d]->pri > p->pri) rotate(p, !d);
        }
        p->push_up();
    }

    void remove(T val) { _remove(root, val); }
    void _remove(Node*& p, T val) {
        if (p == null) return;  // 没找到这个元素，出错了
        if (p->val != val)
            return _remove(p->ch[!(val < p->val)], val), p->push_up();
        if (p->cnt > 1) {
            p->cnt--;
        } else {
            if (p->ch[0] != null && p->ch[1] != null) {
                int d = (p->ch[0]->pri > p->ch[1]->pri);
                rotate(p, d), _remove(p->ch[d], val);
            } else {
                Node* pre = p;
                p = (p->ch[0] == null) ? p->ch[1] : p->ch[0];
                delete pre;
            }
        }
        if (p != null) p->push_up();
    }

    T Kth(int k) { return _kth(root, k); }
    T _kth(Node* p, int k) {
        if (k <= p->ch[0]->sz) return _kth(p->ch[0], k);
        if (k <= p->ch[0]->sz + p->cnt)
            return p->val;
        else
            return _kth(p->ch[1], k - p->ch[0]->sz - p->cnt);
    }

    int rank(T val) { return _rank(root, val); }
    int _rank(Node* p, T val) {
        if (p == null) return 1;
        if (val == p->val) return p->ch[0]->sz + 1;
        if (val < p->val)
            return _rank(p->ch[0], val);
        else
            return _rank(p->ch[1], val) + p->ch[0]->sz + p->cnt;
    }

    T getPre(T val) {
        Node *p = root, *ans = null;
        while (p != null) {
            if (p->val < val)
                ans = p, p = p->ch[1];
            else
                p = p->ch[0];
        }
        return ans == null ? val : ans->val;
    }

    T getPost(T val) {
        Node *p = root, *ans = null;
        while (p != null) {
            if (val < p->val)
                ans = p, p = p->ch[0];
            else
                p = p->ch[1];
        }
        return ans == null ? val : ans->val;
    }

    void rotate(Node*& p, int d) {
        Node* child = p->ch[!d];
        p->ch[!d] = child->ch[d], child->ch[d] = p;
        p->push_up(), child->push_up();
        p = child;
    }
};
template <typename T>
typename Treap<T>::Node* Treap<T>::null = new Treap<T>::Node();