#include<bits/stdc++.h>

#ifdef LOCAL
#include"debug.h"
#endif

using namespace std;

class LCA {
public:
    int n;
    const int LOG = 20;
    vector<vector<int>> g;
    vector<int> dist;
    vector<int> que;
    vector<int> parent;
    vector<vector<int>> jump;
    LCA(int n) {
        this->n = n;
        g.resize(n);
        dist.resize(n, -1);
        parent.resize(n, -1);
        que.resize(1, 0);
        jump.resize(n, vector<int>(LOG));
        dist[0] = 0;
        parent[0] = 0;
    }
    void build() {
        for (int i = 0; i < n - 1; i++) {
          int x, y;
          cin >> x >> y;
          --x; --y;
          g[x].push_back(y);
          g[y].push_back(x);
        }
        for (int b = 0; b < (int) que.size(); b++) {
          for (int u : g[que[b]]) {
            if (dist[u] == -1) {
              que.push_back(u);
              dist[u] = dist[que[b]] + 1;
              parent[u] = que[b];
            }
          }
        }
        for (int i = 0; i < n; i++) {
          jump[i][0] = parent[i];
        }
        for (int j = 1; j < LOG; j++) {
          for (int i = 0; i < n; i++) {
            jump[i][j] = jump[jump[i][j - 1]][j - 1];
          }
        }
    }
    
    
    int lca(int u, int v) {
      if (dist[u] < dist[v]) {
        swap(u, v);
      }
      for (int j = LOG - 1; j >= 0; j--) {
        if (dist[u] - (1 << j) >= dist[v]) {
          u = jump[u][j];
        }
      }
      if (u == v) {
        return u;
      }
      for (int j = LOG - 1; j >= 0; j--) {
        if (jump[u][j] != jump[v][j]) {
          u = jump[u][j];
          v = jump[v][j];
        }
      }
      return parent[u];
    }
};
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    return 0;

