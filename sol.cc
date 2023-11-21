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
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> a(n);
    for (auto& i : a) {
      cin >> i;
    }
    sort(a.rbegin(), a.rend());
    if (x > y) {
      swap(x, y);
    }
    double xs = 0;
    double ys = 0;

    for (int i = 0; i < x + y; ++i) {
      if (i < x) {
        xs += a[i];
      } else {
        ys += a[i];
      }
    }
    xs /= x;
    ys /= y;
    cout << fixed << setprecision(10) << xs + ys << '\n';
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
