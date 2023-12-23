#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

void Freopen() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
}

void SolveOne() {
  Freopen();
  int n, x;
  cin >> n >> x;
  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
    v[i] *= n - i;
  }
  sort(v.begin(), v.end());
  for (int i = 0; i < n; ++i) {
    if (x >= v[i]) {
      x -= v[i];
    } else {
      cout << i << '\n';
      return;
    }
  }
  cout << n << '\n';
};

void Solve() {
  int t = 1;
  while (t--) {
    SolveOne();
  }
}

void SetIO() { cin.tie(0)->sync_with_stdio(0); }

int32_t main() {
  SetIO();
  Solve();
  return 0;
}
