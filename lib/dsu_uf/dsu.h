#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
// TODO: Dynamic ModInt

template<typename T>
constexpr T power(T a, u64 b) {
    T res {1};
    for (; b != 0; b /= 2, a *= a) {
        if (b % 2 == 1) {
            res *= a;
        }
    }
    return res;
}

template<u32 P>
constexpr u32 mulMod(u32 a, u32 b) {
    return 1ULL * a * b % P;
}

template<u64 P>
constexpr u64 mulMod(u64 a, u64 b) {
    u64 res = a * b - u64(1.L * a * b / P - 0.5L) * P;
    res %= P;
    return res;
}

template<typename U, U P>
requires std::unsigned_integral<U>
struct ModIntBase {
public:
    constexpr ModIntBase() : x(0) {}
    
    template<typename T>
    requires std::integral<T>
    constexpr ModIntBase(T x_) : x(norm(x_ % T {P})) {}
    
    constexpr static U norm(U x) {
        if ((x >> (8 * sizeof(U) - 1) & 1) == 1) {
            x += P;
        }
        if (x >= P) {
            x -= P;
        }
        return x;
    }
    
    constexpr U val() const {
        return x;
    }
    
    constexpr ModIntBase operator-() const {
        ModIntBase res;
        res.x = norm(P - x);
        return res;
    }
    
    constexpr ModIntBase inv() const {
        return power(*this, P - 2);
    }
    
    constexpr ModIntBase &operator*=(const ModIntBase &rhs) & {
        x = mulMod<P>(x, rhs.val());
        return *this;
    }
    
    constexpr ModIntBase &operator+=(const ModIntBase &rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    
    constexpr ModIntBase &operator-=(const ModIntBase &rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    
    constexpr ModIntBase &operator/=(const ModIntBase &rhs) & {
        return *this *= rhs.inv();
    }
    
    friend constexpr ModIntBase operator*(ModIntBase lhs, const ModIntBase &rhs) {
        lhs *= rhs;
        return lhs;
    }
    
    friend constexpr ModIntBase operator+(ModIntBase lhs, const ModIntBase &rhs) {
        lhs += rhs;
        return lhs;
    }
    
    friend constexpr ModIntBase operator-(ModIntBase lhs, const ModIntBase &rhs) {
        lhs -= rhs;
        return lhs;
    }
    
    friend constexpr ModIntBase operator/(ModIntBase lhs, const ModIntBase &rhs) {
        lhs /= rhs;
        return lhs;
    }
    
    friend constexpr std::ostream &operator<<(std::ostream &os, const ModIntBase &a) {
        return os << a.val();
    }
    
    friend constexpr bool operator==(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() == rhs.val();
    }
    
    friend constexpr bool operator!=(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() != rhs.val();
    }
    
    friend constexpr bool operator<(ModIntBase lhs, ModIntBase rhs) {
        return lhs.val() < rhs.val();
    }
    
private:
    U x;
};

template<u32 P>
using ModInt = ModIntBase<u32, P>;

template<u64 P>
using ModInt64 = ModIntBase<u64, P>;

constexpr u32 P = 998244353;
using Z = ModInt<P>;
struct DSU {
    std::vector<int> f, siz;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};
struct Node {
    i64 num;
    i64 den;
    int i;
};

bool operator<(const Node &a, const Node &b) {
    return a.num * b.den < b.num * a.den;
}

void solve() {
    int N;
    std::cin >> N;
    
    std::vector<int> p(N + 1);
    for (int i = 1; i <= N; i++) {
        std::cin >> p[i];
    }
    std::vector<int> a(N + 1);
    for (int i = 1; i <= N; i++) {
        std::cin >> a[i];
    }
    
    std::priority_queue<Node> q;
    std::vector cnt(N + 1, 1);
    DSU dsu(N + 1);
    for (int i = 1; i <= N; i++) {
        q.push({a[i], 1, i});
    }
    
    i64 ans = 0;
    while (!q.empty()) {
        auto [num, den, i] = q.top();
        q.pop();
        
        if (dsu.find(i) != i || den != cnt[i]) {
            continue;
        }
        
        int x = dsu.find(p[i]);
        ans += 1LL * cnt[x] * a[i];
        cnt[x] += cnt[i];
        a[x] += a[i];
        dsu.merge(x, i);
        if (x > 0) {
            q.push({a[x], cnt[x], x});
        }
    }
    std::cout << Z(ans) / a[0] << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int T;
    std::cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}



#include <bits/stdc++.h>

struct DSU {
  std::vector<int> f, siz;
  DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
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
    f[y] = x;
    return true;
  }
  int size(int x) { return siz[leader(x)]; }
};

namespace push {
class Solver {
 public:
  void Main() const;

 private:
  void SetIO() const;
  void Run() const;
  void Solve() const;
};

struct DSU {
  std::vector<int> f, siz;
  vector<vector<int>> group;
  DSU(int n) : f(n), siz(n, 1) { 
    std::iota(f.begin(), f.end(), 0);
    group.resize(n);
    for (int i = 0; i < n; ++i) {
      group[i].push_back(i);
    }
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
    f[y] = x;
    return true;
  }

  bool unite_push(int x, int y) {
    x = leader(x);
    y = leader(y);
    if (x == y) return false;
    siz[x] += siz[y];
    f[y] = x;
    for (auto& i : group[y]) {
      group[x].push_back(i);
    }
    return true;
  }

  int size(int x) { return siz[leader(x)]; }
};

void Solver::Solve() const {
  int n, q;
  cin >> n >> q;
  DSU dsu(n);
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int u, v;
      cin >> u >> v;
      --u; --v;
      if (u > v) {
        swap(u, v);
      }
      dsu.unite_push(u, v);
      u = dsu.leader(u);
      auto& g = dsu.group[u];
      sort(g.rbegin(), g.rend());
      if (g.size() > 10) {
        g.resize(10);
      }
    } else {
      int v, k;
      cin >> v >> k;
      //debug(v, k);
      --v; --k;
      int ans = -2;
      v = dsu.leader(v);
      auto g = dsu.group[v];
      //debug(g, k);
      if (k < (int) g.size()) {
        ans = g[k];
      }
      cout << ans + 1 << '\n';
    }
  }
}

void Solver::Run() const {
  auto tt{1};
  // cin >> tt;
  while (tt--) {
    Solve();
  }
}

inline void Solver::SetIO() const { 
  cin.tie(0)->sync_with_stdio(0); 
}

void Solver::Main() const {
  SetIO();
  Run();
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}
}
