#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

template <typename T>
class KMP {
 public:
  // template <typename T>
  vector<int> GetLps(T s) {
    vector<int> p(s.size());
    for (int i = 1, j = 0; i < s.size(); i++) {
      while (j and s[j] != s[i]) j = p[j - 1];
      if (s[j] == s[i]) j++;
      p[i] = j;
    }
    return p;
  }

  // template <typename T>
  vector<int> matching(T& s, T& t) {
    vector<int> p = GetLps(s), match;
    for (int i = 0, j = 0; i < t.size(); i++) {
      while (j and s[j] != t[i]) j = p[j - 1];
      if (s[j] == t[i]) j++;
      if (j == s.size()) match.push_back(i - j + 1), j = p[j - 1];
    }
    return match;
  }
};

class Solver {
 public:
  void Main() const;

 private:
  void SetIO() const;
  void Run() const;
  void Solve() const;
};

class Solution {
 public:
  int minValidStrings(vector<string>& w, string t) {
    const int m = t.size();
    KMP<string> kmp;
    vector<int> lps(m);
    for (auto& i : w) {
      vector<int> tlps = kmp.GetLps(i + "$" + t);
      for (int j = 0; j < m; ++j) {
        lps[j] = max(lps[j], tlps[(int)i.size() + 1 + j]);
      }
    }
    int ans = 0;
    int now = m - 1;
    while (now >= 0) {
      if (lps[now] == 0) {
        return -1;
      }
      ++ans;
      now -= lps[now];
    }
    return ans;
  }
};

void Solver::Solve() const {
  using ll = int64_t;
  Solution so;
  vector<string> a{"abc", "aaaaa", "bcdef"};
  string s = "aabcdabc";
  debug(so.minValidStrings(a, s));
  // Input: words = [], target = "aabcdabc"
}

void Solver::Run() const {
  auto tt{1};
  // cin >> tt;
  while (tt--) {
    Solve();
  }
}

inline void Solver::SetIO() const { cin.tie(0)->sync_with_stdio(0); }

void Solver::Main() const {
  SetIO();
  Run();
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}