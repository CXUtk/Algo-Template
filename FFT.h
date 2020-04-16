
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
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
    int rev[1 << 18];

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

struct FFTSlow {
    const double PI = 3.14159265358979323846;
    void inner_fft(Complex* arr, int len, bool forward) {
        if (len == 1) return;
        Complex* even = (Complex*)malloc(sizeof(Complex) * len / 2);
        Complex* odd = (Complex*)malloc(sizeof(Complex) * len / 2);
        for (int i = 0; i < len; i += 2) {
            even[i / 2] = arr[i];
            odd[i / 2] = arr[i + 1];
        }
        inner_fft(even, len / 2, forward);
        inner_fft(odd, len / 2, forward);
        Complex wn(cos(2 * PI / len),
                   (forward ? 1.0 : -1.0) * sin(2 * PI / len));
        Complex w(1, 0);
        for (int i = 0; i < len / 2; i++) {
            Complex t = w * odd[i];
            arr[i] = even[i] + t;
            arr[i + len / 2] = even[i] - t;
            w = w * wn;
        }
        free(odd);
        free(even);
    }

    void Forward(Complex* arr, int n) { inner_fft(arr, n, true); }

    void Inverse(Complex* arr, int n) { inner_fft(arr, n, false); }
};
