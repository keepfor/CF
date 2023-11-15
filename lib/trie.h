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

class TrieMaxXor {
public:
        vector<int> cnt;
        vector<array<int, 2>> t;
        TrieMaxXor() {
            cnt.push_back(0);
            t.push_back({-1, -1});
        }
        void add(int x, int y) {
            int now = 0;
            for (int i = 31; i >= 0; --i) {
                int b = x >> i & 1;
                if (t[now][b] == -1) {
                    t[now][b] = (int) t.size();
                    t.push_back({-1, -1});
                    cnt.push_back(0);
                }
                now = t[now][b];
                cnt[now] += y;
            }
        }
        int GetMaxXor(int x) {
            int now = 0;
            int res = 0;
            for (int i = 31; i >= 0; --i) {
                int b = x >> i & 1;
                if (t[now][1 ^ b] != -1 and cnt[t[now][1 ^ b]] > 0) {
                    res |= 1 << i;
                    now = t[now][1 ^ b];
                } else {
                    now = t[now][b];
                }
                if (now == -1) {
                    return 0;
                }
            }  
            return res;
        }
};
class Solution {
public:
    int maximumStrongPairXor(vector<int>& v) {
        sort(v.begin(), v.end()); 
        int ans = 0;
        const int n = v.size();
        TrieMaxXor trie;
        for (int i = 0, j = 0; i < n; ++i) {
            while (j < n and v[j] <= 2 * v[i]) {
                trie.add(v[j], 1);
                ++j;
            }
            ans = max(ans, trie.GetMaxXor(v[i]));
            trie.add(v[i], -1);

        }
        return ans;
    }
};
