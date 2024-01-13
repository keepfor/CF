#include <bits/stdc++.h>

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

using namespace std;

void SolveOne() {
  int n;
  cin >> n;
  vector<int> a(2 * n);
  for (auto& i : a) {
    cin >> i;
  }
  sort(a.begin(), a.end());
  if (a[n - 1] == a[n]) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
  }
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