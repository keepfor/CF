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
  DSU(int n, int x) : f(n), siz(n, 1) {
    std::iota(f.begin(), f.end(), 0), mn = mx = f;
    f.assign(n, x);
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
  bool merge(int x, int y, int z) {
    if (f[x] == z or f[y] == z) {
      return false;
    }
    x = leader(x);
    y = leader(y);
    if (x == z or y == z) {
      return false;
    }
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


void Solver::Solve() const {
  int n;
  cin >> n;
  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first;
    a[i].second = i;
  }
  sort(a.rbegin(), a.rend());
  DSU d(n, -1);
  vector<int> ans(n + 1);
  for (auto& [i, j] : a) {
    d.f[j] = j;
    if (j - 1 >= 0) {
      d.merge(j, j - 1, -1);
    }
    if (j + 1 < n) {
      d.merge(j, j + 1, -1);
    }
    int z = d.size(j);
    assert(z <= n);
    ans[z] = max(ans[z], i);
  }
  for (int i = n - 1; i >= 1; --i) {
    ans[i] = max(ans[i], ans[i + 1]);
  }
  for (int i = 1; i <= n; ++i) {
    cout << ans[i] << " \n"[i == n];
  }
}

void Solver::Run() const {
  auto tt{1};
  // cin >> tt;
  while (tt--) {
    Solve();
  }
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}