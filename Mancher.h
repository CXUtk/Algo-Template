struct Manacher {
    char str[MAXN * 2];
    int d[MAXN * 2];
    int sz;
    void build(char* text, int n) {
        str[0] = '$', str[1] = '#';
        sz = n;
        for (int i = 1; i <= sz; i++) {
            d[i * 2] = d[i * 2 + 1] = 1;
            str[i * 2] = text[i - 1];
            str[i * 2 + 1] = '#';
        }
        sz = sz * 2 + 1;
        str[sz + 1] = '@';
        int mid = 0, r = 0;
        int ans = 0;
        for (int i = 2; i <= sz; i++) {
            if (i <= r) d[i] = min(r - i, d[2 * mid - i]);
            while (str[i - d[i]] == str[i + d[i]]) ++d[i];
            if (i + d[i] > r) mid = i, r = i + d[i];
        }
    }
    pair<int, int> getPalin() {
        int l = 1, r = 1;
        for (int i = 2; i <= sz; i++) {
            if (i - d[i] == 0 || i + d[i] == sz + 1) {
                if (d[i] - 1 > r) {
                    l = (i - d[i]) / 2 + 1;
                    r = d[i] - 1;
                }
            }
        }
        return {l, r};
    }
};