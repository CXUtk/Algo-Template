#define ND(c) nodes[c]
#define self nodes[p]
struct DLX {
    struct Node {
        int L, R, U, D;
        int r, c;
    };
    int head[MAXN], sz[MAXN];
    int tot;
    Node nodes[MAXN * MAXN];
    int newNode(int r, int c) {
        ++tot;
        ND(tot).r = r, ND(tot).c = c;
        return tot;
    }

    void build(int rows, int cols) {
        for (int i = 0; i <= cols; i++) {
            ND(i).R = i + 1, ND(i).L = i - 1;
            ND(i).U = ND(i).D = i;
        }
        ND(0).L = cols, ND(cols).R = 0;
        tot = cols;
    }

    void link(int r, int c) {
        int p = newNode(r, c), lower = ND(c).D;
        sz[c]++, self.U = c, self.D = lower;
        ND(lower).U = ND(c).D = p;
        if (!head[r]) {
            head[r] = p;
            self.L = self.R = p;
        } else {
            int last = ND(head[r]).L;
            self.R = head[r], self.L = last;
            ND(last).R = p, ND(head[r]).L = p;
        }
    }
    void remove(int c) {
        ND(ND(c).L).R = ND(c).R, ND(ND(c).R).L = ND(c).L;
        for (int i = ND(c).D; i != c; i = ND(i).D) {
            for (int j = ND(i).R; j != i; j = ND(j).R) {
                ND(ND(j).U).D = ND(j).D, ND(ND(j).D).U = ND(j).U;
                sz[ND(j).c]--;
            }
        }
    }
    void recover(int c) {
        for (int i = ND(c).U; i != c; i = ND(i).U) {
            for (int j = ND(i).L; j != i; j = ND(j).L) {
                ND(ND(j).U).D = j, ND(ND(j).D).U = j;
                sz[ND(j).c]++;
            }
        }
        ND(ND(c).L).R = c, ND(ND(c).R).L = c;
    }
    int ans[MAXN], aptr;
    bool found;
    void solve() {
        if (found) return;
        if (!ND(0).R) {
            for (int i = 0; i < aptr; i++) {
                printf("%d ", ans[i]);
            }
            found = true;
            return;
        }
        int c = ND(0).R;
        for (int i = ND(0).R; i; i = ND(i).R)
            if (sz[i] < sz[c]) c = i;
        remove(c);
        for (int i = ND(c).D; i != c; i = ND(i).D) {
            ans[aptr++] = ND(i).r;
            for (int j = ND(i).R; j != i; j = ND(j).R) remove(ND(j).c);
            solve();
            if (found) return;
            for (int j = ND(i).L; j != i; j = ND(j).L) recover(ND(j).c);
            --aptr;
        }
        recover(c);
    }
};
