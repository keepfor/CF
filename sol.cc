#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

class Solver {
 public:
  inline void Main() const {
    SetIO();
    Run();
  }

 private:
  inline void SetIO() const { 
    cin.tie(0)->sync_with_stdio(0); 
  }
  void Solve() const;
  void Run() const;
};

using ll = long long;

struct DSU {
  std::vector<int> f, siz, mn, mx;
  DSU(int n) : f(n), siz(n, 1) {
    std::iota(f.begin(), f.end(), 0), mn = mx = f;
  }
  int leader(int x) {
    while (x != f[x]) x = f[x] = f[f[x]];
    return x;
  }
  bool same(int x, int y) { return leader(x) == leader(y); }
  bool merge(int x, int y) {
    x = leader(x);
    y = leader(y);
    if (x == y) return false;
    siz[x] += siz[y];
    mn[x] = std::min(mn[x], mn[y]);
    mx[x] = std::max(mx[x], mx[y]);
    f[y] = x;
    return true;
  }
  int size(int x) { return siz[leader(x)]; }
  int min(int x) { return mn[leader(x)]; }
  int max(int x) { return mx[leader(x)]; }
};

template <typename T>
T mod_inv_in_range(T a, T m) {
  // assert(0 <= a && a < m);
  T x = a, y = m;
  T vx = 1, vy = 0;
  while (x) {
    T k = y / x;
    y %= x;
    vy -= k * vx;
    std::swap(x, y);
    std::swap(vx, vy);
  }
  assert(y == 1);
  return vy < 0 ? m + vy : vy;
}

template <typename T>
T mod_inv(T a, T m) {
  a %= m;
  a = a < 0 ? a + m : a;
  return mod_inv_in_range(a, m);
}

template <int MOD_>
struct modnum {
  static constexpr int MOD = MOD_;
  static_assert(MOD_ > 0, "MOD must be positive");

 private:
  int v;

 public:
  modnum() : v(0) {}
  modnum(int64_t v_) : v(int(v_ % MOD)) {
    if (v < 0) v += MOD;
  }
  explicit operator int() const { return v; }
  friend std::ostream& operator<<(std::ostream& out, const modnum& n) {
    return out << int(n);
  }
  friend std::istream& operator>>(std::istream& in, modnum& n) {
    int64_t v_;
    in >> v_;
    n = modnum(v_);
    return in;
  }

  friend bool operator==(const modnum& a, const modnum& b) {
    return a.v == b.v;
  }
  friend bool operator!=(const modnum& a, const modnum& b) {
    return a.v != b.v;
  }

  modnum inv() const {
    modnum res;
    res.v = mod_inv_in_range(v, MOD);
    return res;
  }
  friend modnum inv(const modnum& m) { return m.inv(); }
  modnum neg() const {
    modnum res;
    res.v = v ? MOD - v : 0;
    return res;
  }
  friend modnum neg(const modnum& m) { return m.neg(); }

  modnum operator-() const { return neg(); }
  modnum operator+() const { return modnum(*this); }

  modnum& operator++() {
    v++;
    if (v == MOD) v = 0;
    return *this;
  }
  modnum& operator--() {
    if (v == 0) v = MOD;
    v--;
    return *this;
  }
  modnum& operator+=(const modnum& o) {
    v -= MOD - o.v;
    v = (v < 0) ? v + MOD : v;
    return *this;
  }
  modnum& operator-=(const modnum& o) {
    v -= o.v;
    v = (v < 0) ? v + MOD : v;
    return *this;
  }
  modnum& operator*=(const modnum& o) {
    v = int(int64_t(v) * int64_t(o.v) % MOD);
    return *this;
  }
  modnum& operator/=(const modnum& o) { return *this *= o.inv(); }

  friend modnum operator++(modnum& a, int) {
    modnum r = a;
    ++a;
    return r;
  }
  friend modnum operator--(modnum& a, int) {
    modnum r = a;
    --a;
    return r;
  }
  friend modnum operator+(const modnum& a, const modnum& b) {
    return modnum(a) += b;
  }
  friend modnum operator-(const modnum& a, const modnum& b) {
    return modnum(a) -= b;
  }
  friend modnum operator*(const modnum& a, const modnum& b) {
    return modnum(a) *= b;
  }
  friend modnum operator/(const modnum& a, const modnum& b) {
    return modnum(a) /= b;
  }
};

using num = modnum<998244353>;

vector<num> fact, ifact;

void init() {
  int N = 1100000;
  fact = {1};
  for (int i = 1; i < N; i++) fact.push_back(i * fact[i - 1]);
  ifact.resize(N);
  ifact.back() = 1 / fact.back();
  for (int i = N - 1; i > 0; i--) ifact[i - 1] = i * ifact[i];
}

num ncr(int n, int k) {
  if (k < 0 || k > n) return 0;
  return fact[n] * ifact[k] * ifact[n - k];
}


num p(num x, int y) {
  num z = 1;
  while (y) {
    if (y & 1) {
      z = z * x;
    }
    x = x * x;
    y >>= 1;
  }
  return z;
}

void Solver::Solve() const {
  int n;
  cin >> n;
  vector<int> a(n), b(n);
  for (auto& i : a) {
    cin >> i;
    --i;
  }
  for (auto& i : b) {
    cin >> i;
    --i;
  }
  DSU d(n);
  for (int i = 0; i < n; ++i) {
    d.merge(a[i], b[i]);
  }
  vector<int> cnt(n);
  for (int i = 0; i < n; ++i) {
    ++cnt[d.leader(a[i])];
  }
  for (int i = 0; i < n; ++i) {
    if (cnt[i] > d.size(i)) {
      cout << 0 << '\n';
      return;
    }
  }
  num ans = 1;
  int g = 0;
  for (int i = 0; i < n; ++i) {
    g += d.leader(i) == i;
    if (a[i] == b[i]) {
      ans *= n;
      --g;
    }
  }
  ans *= p(num(2), g);
  cout << ans << '\n';
}

void Solver::Run() const {
  auto tt{1};
  cin >> tt;
  while (tt--) {
    Solve();
  }
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}
