#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

class Solver {
 public:
  void Main() const;

 private:
  void SetIO() const;
  void Run() const;
  void Solve() const;
};

struct union_find {
  vector<int> parent;
  vector<int> size;
  int components = 0;

  union_find(int n = -1) {
    if (n >= 0) init(n);
  }

  void init(int n) {
    parent.resize(n + 1);
    size.assign(n + 1, 1);
    components = n;

    for (int i = 0; i <= n; i++) parent[i] = i;
  }

  int find(int x) { return x == parent[x] ? x : find(parent[x]); }

  bool unite(int x, int y) {
    x = find(x);
    y = find(y);

    if (x == y) return false;

    if (size[x] < size[y]) swap(x, y);

    parent[y] = x;
    size[x] += size[y];
    components--;
    return true;
  }
};

void Solver::Solve() const {
  int n, m;
  cin >> n >> m;
  const int mxd = 10;
  vector<vector<vector<pair<int, int>>>> p(mxd + 1, vector<vector<pair<int, int>>>(mxd + 1, vector<pair<int, int>>())); 
  for (int i = 0; i < m; ++i) {
    int a, d, k;
    cin >> a >> d >> k;
    if (k == 0) {
      continue;
    }
    p[d][a % d].emplace_back(a / d, a / d + k - 1);
  }
  int ans = n;
  union_find uf(n);
  for (int i = 1; i <= mxd; ++i) {
    for (int j = 0; j < i; ++j) {
      sort(p[i][j].begin(), p[i][j].end());
      int lst = -1;
      for (auto& [a, b] : p[i][j]) {
        for (int x = max(lst + 1, a); x <= b; ++x) {
          ans -= int(uf.unite(x * i + j, (x + 1) * i + j));
        }
        lst = max(lst, b);
      }
    }
  }
  cout << ans << '\n';
}

void Solver::Run() const {
  auto tt{1};
  cin >> tt;
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