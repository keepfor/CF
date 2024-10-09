#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
struct SCC {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> stk;
    std::vector<int> dfn, low, bel;
    int cur, cnt;
    
    SCC() {}
    SCC(int n) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        bel.assign(n, -1);
        stk.clear();
        cur = cnt = 0;
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    void dfs(int x) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        
        for (auto y : adj[x]) {
            if (dfn[y] == -1) {
                dfs(y);
                low[x] = std::min(low[x], low[y]);
            } else if (bel[y] == -1) {
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        
        if (dfn[x] == low[x]) {
            int y;
            do {
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while (y != x);
            cnt++;
        }
    }
    
    std::vector<int> work() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                dfs(i);
            }
        }
        return bel;
    }
};
template<class T>
struct MaxFlow {
    struct _Edge {
        int to;
        T cap;
        _Edge(int to, T cap) : to(to), cap(cap) {}
    };
    int n;
    std::vector<_Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<int> cur, h;
    MaxFlow() {}
    MaxFlow(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        e.clear();
        g.assign(n, {});
        cur.resize(n);
        h.resize(n);
    }
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
    T flow(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, std::numeric_limits<T>::max());
        }
        return ans;
    }
    std::vector<bool> minCut() {
        std::vector<bool> c(n);
        for (int i = 0; i < n; i++) {
            c[i] = (h[i] != -1);
        }
        return c;
    }
    struct Edge {
        int from;
        int to;
        T cap;
        T flow;
    };
    std::vector<Edge> edges() {
        std::vector<Edge> a;
        for (int i = 0; i < e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;
            x.to = e[i].to;
            x.cap = e[i].cap + e[i + 1].cap;
            x.flow = e[i + 1].cap;
            a.push_back(x);
        }
        return a;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    std::cin >> N;
    
    SCC g(26);
    for (int i = 0; i < N; i++) {
        std::string S;
        std::cin >> S;
        g.addEdge(S[0] - 'A', S[1] - 'A');
    }
    
    auto bel = g.work();
    int cnt = g.cnt;
    std::vector<int> e(cnt);
    std::vector<bool> conn(cnt);
    std::vector<std::array<int, 2>> edges;
    for (int x = 0; x < 26; x++) {
        for (auto y : g.adj[x]) {
            if (bel[x] == bel[y]) {
                e[bel[x]]++;
            } else {
                conn[bel[x]] = true;
                conn[bel[y]] = true;
                edges.push_back({bel[x], bel[y]});
            }
        }
    }
    
    const int E = edges.size();
    MaxFlow<int> f(2 * E + 2);
    int ans = E;
    int S = 2 * E, T = S + 1;
    for (int i = 0; i < E; i++) {
        f.addEdge(S, 2 * i, 1);
        f.addEdge(2 * i + 1, T, 1);
    }
    std::vector reach(E, std::vector<int>(E));
    for (int i = 0; i < E; i++) {
        for (int j = 0; j < E; j++) {
            if (edges[i][1] == edges[j][0]) {
                reach[i][j] = 1;
            }
        }
    }
    for (int k = 0; k < E; k++) {
        for (int i = 0; i < E; i++) {
            for (int j = 0; j < E; j++) {
                reach[i][j] |= reach[i][k] & reach[k][j];
            }
        }
    }
    for (int i = 0; i < E; i++) {
        for (int j = 0; j < E; j++) {
            if (reach[i][j]) {
                f.addEdge(2 * i, 2 * j + 1, 1);
            }
        }
    }
    ans -= f.flow(S, T);
    for (int i = 0; i < cnt; i++) {
        if (!conn[i] && e[i] > 0) {
            ans++;
        }
    }
    std::cout << ans << "\n";
    
    return 0;
}
