#include<bits/stdc++.h>

#ifdef LOCAL
#include"debug.h"
#else 
#define debug(...) 0
#endif

using namespace std;

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string t;
  int c = 1;
  while (getline(cin, t)) {
    t = to_string(c++) + ". " + t;
    cout << t << '\n';
  }
  return 0;
}
