#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

using ll = long long;

void SolveOne() {
  int n;
  cin >> n;
  vector<ll> a(n);
  for (auto& i : a) {
    cin >> i;
  }
  sort(a.rbegin(), a.rend());
  ll ans = 0;
  ll x = a[0] + 1;
  for (auto& i : a) {
    --x;
    if (x > i) {
      x = i;
    }
    ans += max(0ll, x);
  }
  cout << ans << '\n';
}

void SolveAll() {
  int t = 1;
  // cin >> t;
  while (t--) {
    SolveOne();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

int32_t main() {
  SetIO();
  SolveAll();
  return 0;
}
