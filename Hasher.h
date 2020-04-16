int base[MAXN][2];
struct Hasher {
    static const int MOD1 = 993244853;
    static const int MOD2 = 1e9 + 7;
    int pref[MAXN][2], suf[MAXN][2];
    int length;
    static void init() {
        base[0][0] = base[0][1] = 1;
        for (int i = 1; i <= MAXN - 1; i++)
            base[i][0] = (ll)base[i - 1][0] * 37 % MOD1;
        for (int i = 1; i <= MAXN - 1; i++)
            base[i][1] = (ll)base[i - 1][1] * 233 % MOD2;
    }
    void cal(const string& str) {
        length = str.size();
        for (int i = 1; i <= length; i++) {
            pref[i][0] =
                ((ll)pref[i - 1][0] + (ll)str[i - 1] * base[i][0]) % MOD1;
            pref[i][1] =
                ((ll)pref[i - 1][1] + (ll)str[i - 1] * base[i][1]) % MOD2;
        }
        for (int i = length; i >= 1; i--) {
            suf[i][0] =
                ((ll)suf[i + 1][0] + (ll)str[i - 1] * base[length - i + 1][0]) %
                MOD1;
            suf[i][1] =
                ((ll)suf[i + 1][1] + (ll)str[i - 1] * base[length - i + 1][1]) %
                MOD2;
        }
    }

    pair<int, int> get(int l, int r) {
        return (pair<int, int>){
            (int)(((ll)pref[r][0] - (ll)pref[l - 1][0] + MOD1) % MOD1),
            (int)(((ll)pref[r][1] - (ll)pref[l - 1][1] + MOD2) % MOD2)};
    }

    pair<int, int> get2(int l, int r) {
        return (pair<int, int>){
            (int)(((ll)suf[l][0] - (ll)suf[r + 1][0] + MOD1) % MOD1),
            (int)(((ll)suf[l][1] - (ll)suf[r + 1][1] + MOD2) % MOD2)};
    }

    bool samerev(int l1, int r1, int l2, int r2) {
        if (r1 - l1 != r2 - l2) return false;
        pair<int, int> h1 = get(l1, r1);
        pair<int, int> h2 = get2(l2, r2);
        if (l1 < length - r2 + 1) {
            h1.first = (ll)h1.first * base[length - r2 + 1 - l1][0] % MOD1;
            h1.second = (ll)h1.second * base[length - r2 + 1 - l1][1] % MOD2;
        } else if (l1 > length - r2 + 1) {
            h2.first = (ll)h2.first * base[l1 - (length - r2 + 1)][0] % MOD1;
            h2.second = (ll)h2.second * base[l1 - (length - r2 + 1)][1] % MOD2;
        }
        return h1 == h2;
    }

    bool isPalin(int l, int r) {
        if (l == r) return true;
        l++, r++;
        int len = r - l + 1;
        int mid = l + len / 2;
        if (len & 1) {
            return samerev(l, mid - 1, mid + 1, r);
        } else {
            return samerev(l, mid - 1, mid, r);
        }
    }
};