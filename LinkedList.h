#define get(p) nodes[p]
template <typename T>
struct LinkedList {
    struct Node {
        T val;
        int ch[2];
        Node() {}
        Node(T val) : val(val) { ch[0] = ch[1] = 0; }
    };

    Node nodes[MAXN * 2];
    int head, tail;
    LinkedList() { head = tail = tot = 0; }

    inline void clear() { head = tail = tot = 0; }
    inline bool empty() const { return !head || !tail; }
    inline void print() const {
        int p = head;
        while (p) {
            printf("%d ", get(p).val);
            p = get(p).ch[1];
        }
        printf("\n");
    }
    inline int push_back(T val) {
        int p = newNode(val);
        if (!head) {
            head = tail = p;
        } else {
            get(tail).ch[1] = p;
            get(p).ch[0] = tail;
            tail = p;
        }
        return p;
    }
    inline int push_front(T val) {
        int p = newNode(val);
        if (!head) {
            head = tail = p;
        } else {
            get(head).ch[0] = p;
            get(p).ch[1] = head;
            head = p;
        }
        return p;
    }
    inline T front() const { return get(head).val; }
    inline T back() const { return get(tail).val; }
    inline int insert_before(int q, T val) { return _insert(q, val, 0); }
    inline int insert_after(int q, T val) { return _insert(q, val, 1); }
    inline void pop_back() {
        erase(tail);
        tail = get(tail).ch[0];
    }
    inline void pop_front() {
        erase(head);
        head = get(head).ch[1];
    }
    inline void erase(int q) {
        if (get(q).ch[0]) {
            int l = get(q).ch[0];
            get(l).ch[1] = get(q).ch[1];
        }
        if (get(q).ch[1]) {
            int r = get(q).ch[1];
            get(r).ch[0] = get(q).ch[0];
        }
    }

   private:
    int tot;
    inline int newNode(T val) {
        nodes[++tot] = Node(val);
        return tot;
    }

    inline int _insert(int q, T val, int d) {
        int p = newNode(val);
        int prv = get(q).ch[0 ^ d];
        if (prv) {
            get(prv).ch[1 ^ d] = p;
            get(p).ch[0 ^ d] = prv;
        }
        get(p).ch[1 ^ d] = q;
        get(q).ch[0 ^ d] = p;
        if (q == head && !d) {
            head = p;
        } else if (q == tail && d) {
            tail = p;
        }
        return p;
    }
};
