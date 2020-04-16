void extgcd(ll a, ll b, ll& d, ll& x, ll& y) {
    if (!b) {
        d = a;
        x = 1;
        y = 0;
    } else {
        extgcd(b, a % b, d, y, x);
        y -= x * (a / b);
    }
}

inline ll getInv(ll x, ll mod) {
    ll g, a, b;
    extgcd(x, mod, g, a, b);
    return (a % mod + mod) % mod;
}

int fastExp(ll x, ll p, int mod) {
    if (mod == 0) return 1;
    x %= mod;
    ll ans = 1;
    while (p) {
        if (p & 1) ans = ans * x % mod;
        x = x * x % mod;
        p >>= 1;
    }
    return ans;
}
struct BigInt {
    struct FFT {
        static void forward(int* a, int sz, int s) {
            for (int i = 0, j = 0; i < sz; i++) {
                if (i < j) swap(a[i], a[j]);
                int l = sz >> 1;
                while (l & j) j ^= l, l >>= 1;
                j ^= l;
            }
            for (int i = 2; i <= sz; i <<= 1) {
                int h = i / 2;
                ll wn = fastExp(3, (MOD - 1) / i, MOD);
                for (int j = 0; j < sz; j += i) {
                    ll w = 1, rt;
                    for (int k = 0; k < h; k++, w = w * wn % MOD) {
                        rt = w * a[j + k + h] % MOD;
                        a[j + k + h] = (a[j + k] - rt + MOD) % MOD;
                        a[j + k] = (a[j + k] + rt) % MOD;
                    }
                }
            }
        }

        static void fft(int* a, int sz) { forward(a, sz, 1); }
        static void ifft(int* a, int sz) {
            forward(a, sz, -1);
            reverse(a + 1, a + sz);
            int inv = getInv(sz, MOD);
            for (int i = 0; i < sz; i++) a[i] = (ll)a[i] * (ll)inv % MOD;
        }

        static void mul(int* A, int* B, int sz) {
            fft(A, sz), fft(B, sz);
            for (int i = 0; i < sz; i++) A[i] = A[i] * (ll)B[i] % MOD;
            ifft(A, sz);
        }
    };
    vector<int8_t> digits;
    BigInt() {}
    BigInt(int x) {
        if (!x) {
            digits.push_back(0);
            return;
        }
        while (x) digits.push_back(x % 10), x /= 10;
    }
    explicit BigInt(const string& str) { construct(str); }

    void construct(const string& str) {
        int sz = str.size();
        for (int i = 0; i < sz; i++) digits.push_back(str[i] - '0');
        reverse(digits.begin(), digits.end());
        trimZero();
    }

    BigInt& trimZero() {
        int i = size() - 1;
        for (; i >= 1; i--)
            if (digits[i]) break;
        if (i + 1 < size()) digits.resize(i + 1);
        return *this;
    }

    int size() const { return digits.size(); }

    int get(int x) const {
        if (x >= digits.size()) return 0;
        return digits[x];
    }

    pair<BigInt, BigInt> do_div(const BigInt& b) {
        BigInt ret;
        int sA = size(), sB = b.size();
        ret.digits.resize(sA - sB + 1);
        BigInt test(0);
        for (int j = sA - sB + 1; j < sA; j++) test.digits.push_back(digits[j]);
        for (int i = sA - sB; i >= 0; i--) {
            test = test + digits[i];
            int cnt = 0;
            while (!(test < b)) {
                test = test - b;
                cnt++;
            }
            ret.digits[i] = cnt;
            if (i) test.digits.insert(test.digits.begin(), 0);
            test.trimZero();
        }
        return {ret, test};
    }

