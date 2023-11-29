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
    using ll = long long;
    ll n, q;
    cin >> n >> q;
    vector<int> a(n);
    ll x = (1 + n) * n / 2;
    q %= (1 + n)
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
      x -= 1ll * a[i];
    }
    a.push_back(x);
    rotate(a.begin(), a.end() - q, a.end());
    for (int i = 0; i < n; ++i) {
      cout << a[i] << " \n"[i + 1 == n];
    }
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
