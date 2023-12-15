#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

int32_t main() {
  auto SetIO = []() -> void { cin.tie(0)->sync_with_stdio(0); };
  SetIO();
  auto SolveOne = []() -> void {
    int q;
    cin >> q;
    set<pair<int, int>> fi, la;
    int now = 1;
    while (q--) {
      int t;
      cin >> t;
      if (t == 1) {
        int m;
        cin >> m;
        fi.emplace(now, m);
        la.emplace(-m, now);
        ++now;
      } else if (t == 2) {
        auto x = *fi.begin();
        cout << x.first << ' ';
        fi.erase(x);
        la.erase({-x.second, x.first});
      } else {
        auto x = *la.begin();
        cout << x.second << ' ';
        fi.erase({x.second, -x.first});
        la.erase(x);
      }
    }
    cout << '\n';
  };
  auto Solve = [&SolveOne]() -> void {
    int tt = 1;
    while (tt--) {
      SolveOne();
    }
  };
  Solve();
  return 0;
}
