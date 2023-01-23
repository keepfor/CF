#include <bits/stdc++.h>

using i64 = long long;
template<class T>
struct Flow {
    const int n;
    struct Edge {
        int to;
        T cap;
        Edge(int to, T cap) : to(to), cap(cap) {}
    };
    std::vector<Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<int> cur, h;
    Flow(int n) : n(n), g(n) {}
    
    bool bfs(int s, int t) {
        h.assign(n, -1);
        std::queue<int> que;
        h[s] = 0;
        que.push(s);
        while (!que.empty()) {
            const int u = que.front();
            que.pop();
            for (int i : g[u]) {
                auto [v, c] = e[i];
                if (c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t) {
                        return true;
                    }
                    que.push(v);
                }
            }
        }
        return false;
    }
    
    T dfs(int u, int t, T f) {
        if (u == t) {
            return f;
        }
        auto r = f;
        for (int &i = cur[u]; i < int(g[u].size()); ++i) {
            const int j = g[u][i];
            auto [v, c] = e[j];
            if (c > 0 && h[v] == h[u] + 1) {
                auto a = dfs(v, t, std::min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0) {
                    return f;
                }
            }
        }
        return f - r;
    }
    void addEdge(int u, int v, T c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    T maxFlow(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, std::numeric_limits<T>::max());
        }
        return ans;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
        b[i]--;
    }
    
    std::vector<int> bela(n, -1), belb(n, -1);
    for (int i = 0; i < n; i++) {
        if (bela[i] != -1) continue;
        int j = i;
        while (bela[j] == -1) {
            bela[j] = i;
            j = a[j];
        }
    }
    for (int i = 0; i < n; i++) {
        if (belb[i] != -1) continue;
        int j = i;
        while (belb[j] == -1) {
            belb[j] = i;
            j = b[j];
        }
    }
    
    Flow<int> flow(2 * n + 2);
    for (int i = 0; i < n; i++) {
        flow.addEdge(bela[i], n + belb[i], 1);
    }
    for (int i = 0; i < n; i++) {
        flow.addEdge(2 * n, i, 1);
        flow.addEdge(n + i, 2 * n + 1, 1);
    }
    
    flow.maxFlow(2 * n, 2 * n + 1);
    
    std::vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (flow.e[2 * i].cap) {
            ans.push_back(i);
        }
    }
    
    std::cout << ans.size() << "\n";
    for (auto x : ans) {
        std::cout << x + 1 << " \n"[x == ans.back()];
    }
    
    return 0;
}
