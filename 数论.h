#include <cmath>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
const int MAXN = 50000;

bool vis[MAXN];
vector<int> primes;
void sieve(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (vis[i]) continue;
        for (int j = i * i; j <= x; j += i) {
            vis[j] = true;
        }
    }
}
void getprimes(int x) {
    sieve(x);
    for (int i = 2; i <= x; i++) {
        if (!vis[i]) primes.push_back(i);
    }
}

int phi[MAXN];
void getphi(int x) {
    memset(phi, 0, sizeof(phi));
    phi[1] = 1;
    for (int i = 2; i <= x; i++) {
        if (!phi[i]) {
            for (int j = i; j <= x; j += i) {
                if (!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}

ll modmul(ll a, ll b, ll p) {
    a %= p;
    ll ans = 0;
    while (b) {
        if (b & 1) ans = (ans + a) % p;
        b >>= 1;
        a = (a + a) % p;
    }
    return ans;
}

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

ll choose(int n, int k) {
    return fact[n] * getInv(fact[k] * fact[n - k] % MOD, MOD) % MOD;
}

// Given: A list of reminder equation x = a_i (mod m_i)
ll crt(int len, int* a, int* m) {
    ll M = 1, x = 0;
    for (int i = 0; i < len; i++) M *= m[i];
    for (int i = 0; i < len; i++) {
        ll w = M / m[i];
        x += ((w * a[i]) % M) * getInv(w, m[i]) % M;
        x %= M;
    }
    return (x % M + M) % M;
}

// Given: a^x = b (mod p)
ll bsgs(int a, int b, int p) {
    if (a % p == 0 && b) return -1;
    ll m = (ll)sqrt(p + 0.5);
    ll invM = getInv(fastExp(a, m, p), p);
    // a^i = e[i] mod p
    map<int, int> x;
    x[1] = 0;
    ll base = 1;
    for (int i = 1; i < m; i++) {
        base = base * a % p;
        if (!x.count(base)) x[base] = i;
    }
    for (ll i = 0; i < p / m; i++) {
        if (x.count(b)) return i * m + x[b];
        b = b * invM % p;
    }
    return -1;
}
