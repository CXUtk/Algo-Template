struct Fraction {
    ll a, b;
    Fraction(ll a, ll b) : a(a), b(b) {}
    Fraction() {}
    void simplify() {
        ll g = __gcd(a, b);
        a /= g, b /= g;
    }
    Fraction operator-(const Fraction& other) const {
        ll gcd = __gcd(other.b, b);
        ll lcm = other.b / gcd * b;
        ll c = a * other.b / gcd;
        ll d = other.a * b / gcd;
        return Fraction(c - d, lcm);
    }

    bool operator<(const Fraction& other) const {
        ll gcd = __gcd(other.b, b);
        ll c = a * other.b / gcd;
        ll d = other.a * b / gcd;
        return c < d;
    }
    bool operator<=(const Fraction& other) const {
        ll gcd = __gcd(other.b, b);
        ll c = a * other.b / gcd;
        ll d = other.a * b / gcd;
        return c <= d;
    }
    bool operator==(const Fraction& other) const {
        ll gcd = __gcd(other.b, b);
        ll c = a * other.b / gcd;
        ll d = other.a * b / gcd;
        return c <= d;
    }
};