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
  while (TESTCASES--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& i : a) {
      cin >> i;
    }
    sort(a.begin(), a.end());
    if (a[0] == a[n / 2 - 1] and a[n / 2] == a[n - 1] and a[n / 2] != a[n / 2 - 1]) {
      cout << "YES\n";
      cout << a[0] << ' ' << a[n / 2] << '\n';
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}
