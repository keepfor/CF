#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

class Solver {
 public:
  void Main() const;

 private:
  void SetIO() const;
  void Run() const;
  void Solve() const;
};

template<typename T>
class MinTrie {
 public:
  struct Node {
    vector<int> next;
    bool word;
    int mn;
    Node() {
        next.resize(26, -1);
        word = false;
        mn = 1e9;
    }
  };
  vector<Node> trie;
  MinTrie() {
    trie.assign(1, Node());
  } 
  void insert(string s, T c) {
    int now = 0;
    for (auto& j : s) {
        int x = j - 'a';
        if (trie[now].next[x] == -1) {
            trie[now].next[x] = trie.size();
            trie.emplace_back(Node());
        }
        now = trie[now].next[x];
    }
    trie[now].word = true;
    trie[now].mn = min(trie[now].mn, c);
  }
};

class Solution {
public:
    int minimumCost(string s, vector<string>& a, vector<int>& c) {
        MinTrie<int> mt;
        const int m = a.size();
        for (int i = 0; i < m; ++i) {
            mt.insert(a[i], c[i]);
        }
        const int n = s.size();
        const int inf = 1e9;
        vector<int> dp(n + 1, inf);
        dp[0] = 0;
        for (int i = 0; i < n; ++i) {
            int now = 0;
            for (int j = i; j < n; ++j) {
                int y = s[j] - 'a';
                if (mt.trie[now].next[y] == -1) {
                    break;
                } 
                now = mt.trie[now].next[y]; 
                if (mt.trie[now].word) {
                    dp[j + 1] = min(dp[j + 1], dp[i] + mt.trie[now].mn);
                }

            }
        }
        return dp[n] >= inf ? -1 : dp[n];
    }
};

void Solver::Solve() const {
  using ll = long long;
  Solution s;
  string ss = "abcdef";
  vector<string> a{"abdef","abc","d","def","ef"};
  vector<int> c{100,1,1,10,5};
  debug(s.minimumCost(ss, a, c));
}

void Solver::Run() const {
  auto tt{1};
  // cin >> tt;
  while (tt--) {
    Solve();
  }
}

inline void Solver::SetIO() const { 
  cin.tie(0)->sync_with_stdio(0); 
}

void Solver::Main() const {
  SetIO();
  Run();
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}



