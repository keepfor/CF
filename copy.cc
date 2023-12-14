#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

#define int long long

int32_t main() {
  auto SetIO = []() -> void { cin.tie(0)->sync_with_stdio(0); };
  SetIO();
  auto SolveOne = []() -> void {
    using ll = long long;
    int n;
    cin >> n;
    vector<vector<ll>> sum(1 + n, vector<ll>(31));
    for (int i = 1; i <= n; ++i) {
      int t;
      cin >> t;
      for (int j = 0; j < 31; ++j) {
        if ((t >> j) & 1) {
          sum[i][j] += 1ll;
        }
        sum[i][j] += sum[i - 1][j];
      }
    }

    auto get = [&](ll mid, ll l) -> ll {
      ll c = 0;
      for (int i = 0; i < 31; ++i) {
        int x = (sum[mid][i] - sum[l - 1][i]);
        if (x == (mid - l + 1)) {
          c ^= (1ll << i);
        }
      }
      return c;
    };
    int q;
    cin >> q;
    while (q--) {
      ll l, k;
      cin >> l >> k;
      int oril = l;
      ll r = n;
      if (get(l, l) < k) {
        cout << -1 << ' ';
        continue;
      }
      while (l != r) {
        ll mid = (1ll + l + r) / 2;
        assert(mid >= l);
        if (get(mid, oril) >= k) {
          l = mid;
        } else {
          r = mid - 1;
        }
      }
      cout << l << ' ';
    }
    cout << '\n';
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
