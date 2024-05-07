#include <bits/stdc++.h>

constexpr int P = 1000000007;
using i64 = long long;
// assume -P <= x < 2P
int norm(int x) {
  if (x < 0) {
    x += P;
  }
  if (x >= P) {
    x -= P;
  }
  return x;
}
template <class T>
T power(T a, i64 b) {
  T res = 1;
  for (; b; b /= 2, a *= a) {
    if (b % 2) {
      res *= a;
    }
  }
  return res;
}
struct Z {
  int x;
  Z(int x = 0) : x(norm(x)) {}
  Z(i64 x) : x(norm(x % P)) {}
  int val() const { return x; }
  Z operator-() const { return Z(norm(P - x)); }
  Z inv() const {
    assert(x != 0);
    return power(*this, P - 2);
  }
  Z &operator*=(const Z &rhs) {
    x = i64(x) * rhs.x % P;
    return *this;
  }
  Z &operator+=(const Z &rhs) {
    x = norm(x + rhs.x);
    return *this;
  }
  Z &operator-=(const Z &rhs) {
    x = norm(x - rhs.x);
    return *this;
  }
  Z &operator/=(const Z &rhs) { return *this *= rhs.inv(); }
  friend Z operator*(const Z &lhs, const Z &rhs) {
    Z res = lhs;
    res *= rhs;
    return res;
  }
  friend Z operator+(const Z &lhs, const Z &rhs) {
    Z res = lhs;
    res += rhs;
    return res;
  }
  friend Z operator-(const Z &lhs, const Z &rhs) {
    Z res = lhs;
    res -= rhs;
    return res;
  }
  friend Z operator/(const Z &lhs, const Z &rhs) {
    Z res = lhs;
    res /= rhs;
    return res;
  }
  friend std::istream &operator>>(std::istream &is, Z &a) {
    i64 v;
    is >> v;
    a = Z(v);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const Z &a) {
    return os << a.val();
  }
};

template <typename T>
struct Fenwick {
  int n;
  std::vector<T> a;

  Fenwick(int n = 0) { init(n); }

  void init(int n) {
    this->n = n;
    a.assign(n, T());
  }

  void add(int x, T v) {
    for (int i = x + 1; i <= n; i += i & -i) {
      a[i - 1] += v;
    }
  }

  T sum(int x) {
    auto ans = T();
    for (int i = x; i > 0; i -= i & -i) {
      ans += a[i - 1];
    }
    return ans;
  }

  T rangeSum(int l, int r) { return sum(r) - sum(l); }

  int kth(T k) {
    int x = 0;
    for (int i = 1 << std::__lg(n); i; i /= 2) {
      if (x + i <= n && k >= a[x + i - 1]) {
        x += i;
        k -= a[x - 1];
      }
    }
    return x;
  }
};

struct Max {
  int v;
  Max(int x = -1E9) : v{x} {}

  Max &operator+=(Max a) {
    v = std::max(v, a.v);
    return *this;
  }
};

template <typename T>
struct Fenwick {
  int n;
  std::vector<T> a;

  Fenwick(int n_ = 0) { init(n_); }

  void init(int n_) {
    n = n_;
    a.assign(n, T{});
  }

  void add(int x, const T &v) {
    for (int i = x + 1; i <= n; i += i & -i) {
      a[i - 1] = a[i - 1] + v;
    }
  }

  T sum(int x) {
    T ans{};
    for (int i = x; i > 0; i -= i & -i) {
      ans = ans + a[i - 1];
    }
    return ans;
  }

  T rangeSum(int l, int r) { return sum(r) - sum(l); }

