#ifndef CP
#define CP
#include<bits/stdc++.h>
using namespace std;
#endif

#ifdef LOCAL
#include"./lib/debug.h"
#else 
#define debug(...) 0
#endif

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  auto f = [](char **x, char **y) {
    char* t = *x;
    *x = *y;
    *y = t;
  };
  char *a = "123";
  char *b = "456";
  f(&a, &b);
  cout << a << '\n';
  cout << b << '\n';
  return 0;
}