    pair<BigInt, BigInt> do_div2(const BigInt& b) {
        ll l = 1, r = 1e18, ans = 1;
        while (l <= r) {
            ll mid = (l + r) / 2;
            BigInt t = b * mid;
            if (!(*this < t)) {
                ans = mid, l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return {ans, *this - b * ans};
    }

    BigInt operator+(const BigInt& b) const {
        BigInt ret;
        int sz = max(this->size(), b.size());
        ret.digits.resize(sz);
        int carry = 0;
        for (int i = 0; i < sz; i++) {
            int x = carry + get(i) + b.get(i);
            carry = x / 10, x %= 10;
            ret.digits[i] = x;
        }
        while (carry) {
            int x = carry;
            carry = x / 10;
            ret.digits.push_back(x % 10);
        }
        return ret;
    }

    BigInt operator*(const BigInt& b) const {
        BigInt ret;
        int szA = size(), szB = b.size();
        int sz = szA + szB - 1;
        ret.digits.resize(sz);
        static int A[(1 << 21) + 5], B[(1 << 21) + 5];
        int s = 1;
        while (s < sz) s <<= 1;
        memset(A, 0, sizeof(int) * s), memset(B, 0, sizeof(int) * s);
        for (int i = 0; i < szA; i++) A[i] = digits[i];
        for (int i = 0; i < szB; i++) B[i] = b.digits[i];
        FFT::mul(A, B, s);
        int carry = 0;
        for (int i = 0; i < szA + szB - 1; i++) {
            int x = A[i] + carry;
            ret.digits[i] = x % 10, carry = x / 10;
        }
        while (carry) {
            int x = carry;
            carry = x / 10;
            ret.digits.push_back(x % 10);
        }
        return ret;
    }

    BigInt operator-(const BigInt& b) {
        BigInt ret;
        int sz = size();
        ret.digits.resize(sz);
        int carry = 0;
        for (int i = 0; i < sz; i++) {
            int x = get(i) - b.get(i) + carry;
            carry = x < 0 ? -1 : 0;
            ret.digits[i] = (x + 10) % 10;
        }
        return ret.trimZero();
    }
    BigInt operator/(const BigInt& b) {
        if (*this < b) return BigInt(0);
        auto pair = do_div(b);
        return pair.first.trimZero();
    }
    BigInt operator%(const BigInt& b) {
        if (*this < b) return *this;
        auto pair = do_div(b);
        return pair.second.trimZero();
    }

    BigInt operator^(int p) {
        BigInt ans(1), x = *this;
        while (p) {
            if (p & 1) ans = x * ans;
            x = x * x, p >>= 1;
        }
        return ans;
    }

    BigInt operator*(ll b) const {
        BigInt ret;
        int sz = this->size();
        ll carry = 0;
        ret.digits.resize(sz);
        for (int i = 0; i < sz; i++) {
            ll x = digits[i] * b + carry;
            carry = x / 10, ret.digits[i] = x % 10;
        }
        while (carry) {
            ll x = carry;
            carry = x / 10;
            ret.digits.push_back(x % 10);
        }
        return ret;
    }

    BigInt operator/(int b) const {
        BigInt ret;
        ll tmp = 0;
        for (int i = size() - 1; i >= 0; i--) {
            tmp *= 10, tmp += digits[i];
            ret.digits.push_back(tmp / b);
            tmp = tmp - tmp / b * b;
        }
        if (ret.digits.empty()) ret.digits.push_back(0);
        reverse(ret.digits.begin(), ret.digits.end());
        return ret;
    }

    BigInt operator+(int b) const {
        BigInt ret;
        ret.digits.resize(size());
        int x = digits[0] + b, carry = x / 10, sz = size();
        ret.digits[0] = x % 10;
        for (int i = 1; i < sz; i++) {
            int x = carry + digits[i];
            carry = x / 10, ret.digits[i] = x % 10;
        }
        while (carry) {
            int x = carry;
            carry = x / 10;
            ret.digits.push_back(x % 10);
        }
        return ret;
    }

    bool operator<(const BigInt& b) const {
        if (size() < b.size()) return true;
        if (size() > b.size()) return false;
        int sz = size();
        for (int i = sz - 1; i >= 0; i--) {
            if (digits[i] < b.digits[i])
                return true;
            else if (digits[i] > b.digits[i])
                return false;
        }
        return false;
    }

    bool operator==(const BigInt& b) const {
        if (size() != b.size()) return false;
        int sz = size();
        for (int i = sz - 1; i >= 0; i--)
            if (digits[i] != b.digits[i]) return false;
        return true;
    }
    bool operator!=(const BigInt& b) const { return !((*this) == b); }
};

ostream& operator<<(ostream& os, const BigInt& x) {
    int i;
    for (i = x.size() - 1; i >= 1; i--)
        if (x.digits[i]) break;
    for (; i >= 0; --i) os << (char)(x.digits[i] + '0');
    return os;
}
istream& operator>>(istream& is, BigInt& x) {
    string s;
    cin >> s, x.construct(s);
    return is;
}