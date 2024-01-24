#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...) 7
#endif

#include <bits/stdc++.h>

using namespace std;

void SolveOne() {
  int n;
  string s;
  cin >> n >> s;
  s = "0" + s + "0";
  bool no = s.find("11") != string::npos;
  no |= s.find("000") != string::npos;
  if (no) {
    cout << "No\n";
    return;
  }
  cout << "Yes\n";
};

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