  int select(const T &k) {
    int x = 0;
    T cur{};
    for (int i = 1 << std::__lg(n); i; i /= 2) {
      if (x + i <= n && cur + a[x + i - 1] <= k) {
        x += i;
        cur = cur + a[x - 1];
      }
    }
    return x;
  }
};
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector<i64> s(n + 1);
  for (int i = 0; i < n; i++) {
    s[i + 1] = s[i] + a[i];
  }

  auto v = s;
  std::sort(v.begin(), v.end());

  Fenwick<Max> fen(n + 1);

  std::vector<int> dp(n + 1);
  for (int i = 0; i <= n; i++) {
    int x = std::lower_bound(v.begin(), v.end(), s[i]) - v.begin();
    if (i == 0) {
      dp[i] = 0;
    } else {
      dp[i] = std::max(dp[i - 1], i + fen.sum(x + 1).v);
    }
    fen.add(x, dp[i] - i);
  }

  std::cout << dp[n] << "\n";

  return 0;
}
/*
struct Fenwick {
    const int n;
    std::vector<T> a;
    Fenwick(int n) : n(n), a(n) {}
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    T sum(int x) {
        T ans = 0;
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    std::vector<i64> b(n + 1);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = n - 1; i > 0; i--) {
        a[i] -= a[i - 1];
    }

    for (int i = 1; i <= n; i++) {
        std::cin >> b[i];
        b[i] += b[i - 1];
    }

    std::vector<std::array<i64, 4>> qry(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        std::cin >> l >> r;
        l--;
        qry[i] = {b[l], l, r, i};
    }
    std::sort(qry.begin(), qry.end());

    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) { return b[i] < b[j]; });

    Fenwick<Z> sp(n), cp(n), sn(n), cn(n);
    for (int i = 0; i < n; i++) {
        sp.add(i, Z(b[i]) * a[i]);
        cp.add(i, a[i]);
    }
    std::vector<Z> ans(q);

    int j = 0;
    for (auto [v, l, r, i] : qry) {
        while (j < n && b[p[j]] <= v) {
            int k = p[j++];
            sp.add(k, -Z(b[k]) * a[k]);
            cp.add(k, -a[k]);
            sn.add(k, Z(b[k]) * a[k]);
            cn.add(k, a[k]);
        }

        ans[i] = sp.rangeSum(l, r) - sn.rangeSum(l, r) + (cn.rangeSum(l, r) -
cp.rangeSum(l, r)) * v;
    }

    for (auto x : ans) {
        std::cout << x << "\n";
    }

    return 0;
}
*/

namespace le {
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class Fenwick {
 public:
  vector<T> fenw;
  int n;

  Fenwick(int _n) : n(_n) { fenw.resize(n); }

  void modify(int x, T v) {
    while (x < n) {
      fenw[x] += v;
      x |= (x + 1);
    }
  }

  T get(int x) {
    T v{};
    while (x >= 0) {
      v += fenw[x];
      x = (x & (x + 1)) - 1;
    }
    return v;
  }
};

class Solution {
 public:
  vector<int> resultArray(vector<int> &v) {
    const int n = v.size();
    vector<int> ord(n);
    vector<int> sv = v;
    sort(sv.begin(), sv.end());
    for (int i = 0; i < n; ++i) {
      ord[i] = lower_bound(sv.begin(), sv.end(), v[i]) - sv.begin();
    }
    vector<int> a{ord[0]};
    vector<int> b{ord[1]};
    Fenwick<int> fa(n);
    Fenwick<int> fb(n);
    fa.modify(ord[0], 1);
    fb.modify(ord[1], 1);
    for (int i = 2; i < n; ++i) {
      int ga = fa.get(n - 1) - fa.get(ord[i]);
      int gb = fb.get(n - 1) - fb.get(ord[i]);
      if (ga > gb) {
        a.push_back(ord[i]);
        fa.modify(ord[i], 1);
      } else if (gb > ga) {
        b.push_back(ord[i]);
        fb.modify(ord[i], 1);
      } else {
        if (a.size() <= b.size()) {
          a.push_back(ord[i]);
          fa.modify(ord[i], 1);
        } else {
          b.push_back(ord[i]);
          fb.modify(ord[i], 1);
        }
      }
    }
    vector<int> ans;
    for (auto &i : a) {
      ans.push_back(sv[i]);
    }
    for (auto &i : b) {
      ans.push_back(sv[i]);
    }
    return ans;
  }
};
}  // namespace le
