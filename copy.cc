#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

#include <bits/stdc++.h>

using namespace std;

template <class T>
struct Trie {
  vector<vector<int>> trie{vector<int>(10, -1)};

  void newNode() { trie.emplace_back(10, -1); }

  void add(string s) {
    int now = 0;
    for (auto& i : s) {
      int x = i - '0';
      if (trie[now][x] == -1) {
        trie[now][x] = trie.size();
        newNode();
      }
      now = trie[now][x];
    }
  }

  T lcp(string s) {
    int len = 0;
    int now = 0;
    for (auto& i : s) {
      int x = i - '0';
      if (trie[now][x] == -1) {
        break;
      }
      ++len;
      now = trie[now][x];
    }
    return len;
  }
};

class Solution {
 public:
  int longestCommonPrefix(vector<int>& v, vector<int>& b) {
    Trie<int> t;
    int ans = 0;
    for (auto& i : v) {
      t.add(to_string(i));
    }
    for (auto& i : b) {
      ans = max(ans, t.lcp(to_string(i)));
    }
    return ans;
  }
};

void SolveOne() {
  Solution s;
  vector<int> v{1, 3};
  vector<int> b{32, 22};
  debug(s.longestCommonPrefix(v, b));
};

void SolveAll() {
  auto t{1};
  // cin >> t;
  while (t--) {
    SolveOne();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

signed main() {
  SetIO();
  SolveAll();
  return 0;
}
