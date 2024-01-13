#include <bits/stdc++.h>

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

using namespace std;

void SolveOne() {
  int r, d;
  cin >> r >> d;
  int n;
  cin >> n;
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    int c;
    cin >> c;
    double di = sqrt(x * x + y * y);
    if (di - c - (r - d) >= 0 and di + c <= r) {
      ++ans;
    }
  }
  cout << ans << '\n';
};

void SolveAll() {
  int test_case_num = 1;
  // cin >> test_case_num;
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