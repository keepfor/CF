#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include"lib/debug.h"
#else
#define debug(...) 
#endif

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int TESTCASES = 1;
  cin >> TESTCASES;
  auto ask = [](int r, int c) -> int {
    cout << "? " << r << ' ' << c << endl;
    int x;
    cin >> x;
    return x;
  };
  while (TESTCASES--) {
    int n, m;
    cin >> n >> m;
    int a = ask(1, 1);
    int b = ask(n, m);
    int x, y;
    if (a + b == n - 1) {
      x = a + 1;
      y = ask(a + 1, 1) + 1;
    } else if (a + b == m - 1) {
      y = a + 1;
      x = ask(1, a + 1) + 1;
    } else {
      if (1 + a <= n and m - b >= 1 and ask(1 + a, m - b) == 0) {
        x = 1 + a;
        y = m - b;
      } else {
        x = n - b;
        y = 1 + a;
      }
    }
    cout << "! " << x << ' ' << y << endl;
  }
  return 0;
}
