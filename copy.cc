#include <bits/stdc++.h>

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

using namespace std;

void SolveOne() {
  using ll = long long;
  ll a, b;
  cin >> a >> b;
  if (a - b > 1) {
    cout << "NO\n";
    return;
  }
  ll c = a * a - b * b;
  for (ll i = 2; i * i <= c; ++i) {
    if (c % i == 0) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
};

void SolveAll() {
  int test_case_num = 1;
  cin >> test_case_num;
  while (test_case_num--) {
    SolveOne();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

int32_t main() {
  SetIO();
  SolveAll();
  return 0;
}
