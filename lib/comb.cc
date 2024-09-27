#include <bits/stdc++.h>

using i64 = long long;
template <class T>
constexpr T power(T a, i64 b) {
  T res = 1;
  for (; b; b /= 2, a *= a) {
    if (b % 2) {
      res *= a;
    }
  }
  return res;
}

template <int P>
struct MInt {
  int x;
  constexpr MInt() : x{} {}
  constexpr MInt(i64 x) : x{norm(x % P)} {}

  constexpr int norm(int x) const {
    if (x < 0) {
      x += P;
    }
    if (x >= P) {
      x -= P;
    }
    return x;
  }
  constexpr int val() const { return x; }
  explicit constexpr operator int() const { return x; }
  constexpr MInt operator-() const {
    MInt res;
    res.x = norm(P - x);
    return res;
  }
  constexpr MInt inv() const {
    assert(x != 0);
    return power(*this, P - 2);
  }
  constexpr MInt &operator*=(MInt rhs) {
    x = 1LL * x * rhs.x % P;
    return *this;
  }
  constexpr MInt &operator+=(MInt rhs) {
    x = norm(x + rhs.x);
    return *this;
  }
  constexpr MInt &operator-=(MInt rhs) {
    x = norm(x - rhs.x);
    return *this;
  }
  constexpr MInt &operator/=(MInt rhs) { return *this *= rhs.inv(); }
  friend constexpr MInt operator*(MInt lhs, MInt rhs) {
    MInt res = lhs;
    res *= rhs;
    return res;
  }
  friend constexpr MInt operator+(MInt lhs, MInt rhs) {
    MInt res = lhs;
    res += rhs;
    return res;
  }
  friend constexpr MInt operator-(MInt lhs, MInt rhs) {
    MInt res = lhs;
    res -= rhs;
    return res;
  }
  friend constexpr MInt operator/(MInt lhs, MInt rhs) {
    MInt res = lhs;
    res /= rhs;
    return res;
  }
  friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
    i64 v;
    is >> v;
    a = MInt(v);
    return is;
  }
  friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
    return os << a.val();
  }
  friend constexpr bool operator==(MInt lhs, MInt rhs) {
    return lhs.val() == rhs.val();
  }
  friend constexpr bool operator!=(MInt lhs, MInt rhs) {
    return lhs.val() != rhs.val();
  }
};

template <int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int P = 998244353;
using Z = MInt<P>;
std::vector<int> minp, primes;

void sieve(int n) {
  minp.assign(n + 1, 0);
  primes.clear();

  for (int i = 2; i <= n; i++) {
    if (minp[i] == 0) {
      minp[i] = i;
      primes.push_back(i);
    }

    for (auto p : primes) {
      if (i * p > n) {
        break;
      }
      minp[i * p] = p;
      if (p == minp[i]) {
        break;
      }
    }
  }
}

struct Comb {
  int n;
  std::vector<Z> _fac;
  std::vector<Z> _invfac;
  std::vector<Z> _inv;

  Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
  Comb(int n) : Comb() { init(n); }

  void init(int m) {
    if (m <= n) return;
    _fac.resize(m + 1);
    _invfac.resize(m + 1);
    _inv.resize(m + 1);

    for (int i = n + 1; i <= m; i++) {
      _fac[i] = _fac[i - 1] * i;
    }
    _invfac[m] = _fac[m].inv();
    for (int i = m; i > n; i--) {
      _invfac[i - 1] = _invfac[i] * i;
      _inv[i] = _invfac[i] * _fac[i - 1];
    }
    n = m;
  }

  Z fac(int m) {
    if (m > n) init(2 * m);
    return _fac[m];
  }
  Z invfac(int m) {
    if (m > n) init(2 * m);
    return _invfac[m];
  }
  Z inv(int m) {
    if (m > n) init(2 * m);
    return _inv[m];
  }
  Z binom(int n, int m) {
    if (n < m || m < 0) return 0;
    return fac(n) * invfac(m) * invfac(n - m);
  }
} comb;

/*
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    sieve(1000000);

    std::map<int, int> cnt;
    for (int i = 0; i < 2 * n; i++) {
        int a;
        std::cin >> a;
        cnt[a] += 1;
    }

    std::vector<Z> dp(n + 1);
    dp[0] = 1;
    for (auto [x, c] : cnt) {
        for (int i = n; i >= 0; i--) {
            if (i < n && minp[x] == x) {
                dp[i + 1] += dp[i] * comb.invfac(c - 1);
            }
            dp[i] *= comb.invfac(c);
        }
    }

    auto ans = dp[n] * comb.fac(n);
    std::cout << ans << "\n";

    return 0;
}
*/

#include <bits/stdc++.h>

using i64 = long long;

