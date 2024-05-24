#include <bits/stdc++.h>
using namespace std;

class IsSubstring {
 public:
  template <typename STRING>  
  vector<int> z_algorithm(const STRING& s) {
    int n = int(s.size());
    if (n == 0) return {};
    vector<int> z(n);
    z[0] = 0;
    for (int i = 1, j = 0; i < n; i++) {
      int& k = z[i];
      k = (j + z[j] <= i) ? 0 : min(j + z[j] - i, z[i - j]);
      while (i + k < n && s[k] == s[i + k]) k++;
      if (j + z[j] < i + z[i]) j = i;
    }
    z[0] = n;
    return z;
  }
  #line 2 "library/string/is_substring.hpp"

  // 連続部分列に含むかどうか。z-algo で線形時間
  template <typename STRING>
  bool is_substring(STRING& S, STRING& T) {
    int n = int(S.size()), m = int(T.size());
    STRING ST;
    for (auto&& x: S) ST.push_back(x);
    for (auto&& x: T) ST.push_back(x);
    auto Z = z_algorithm(ST);
    for (int i = n; i < n + m; ++i) {
      if (Z[i] >= n) return true;
    }
    return false;
  }
};