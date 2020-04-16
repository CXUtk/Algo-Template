#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
typedef long long ll;
using namespace std;

struct Complex {
    double real;
    double img;

    Complex() = default;
    Complex(double r, double i) : real(r), img(i) {}

    Complex& operator+=(const Complex& other) {
        real += other.real;
        img += other.img;
        return *this;
    }
    Complex& operator-=(const Complex& other) {
        real -= other.real;
        img -= other.img;
        return *this;
    }
    Complex& operator*=(const Complex& other) {
        double r = real, i = img;
        real = r * other.real - i * other.img;
        img = r * other.img + i * other.real;
        return *this;
    }
};

Complex operator+(const Complex& a, const Complex& b) {
    Complex ret = a;
    ret += b;
    return ret;
}

Complex operator-(const Complex& a, const Complex& b) {
    Complex ret = a;
    ret -= b;
    return ret;
}

Complex operator*(const Complex& a, const Complex& b) {
    Complex ret = a;
    ret *= b;
    return ret;
}

struct FFT {
    const double PI = 3.14159265358979323846;
    int rev[1 << 21];

    void inner_fft(Complex* arr, int len, bool forward) {
        for (int i = 0; i < len; i++) {
            if (i < rev[i]) {
                swap(arr[i], arr[rev[i]]);
            }
        }
        int s = (forward ? 1 : -1);
        for (int i = 1; i < len; i <<= 1) {
            Complex wn(cos(PI / i), s * sin(PI / i));
            int step = i << 1;
            for (int j = 0; j < len; j += step) {
                Complex w(1, 0);
                for (int k = 0; k < i; k++) {
                    Complex xx = arr[j + k];
                    Complex yy = w * arr[j + k + i];
                    arr[j + k] = xx + yy;
                    arr[j + k + i] = xx - yy;
                    w *= wn;
                }
            }
        }
    }

    void Preprocess(int n) {
        int l = 0;
        int k = 1;
        while (k < n) {
            k <<= 1;
            l++;
        }
        for (int i = 0; i < n; i++) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
        }
    }

    void Forward(Complex* arr, int n) { inner_fft(arr, n, true); }

    void Inverse(Complex* arr, int n) { inner_fft(arr, n, false); }
};

FFT fft;
Complex A[1 << 21];
Complex B[1 << 21];

struct BigInt {
    vector<int> digits;

    inline std::size_t size() const { return digits.size(); }

    void Print() const {
        for (int i = digits.size() - 1; i >= 0; i--) {
            printf("%d", digits[i]);
        }
    }

    inline void TrimZero() {
        for (int i = digits.size() - 1; i >= 1; i--) {
            if (digits[i] == 0) {
                digits.pop_back();
            } else
                break;
        }
    }

    BigInt() {
        digits.clear();
        digits.push_back(0);
    }

    BigInt(int x) {
        digits.clear();
        while (x) {
            digits.push_back(x % 10);
            x /= 10;
        }
        reverse(digits.begin(), digits.end());
    }
    BigInt(const char* str) {
        digits.clear();
        for (int i = 0; str[i]; i++) {
            digits.push_back(str[i] - '0');
        }
        reverse(digits.begin(), digits.end());
    }

    BigInt(const BigInt& other) {
        digits = vector<int>(other.digits.begin(), other.digits.end());
    }
    BigInt(const vector<int>& other) {
        digits.assign(other.begin(), other.end());
    }
    BigInt operator+(const BigInt& b) const {
        const BigInt* A = this;
        const BigInt* B = &b;
        if (this->size() < b.size()) {
            swap(A, B);
        }
        int carry = 0;
        int s = A->size();
        int sb = B->size();
        vector<int> tmp(s, 0);
        for (int i = 0; i < s; i++) {
            int c = A->digits[i] + (i >= sb ? 0 : B->digits[i]) + carry;
            carry = c / 10;
            c %= 10;
            tmp[i] = c;
        }
        if (carry) {
            tmp.push_back(carry);
        }
        return BigInt(tmp);
    }

    BigInt operator*(const BigInt& b) const {
        int n = this->size() + b.size();
        int lens = 1;
        while (lens < n) {
            lens <<= 1;
        }
        int SA = this->size();
        int SB = b.size();

        for (int i = 0; i < lens; i++) {
            A[i].real = (i >= SA ? 0.0 : digits[i]);
            A[i].img = 0.0;
            B[i].real = (i >= SB ? 0.0 : b.digits[i]);
            B[i].img = 0.0;
        }
        fft.Preprocess(lens);
        fft.Forward(A, lens);
        fft.Forward(B, lens);
        for (int i = 0; i <= lens; i++) {
            A[i] *= B[i];
        }
        fft.Inverse(A, lens);
        vector<int> ans;
        int carry = 0;
        for (int i = 0; i < lens; i++) {
            int c = (int)(A[i].real / lens + 0.5) + carry;
            carry = c / 10;
            ans.push_back(c % 10);
        }
        while (carry) {
            ans.push_back(carry % 10);
            carry /= 10;
        }
        BigInt ret(ans);
        ret.TrimZero();
        return ret;
    }

    BigInt operator/(int other) const {
        vector<int> ans;
        ll x = 0;
        int s = this->size();
        int z = 0;
        for (int i = s - 1; i >= 0; i--) {
            x = x * 10LL + (ll)digits[i];
            int t = x / other;
            if (t) z++;
            if (z == 0) continue;
            ans.push_back(t);
            x %= other;
        }
        if (ans.empty()) {
            ans.push_back(0);
        }
        reverse(ans.begin(), ans.end());
        BigInt res(ans);
        res.TrimZero();
        return res;
    }

    BigInt& operator+=(const BigInt& other) {
        BigInt tmp = *this + other;
        digits.assign(tmp.digits.begin(), tmp.digits.end());
        return *this;
    }

    BigInt& operator+=(int other) {
        int s = this->size();
        int carry = other;
        for (int i = 0; i < s; i++) {
            int c = digits[i] + carry;
            carry = c / 10;
            digits[i] = c % 10;
        }
        while (carry) {
            digits.push_back(carry % 10);
            carry /= 10;
        }
        return *this;
    }

    bool operator>(const BigInt& other) {
        if (size() == other.size()) {
            for (int i = size(); i >= 0; i++) {
                if (digits[i] > other.digits[i]) {
                    return true;
                }
            }
            return false;
        }
        return size() > other.size();
    }
};