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
    int n;
    cin >> n;
    vector<int> v(2 * n);
    for (auto& i : v) {
      cin >> i;
    }
    sort(v.begin(), v.end());
    int ans = 0;
    for (int i = 0; i < n; i += 2) {
      ans += v[i + 1] - v[i];
    }
    cout << ans << '\n';
  };
  auto Solve = [&SolveOne]() -> void {
    int t = 1;
    cin >> t;
    while (t--) {
      SolveOne();
    }
  };
  Solve();
  return 0;
}
