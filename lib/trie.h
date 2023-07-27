#include <bits/stdc++.h>

using namespace std;

class Trie {
 public:
  vector<vector<int>> trie;
  Trie() { trie.resize(1, vector<int>(2, -1)); }
  void add(int x) {}
};

class BinaryTrie : Trie {
 public:
  void add(int x) {
    int sz = 0;
    for (int i = 31; i >= 0; --i) {
      int b = (x >> i) & 1;
      if (trie[sz][b] == -1) {
        trie[sz][b] = (int)trie.size();
        trie.emplace_back(vector<int>(2, -1));
      }
      sz = trie[sz][b];
    }
  }

  // Find max xor.
  int query(int x) {
    int sz = 0;
    int ans = 0;
    for (int i = 31; i >= 0; --i) {
      int b = (x >> i) & 1;
      if (trie[sz][1 - b] != -1) {
        ans += 1 << i;
        sz = trie[sz][1 - b];
      } else {
        sz = trie[sz][b];
      }
    }
    return ans;
  }
};

#ifdef Test
int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  BinaryTrie t;
  vector<int> a{3, 10, 5, 25, 2, 8};
  for (auto& i : a) {
    t.add(i);
  }
  int ans = 0;
  for (auto& i : a) {
    ans = max(ans, t.query(i));
  }
  cout << ans << '\n';
  return 0;
}
#endif
