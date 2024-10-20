class Hashing {
 public:
    using ll = int64_t;
    static constexpr ll mod = 903547;
    static constexpr ll base = 67;
    vector<ll> p;
    vector<ll> h;
    vector<ll> rev;
    Hashing(const string& v) {
        const int n = v.size();
        p.assign(n + 1, 1);
        h.assign(n + 1, 0);
        rev.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            p[i] = p[i - 1] * base % mod;
        }
        for (int i = 1; i <= n; ++i) {
            h[i] = ((h[i - 1] * base % mod) + v[i - 1]) % mod; 
        }
        for (int i = n - 1; i >= 0; --i) {
            rev[i] = ((rev[i + 1] * base % mod) + v[i]) % mod; 
        }
    }

    int getH(int l, int r) {
        const int z = r - l + 1;
        return (h[r + 1] - ((h[l] * p[z]) % mod) + mod) % mod;
    }

    int getR(int l, int r) {
        const int z = r - l + 1;
        return (rev[l] - ((rev[r + 1] * p[z]) % mod) + mod) % mod;;
    }
};

class Solution {
public:
    vector<bool> findAnswer(vector<int>& p, string s) {
      const int n = p.size();

      vector<vector<int>> g(n);
      for (int i = 1; i < n; ++i) {
        g[p[i]].push_back(i);
      }

      vector<int> l(n), r(n);
      string t;
      auto Dfs = [&](auto&& self, int u, int pa) -> void {
        l[u] = (int) t.size();
        for (auto& v : g[u]) {
          if (v == pa) continue;
          self(self, v, u);
        }
        r[u] = (int) t.size();
        t += s[u];     
      };
      Dfs(Dfs, 0, -1);
      vector<bool> ans(n);
      Hashing hash(t);
      for (int i = 0; i < n; ++i) {
        int a = hash.getH(l[i], r[i]);
        int b = hash.getR(l[i], r[i]);
        ans[i] = bool(a == b);
      }
      return ans;
    }
};