constexpr int dx[] = {0, 0, -1, 1};
constexpr int dy[] = {-1, 1, 0, 0};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int H, W, T;
    std::cin >> H >> W >> T;
    
    std::vector<std::string> S(H);
    for (int i = 0; i < H; i++) {
        std::cin >> S[i];
    }
    
    std::string s = "SoG";
    std::vector<std::pair<int, int>> p;
    for (auto c : s) {
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (S[i][j] == c) {
                    p.emplace_back(i, j);
                }
            }
        }
    }
    
    int N = p.size();
    
    std::vector dis(N, std::vector<int>(N));
    for (int i = 0; i < N; i++) {
        std::queue<std::pair<int, int>> q;
        std::vector d(H, std::vector(W, -1));
        q.push(p[i]);
        d[p[i].first][p[i].second] = 0;
        
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                
                if (0 <= nx && nx < H && 0 <= ny && ny < W && S[nx][ny] != '#' && d[nx][ny] == -1) {
                    d[nx][ny] = d[x][y] + 1;
                    q.emplace(nx, ny);
                }
            }
        }
        
        for (int j = 0; j < N; j++) {
            dis[i][j] = d[p[j].first][p[j].second];
        }
    }
    
    std::vector dp(1 << N, std::vector(N, T + 1));
    dp[1][0] = 0;
    
    int ans = -1;
    for (int s = 1; s < (1 << N); s += 2) {
        if (dp[s][N - 1] <= T) {
            ans = std::max(ans, __builtin_popcount(s) - 2);
        }
        for (int i = 0; i < N; i++) {
            if (s >> i & 1) {
                for (int j = 0; j < N; j++) {
                    if ((~s >> j & 1) && dis[i][j] != -1) {
                        dp[s | 1 << j][j] = std::min(dp[s | 1 << j][j], dp[s][i] + dis[i][j]);
                    }
                }
            }
        }
    }
    std::cout << ans << "\n";
    
    return 0;
}



#include <bits/stdc++.h>

using i64 = long long;
template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

constexpr i64 mul(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}
template<i64 P>
struct MLong {
    i64 x;
    constexpr MLong() : x{} {}
    constexpr MLong(i64 x) : x{norm(x % getMod())} {}
    
    static i64 Mod;
    constexpr static i64 getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(i64 Mod_) {
        Mod = Mod_;
    }
    constexpr i64 norm(i64 x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr i64 val() const {
        return x;
    }
    explicit constexpr operator i64() const {
        return x;
    }
    constexpr MLong operator-() const {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MLong inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MLong &operator*=(MLong rhs) & {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MLong &operator+=(MLong rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MLong &operator-=(MLong rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MLong &operator/=(MLong rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MLong operator*(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MLong operator+(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MLong operator-(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MLong operator/(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MLong &a) {
        i64 v;
        is >> v;
        a = MLong(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MLong lhs, MLong rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MLong lhs, MLong rhs) {
        return lhs.val() != rhs.val();
    }
};

template<>
i64 MLong<0LL>::Mod = 1;

template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(i64 x) : x{norm(x % getMod())} {}
    
    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};

template<>
int MInt<0>::Mod = 1;

template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int P = 998244353;
using Z = MInt<P>;

struct Comb {
    int n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;
    
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() {
        init(n);
    }
    
    void init(int m) {
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }
    
    Z fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    Z invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    Z inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    Z binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string S;
    std::cin >> S;
    
    int N = S.size();
    
    int q = std::count(S.begin(), S.end(), '?');
    auto ans = power(Z(52), q);
    
    std::vector dp(N + 1, std::vector<Z>(3));
    dp[N][0] = 1;
    for (int i = N - 1; i >= 0; i--) {
        if (S[i] == '?') {
            dp[i][0] += dp[i + 1][0] * 26;
            dp[i][1] += dp[i + 1][0] * 26;
            dp[i][1] += dp[i + 1][1] * 26;
            dp[i][2] += dp[i + 1][1] * 26;
            dp[i][2] += dp[i + 1][2] * 52;
        } else if (std::islower(S[i])) {
            dp[i][0] += dp[i + 1][0];
            dp[i][2] += dp[i + 1][1];
            dp[i][2] += dp[i + 1][2];
        } else {
            dp[i][1] += dp[i + 1][0];
            dp[i][1] += dp[i + 1][1];
            dp[i][2] += dp[i + 1][2];
        }
    }
    
    bool vis[26] {};
    int cntv = 26;
    int cntq = 0;
    std::vector<Z> pw(N + 1);
    pw[0] = 1;
    for (int i = 1; i <= N; i++) {
        pw[i] = pw[i - 1] * 26;
    }
    for (int i = 0; i < N; i++) {
        if (std::islower(S[i])) {
            continue;
        }
        if (S[i] == '?') {
            Z res = 0;
            for (int j = 0; j <= std::min(cntq, cntv); j++) {
                res += comb.binom(cntq, j) * comb.binom(cntv, j) * comb.fac(j) * (26 - cntv + j) * pw[cntq - j];
            }
            ans -= res * dp[i + 1][2];
            cntq++;
        } else {
            if (vis[S[i] - 'A']) {
                Z res = 0;
                for (int j = 0; j <= std::min(cntq, cntv); j++) {
                    res += comb.binom(cntq, j) * comb.binom(cntv, j) * comb.fac(j) * pw[cntq - j];
                }
                ans -= res * dp[i + 1][2];
                break;
            }
            Z res = 0;
            for (int j = 0; j <= std::min(cntq - 1, cntv - 1); j++) {
                res += comb.binom(cntq, j + 1) * comb.binom(cntv - 1, j) * comb.fac(j + 1) * pw[cntq - j - 1];
            }
            ans -= res * dp[i + 1][2];
            vis[S[i] - 'A'] = true;
            cntv--;
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
