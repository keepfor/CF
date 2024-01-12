#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

#include <bits/stdc++.h>

using namespace std;

void SolveOne(){

};

void SolveAll() {
  int TC = 1;
  // cin >> TC;
  while (TC--) {
    SolveOne();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

int32_t main() {
  SetIO();
  SolveAll();
  return 0;
}