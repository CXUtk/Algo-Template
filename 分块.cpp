#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

typedef long long ll;
using namespace std;
const int INF = 2147483647;
const int INF2 = 0x3f3f3f3f;
const ll INF64 = 1e18;
const double INFD = 1e30;
const double EPS = 1e-6;
const double PI = 3.14159265;
const ll MOD = 1e8;

template <typename T>
inline T read() {
    T X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch)) {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}

const int MAXN = 1000005;
int n, m, k;
int CASE;
struct Block {
    int l, r, tag;
    int arr[1005];
};
Block blocks[1005];
int belong[MAXN];
void modify(int l, int r, int w) {
    int ls = min(r, blocks[belong[l]].r);
    for (int i = l; i <= ls; i++) {
        blocks[belong[l]].arr[i - blocks[belong[l]].l] += w;
    }
    for (int i = belong[l] + 1; i <= belong[r] - 1; i++) {
        blocks[i].tag += w;
    }
    if (belong[l] != belong[r]) {
        int rs = max(l, blocks[belong[r]].l);
        for (int i = r; i >= rs; i--) {
            blocks[belong[r]].arr[i - blocks[belong[r]].l] += w;
        }
        Block& br = blocks[belong[r]];
        sort(br.arr, br.arr + br.r - br.l + 1);
    }
}

int query(int l, int r, int w) {
    int res = 0;
    Block& bl = blocks[belong[l]];
    int ls = min(r, bl.r);
    for (int i = l; i <= ls; i++) {
        res += bl.arr[i - bl.l] + bl.tag >= w;
    }
    for (int i = belong[l] + 1; i <= belong[r] - 1; i++) {
        Block& bc = blocks[i];
        res += bc.r - bc.l + 1 -
               (lower_bound(bc.arr, bc.arr + bc.r - bc.l + 1, w - bc.tag) -
                bc.arr);
    }
    if (belong[l] != belong[r]) {
        Block& br = blocks[belong[r]];
        int rs = max(l, br.l);
        for (int i = r; i >= rs; i--) {
            res += br.arr[i - br.l] + br.tag >= w;
        }
    }
    return res;
}
int main() {
#ifdef LOCALLL
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    int B = (int)sqrt(n + log(m)) + 1;
    // 块数，向上取整
    int CNT = (n + B - 1) / B;
    for (int i = 1; i <= CNT; i++) {
        blocks[i].l = B * (i - 1) + 1;
        blocks[i].r = min(n, B * i);
    }
    int tot = 1;
    for (int i = 1; i <= CNT; i++) {
        for (int j = blocks[i].l; j <= blocks[i].r; j++) {
            blocks[i].arr[j - blocks[i].l] = read<int>();
            belong[tot] = i;
            tot++;
        }
    }
    for (int i = 1; i <= CNT; i++) {
        sort(blocks[i].arr, blocks[i].arr + blocks[i].r - blocks[i].l + 1);
    }
    while (m--) {
        char c;
        int l, r, w;
        scanf(" %c %d %d %d", &c, &l, &r, &w);
        if (c == 'A') {
            printf("%d\n", query(l, r, w));
        } else {
            modify(l, r, w);
        }
    }
    return 0;
}