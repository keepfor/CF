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

void Solver::Solve() const {
  int n;
  cin >> n;
  priority_queue<pair<int, int>> s;
  s.emplace(n - 1, 0);
  vector<int> ans(n);
  for (int i = 1; i <= n; ++i) {
    assert(s.size());
    auto [d, l] = s.top();
    l *= -1;
    int r = d + l;
    s.pop();
    int len = r - l + 1;
    int md;
    if (len & 1) {
      md = (r + l) / 2;
    } else {
      md = (r + l - 1) / 2;
    }
    assert(md >= 0 and md < n);
    ans[md] = i;
    if (md - 1 >= 0 and l <= md - 1) {
      s.emplace(md - 1 - l, -l);
    }
    if (md + 1 < n and md + 1 <= r) {
      s.emplace(r - (md + 1), -(md + 1));
    }
  }
  for (int i = 0; i < n; ++i) {
    cout << ans[i] << " \n"[i + 1 == n];
  }
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
