
bool vis[MAXN];
int primes[MAXN];
set<ll> pr;
mt19937 mt;
int tot;
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
        if (!vis[i]) primes[tot++] = i, pr.insert(i);
    }
}

inline ll modmul(ll a, ll b, ll p) {
    return (__int128_t)a * (__int128_t)b % p;
    a %= p;
    ll ans = 0;
    while (b) {
        if (b & 1) ans = (ans + a) % p;
        b >>= 1;
        a = (a + a) % p;
    }
    return ans;
}
// 带模数（慢速）乘的快速幂【毒瘤！】
inline ll fastExp(ll x, ll p, ll mod) {
    x %= mod;
    ll ans = 1;
    while (p) {
        if (p & 1) ans = modmul(ans, x, mod);
        x = modmul(x, x, mod) % mod;
        p >>= 1;
    }
    return ans;
}

inline bool miller_rabin(ll x) {
    if (x == 2) return true;
    if (pr.count(x)) return true;
    if (x < 2 || !(x & 1)) return false;
    ll pow = 0, u = x - 1;
    while (!(u & 1)) {
        pow++;
        u >>= 1;
    }
    for (int i = 0; i < 12; i++) {
        int p = primes[i];
        if (p >= x) break;
        ll v = fastExp(p, u, x);
        if (v == 1 || v == x - 1) continue;
        for (int i = 0; i < pow; i++) {
            ll t = modmul(v, v, x);
            if (t == 1 && v != 1 && v != x - 1) return false;
            v = t;
        }
        if (v != 1) return false;
    }
    return true;
}

inline ll f(ll x, ll c, ll p) { return (modmul(x, x, p) + c) % p; }

ll pollard_rho(ll x) {
    ll c = (ll)mt() % (x - 1) + 1LL;
    ll s = 0, t = 0, val = 1;
    for (int i = 1;; i <<= 1, s = t, val = 1) {
        for (int z = 1; z <= i; z++) {
            t = f(t, c, x);
            val = modmul(val, abs(t - s), x);
            if (!val) return x;
            if (!(z % 127)) {
                ll g = __gcd(val, x);
                if (g > 1) return g;
            }
        }
        ll g = __gcd(val, x);
        if (g > 1) return g;
    }
    return x;
}

ll maxFact;

void fact(ll x) {
    if (x <= maxFact || x < 2) return;
    if (miller_rabin(x)) {
        maxFact = max(maxFact, x);
        return;
    }
    ll p = x;
    while (p == x) p = pollard_rho(x);
    while (x % p == 0) x /= p;
    fact(x), fact(p);
}

int main() {
#ifdef LOCALLL
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    getprimes(1000000);
    cin.sync_with_stdio(false);
    int T;
    cin >> T;
    ll x;
    while (T--) {
        cin >> x;
        maxFact = 0;
        if (miller_rabin(x)) {
            cout << "Prime" << endl;
        } else {
            fact(x);
            cout << maxFact << endl;
        }
    }
    return 0;
}