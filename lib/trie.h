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
        t[now][b] = (int)t.size();
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
namespace digit {
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
}  // namespace digit
namespace longest_common_suffix_queries {
// https://leetcode.com/problems/longest-common-suffix-queries/
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
      x = t[x][c];
      id[x] = idx;
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
    stable_sort(ord.begin(), ord.end(), [&](auto a, auto b) -> bool {
      return v[a].size() < v[b].size();
    });
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
};  // namespace longest_common_suffix_queries
