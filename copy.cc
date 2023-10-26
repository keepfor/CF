#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int32_t main() {
  auto SetIO = []() -> void { cin.tie(0)->sync_with_stdio(0); };
  SetIO();
  auto SolveOne = []() -> void {
    const int n = 11;
    vector<int> v(n);
    for (auto& i : v) {
      i += rng() % 100;
    }
    debug(v);
    auto q = [&](int l, int r) -> int {
      int x = v[l];
      while (1) {
        while (v[l] < x) {
          ++l;
        }
        while (v[r] > x) {
          --r;
        }
        if (l >= r) {
          debug(l, r);
          return r;
        }
        swap(v[l], v[r]);
        debug(v);
        ++l;
        --r;
      };
    };
    int l = 0;
    int r = n - 1;
    int k = 2;
    while (l <= r) {
      int p = q(l, r);
      debug(p);
      if (p == k) {
        for (auto& i : v) {
          cout << i << ' ';
        }
        cout << '\n';
        break;
      } else if (p < k) {
        l = p + 1;
      } else {
        r = p - 1;
      }
    }
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
