class Solution {
public:
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
      vector<vector<int>> g(n);
      for (auto& i : edges) {
        g[i[0]].push_back(i[1]);
        g[i[1]].push_back(i[0]);
      }
      vector<int> p(n, -1), dep(n, -1);
      dep[0] = 0;
      function<void(int)> dfs = [&](int u) -> void {
        for (auto& v : g[u]) {
          if (dep[v] == -1) {
            dep[v] = dep[u] + 1;
            p[v] = u;
            dfs(v);
          }
        }
      };
      dfs(0);
      vector<int> cnt(n);
      for (auto& i : price) {
        int u = i[0], v = i[1];
        if (dep[u] > dep[v]) {
          swap(u, v);
        }
        while (dep[u] != dep[v]) {
          ++cnt[u];
          u = p[u];
        }
        while (u != v) {
          ++cnt[u];
          ++cnt[v];
          u = p[u];
          v = p[v];
        }
        ++cnt[u];
      }
      function<pair<int, int>(int, int)> df = [&](int u, int fa) -> pair<int, int> {
        int nhav = 0, hav = 0;
        for (auto& v : g[u]) {
          if (v != u) {
            auto [nha, ha] = df(v, u);
            nhav += x;
            hav += min(x, y);
          }
        }
        return {price[u] * cnt[u] + hav, price[u] * cnt[u] / 2 + nhav};
      };
      auto [x, y] = df(0, -1);
      return min(x, y);
    }
};
