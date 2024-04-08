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
  vector<int> a(n);
  for (auto& i : a) {
    cin >> i;
  }
  vector<int> b(n);
  for (auto& i : b) {
    cin >> i;
  }
  set<pair<ll, ll>> vis;
  ll sum = 0;
  ll de = 0;
  for (int i = 0; i < n; ++i) {
    sum += a[i] - b[i];
    ll mx = a[i];
    ll mn = b[i];
    assert(b[i] <= a[i]);
    while (1) {
      auto it = vis.lower_bound({mn, mx});
      if (it != vis.end() and it->first <= mx) {
        mx = max(mx, it->second);
        vis.erase(it);
      } else {
        break;
      }
    }
    while (1) {
      auto it = vis.lower_bound({mn, mx});
      if (it != vis.begin() and prev(it)->second >= mn) {
        it = prev(it);
        mn = min(mn, it->first);
        mx = max(mx, it->second);
        vis.erase(it);
      } else {
        break;
      }
    }
    vis.emplace(mn, mx);
    de = max(de, mx - mn);
    cout << sum - de << " \n"[i + 1 == n];
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
