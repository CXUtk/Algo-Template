struct BigIntLite {
    int digits[10];
    int sz;
    static const int COMPRESS = 100000000;
    BigIntLite(ll val) {
        sz = 0;
        while (val) {
            digits[sz++] = val % COMPRESS;
            val /= COMPRESS;
        }
    }

    BigIntLite(const string& str) {
        for (int i = str.size() - 1; i >= 0; i -= 8) {
            int c = 0;
            for (int j = i; j >= i - 7 && j >= 0; j--) {
                c *= 10;
                c += str[j] - '0';
            }
            digits[sz++] = c;
        }
    }

    BigIntLite() { sz = 1; }

    BigIntLite(const BigIntLite& other) {
        for (int i = 0; i < other.sz; i++) {
            digits[i] = other.digits[i];
        }
        sz = other.sz;
    }

    void print() const {
        vector<char> ans;
        for (int i = 0; i < sz; i++) {
            int t = digits[i];
            for (int j = 0; j < 8; j++) {
                ans.push_back(t % 10);
                t /= 10;
            }
        }

        for (int i = ans.size() - 1; i >= 1; i--) {
            if (ans[i] == 0) {
                ans.pop_back();
            } else
                break;
        }
        reverse(ans.begin(), ans.end());
        for (auto a : ans) {
            putc(a + '0', stdout);
        }
    }

    inline BigIntLite operator+(int num) const {
        BigIntLite tmp(*this);
        tmp.digits[0] += num;
        int carry = tmp.digits[0] / COMPRESS;
        tmp.digits[0] %= COMPRESS;
        int j = 1;
        while (carry) {
            if (j == tmp.sz) tmp.digits[tmp.sz++] = 0;
            tmp.digits[j] += carry;
            carry = tmp.digits[j] / COMPRESS;
            tmp.digits[j] %= COMPRESS;
        }
        return tmp;
    }

    inline BigIntLite operator+(const BigIntLite& num) const {
        BigIntLite tmp(0);
        const BigIntLite* other = nullptr;
        if (sz < num.sz)
            tmp = num, other = this;
        else
            tmp = *this, other = &num;
        int carry = 0;
        int sz = tmp.sz;
        int osz = other->sz;
        for (int i = 0; i < sz; i++) {
            tmp.digits[i] += (i >= osz ? 0 : other->digits[i]) + carry;
            carry = tmp.digits[i] / COMPRESS;
            tmp.digits[i] %= COMPRESS;
        }
        if (carry) {
            tmp.digits[tmp.sz++] = carry;
        }
        return tmp;
    }

    BigIntLite& operator+=(const BigIntLite& other) {
        BigIntLite tmp = *this + other;
        for (int i = 0; i < tmp.sz; i++) {
            digits[i] = tmp.digits[i];
        }
        sz = tmp.sz;
        return *this;
    }
};
