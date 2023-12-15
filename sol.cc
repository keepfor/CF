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
    set<pair<pair<int, int>, pair<int, int>>> vis;
    int x = 0, y = 0;
    cin >> s;
    int ans = 0;
    for (auto& i : s) {
      int px = x;
      int py = y;
      if (i == 'N') ++x;
      if (i == 'S') --x;
      if (i == 'E') ++y;
      if (i == 'W') --y;
      if (vis.emplace(min(make_pair(px, py), make_pair(x, y)),
                      max(make_pair(px, py), make_pair(x, y)))
              .second) {
        ans += 5;
      } else {
        ans += 1;
      }
    }
    cout << ans << '\n';
  };
  auto Solve = [&SolveOne]() -> void {
    int tt = 1;
    cin >> tt;
    while (tt--) {
      SolveOne();
    }
  };
  Solve();
  return 0;
}
