#include<bits/stdc++.h>
using namespace std;
int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    string s;
    cin >> s;
    int ans = (int) s.size();
    int a = 0, b = 0;
    for (auto &i : s) {
      if (i == 'A') {
        ++a;
      } else {
        if (a > 0) {
          --a;
          ans -= 2;
        } else {
          ++b;
        }
      }
    }
    ans -= b / 2 * 2;
    cout << ans << '\n';
  }
  return 0;
}
/*
 * n - deleted = shortest
 * bbb = b 
 * 3 => 1 => -2
 * bbbb => 0 => -4
 * - n / 2 * 2
 */
