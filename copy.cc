#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

template <int Size>
class Trie {
 public:
  Trie() { New(); }

  void Insert(string s, int idx) {
    int x = 0;
    id[0] = idx;
    for (auto& i : s) {
      int c = i - 'a';
      if (t[x][c] == -1) {
        t[x][c] = t.size();
        New();
      }
      id[t[x][c]] = idx;
      x = t[x][c];
    }
  }

  int GetLCSuf(string s) {
    int x = 0;
    for (auto& i : s) {
      int c = i - 'a';
      if (t[x][c] == -1) {
        return id[x];
      }
      x = t[x][c];
    }
    return id[x];
  }

 private:
  static constexpr int n = Size;

  void New() {
    t.emplace_back(vector<int>(n, -1));
    id.push_back(-1);
  }

  vector<vector<int>> t;
  vector<int> id;
};

class Solution {
 public:
  vector<int> stringIndices(vector<string>& v, vector<string>& q) {
    for (auto& i : v) {
      reverse(i.begin(), i.end());
    }
    for (auto& i : q) {
      reverse(i.begin(), i.end());
    }
    const int n = v.size();
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(),
         [&](auto a, auto b) -> bool { return v[a].size() < v[b].size(); });
    Trie<26> t;
    for (int i = n - 1; i >= 0; --i) {
      t.Insert(v[ord[i]], ord[i]);
    }
    const int m = q.size();
    vector<int> ans(m);
    for (int i = 0; i < m; ++i) {
      ans[i] = t.GetLCSuf(q[i]);
    }
    return ans;
  }
};

class Solver {
 public:
  inline void Main() const {
    SetIO();
    Run();
  }

 private:
  using ll = long long;

  inline void SetIO() const { cin.tie(0)->sync_with_stdio(0); }

  void Solve() const;
  void Run() const;
};

void Solver::Solve() const {
  Solution s;
  /*
   *
   *
Input: wordsContainer = [], wordsQuery = []
[], wordsQuery = []
   * */
  vector<string> a{"abcdefgh","poiuygh","ghghgh"};
  vector<string> b{"gh","acbfgh","acbfegh"};
  debug(s.stringIndices(a, b));
}

void Solver::Run() const {
  auto tt{1};
  // cin >> tt;
  while (tt--) {
    Solve();
  }
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}
