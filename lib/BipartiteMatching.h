#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <deque>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
using lint = long long;
using pint = pair<int, int>;
using plint = pair<lint, lint>;
struct fast_ios { fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(20); }; } fast_ios_;
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define IFOR(i, begin, end) for(int i=(end)-1,i##_begin_=(begin);i>=i##_begin_;i--)
#define REP(i, n) FOR(i,0,n)
#define IREP(i, n) IFOR(i,0,n)
template <typename T> bool chmax(T &m, const T q) { return m < q ? (m = q, true) : false; }
template <typename T> bool chmin(T &m, const T q) { return m > q ? (m = q, true) : false; }
const std::vector<std::pair<int, int>> grid_dxs{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int floor_lg(long long x) { return x <= 0 ? -1 : 63 - __builtin_clzll(x); }
template <class T1, class T2> T1 floor_div(T1 num, T2 den) { return (num > 0 ? num / den : -((-num + den - 1) / den)); }
template <class T1, class T2> std::pair<T1, T2> operator+(const std::pair<T1, T2> &l, const std::pair<T1, T2> &r) { return std::make_pair(l.first + r.first, l.second + r.second); }
template <class T1, class T2> std::pair<T1, T2> operator-(const std::pair<T1, T2> &l, const std::pair<T1, T2> &r) { return std::make_pair(l.first - r.first, l.second - r.second); }
template <class T> std::vector<T> sort_unique(std::vector<T> vec) { sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end()); return vec; }
template <class T> int arglb(const std::vector<T> &v, const T &x) { return std::distance(v.begin(), std::lower_bound(v.begin(), v.end(), x)); }
template <class T> int argub(const std::vector<T> &v, const T &x) { return std::distance(v.begin(), std::upper_bound(v.begin(), v.end(), x)); }
template <class IStream, class T> IStream &operator>>(IStream &is, std::vector<T> &vec) { for (auto &v : vec) is >> v; return is; }

template <class OStream, class T> OStream &operator<<(OStream &os, const std::vector<T> &vec);
template <class OStream, class T, size_t sz> OStream &operator<<(OStream &os, const std::array<T, sz> &arr);
template <class OStream, class T, class TH> OStream &operator<<(OStream &os, const std::unordered_set<T, TH> &vec);
template <class OStream, class T, class U> OStream &operator<<(OStream &os, const pair<T, U> &pa);
template <class OStream, class T> OStream &operator<<(OStream &os, const std::deque<T> &vec);
template <class OStream, class T> OStream &operator<<(OStream &os, const std::set<T> &vec);
template <class OStream, class T> OStream &operator<<(OStream &os, const std::multiset<T> &vec);
template <class OStream, class T> OStream &operator<<(OStream &os, const std::unordered_multiset<T> &vec);
template <class OStream, class T, class U> OStream &operator<<(OStream &os, const std::pair<T, U> &pa);
template <class OStream, class TK, class TV> OStream &operator<<(OStream &os, const std::map<TK, TV> &mp);
template <class OStream, class TK, class TV, class TH> OStream &operator<<(OStream &os, const std::unordered_map<TK, TV, TH> &mp);
template <class OStream, class... T> OStream &operator<<(OStream &os, const std::tuple<T...> &tpl);

template <class OStream, class T> OStream &operator<<(OStream &os, const std::vector<T> &vec) { os << '['; for (auto v : vec) os << v << ','; os << ']'; return os; }
template <class OStream, class T, size_t sz> OStream &operator<<(OStream &os, const std::array<T, sz> &arr) { os << '['; for (auto v : arr) os << v << ','; os << ']'; return os; }
template <class... T> std::istream &operator>>(std::istream &is, std::tuple<T...> &tpl) { std::apply([&is](auto &&... args) { ((is >> args), ...);}, tpl); return is; }
template <class OStream, class... T> OStream &operator<<(OStream &os, const std::tuple<T...> &tpl) { os << '('; std::apply([&os](auto &&... args) { ((os << args << ','), ...);}, tpl); return os << ')'; }
template <class OStream, class T, class TH> OStream &operator<<(OStream &os, const std::unordered_set<T, TH> &vec) { os << '{'; for (auto v : vec) os << v << ','; os << '}'; return os; }
template <class OStream, class T> OStream &operator<<(OStream &os, const std::deque<T> &vec) { os << "deq["; for (auto v : vec) os << v << ','; os << ']'; return os; }
template <class OStream, class T> OStream &operator<<(OStream &os, const std::set<T> &vec) { os << '{'; for (auto v : vec) os << v << ','; os << '}'; return os; }
template <class OStream, class T> OStream &operator<<(OStream &os, const std::multiset<T> &vec) { os << '{'; for (auto v : vec) os << v << ','; os << '}'; return os; }
template <class OStream, class T> OStream &operator<<(OStream &os, const std::unordered_multiset<T> &vec) { os << '{'; for (auto v : vec) os << v << ','; os << '}'; return os; }
template <class OStream, class T, class U> OStream &operator<<(OStream &os, const std::pair<T, U> &pa) { return os << '(' << pa.first << ',' << pa.second << ')'; }
template <class OStream, class TK, class TV> OStream &operator<<(OStream &os, const std::map<TK, TV> &mp) { os << '{'; for (auto v : mp) os << v.first << "=>" << v.second << ','; os << '}'; return os; }
template <class OStream, class TK, class TV, class TH> OStream &operator<<(OStream &os, const std::unordered_map<TK, TV, TH> &mp) { os << '{'; for (auto v : mp) os << v.first << "=>" << v.second << ','; os << '}'; return os; }
#ifdef HITONANODE_LOCAL
const string COLOR_RESET = "\033[0m", BRIGHT_GREEN = "\033[1;32m", BRIGHT_RED = "\033[1;31m", BRIGHT_CYAN = "\033[1;36m", NORMAL_CROSSED = "\033[0;9;37m", RED_BACKGROUND = "\033[1;41m", NORMAL_FAINT = "\033[0;2m";
#define dbg(x) std::cerr << BRIGHT_CYAN << #x << COLOR_RESET << " = " << (x) << NORMAL_FAINT << " (L" << __LINE__ << ") " << __FILE__ << COLOR_RESET << std::endl
#define dbgif(cond, x) ((cond) ? std::cerr << BRIGHT_CYAN << #x << COLOR_RESET << " = " << (x) << NORMAL_FAINT << " (L" << __LINE__ << ") " << __FILE__ << COLOR_RESET << std::endl : std::cerr)
#else
#define dbg(x) ((void)0)
#define dbgif(cond, x) ((void)0)
#endif

// Directed graph library to find strongly connected components （強連結成分分解）
// 0-indexed directed graph
// Complexity: O(V + E)
struct DirectedGraphSCC {
    int V; // # of Vertices
    std::vector<std::vector<int>> to, from;
    std::vector<int> used; // Only true/false
    std::vector<int> vs;
    std::vector<int> cmp;
    int scc_num = -1;

    DirectedGraphSCC(int V = 0) : V(V), to(V), from(V), cmp(V) {}

    void _dfs(int v) {
        used[v] = true;
        for (auto t : to[v])
            if (!used[t]) _dfs(t);
        vs.push_back(v);
    }
    void _rdfs(int v, int k) {
        used[v] = true;
        cmp[v] = k;
        for (auto t : from[v])
            if (!used[t]) _rdfs(t, k);
    }

    void add_edge(int from_, int to_) {
        assert(from_ >= 0 and from_ < V and to_ >= 0 and to_ < V);
        to[from_].push_back(to_);
        from[to_].push_back(from_);
    }

    // Detect strongly connected components and return # of them.
    // Also, assign each vertex `v` the scc id `cmp[v]` (0-indexed)
    int FindStronglyConnectedComponents() {
        used.assign(V, false);
        vs.clear();
        for (int v = 0; v < V; v++)
            if (!used[v]) _dfs(v);
        used.assign(V, false);
        scc_num = 0;
        for (int i = (int)vs.size() - 1; i >= 0; i--)
            if (!used[vs[i]]) _rdfs(vs[i], scc_num++);
        return scc_num;
    }

    // Find and output the vertices that form a closed cycle.
    // output: {v_1, ..., v_C}, where C is the length of cycle,
    //         {} if there's NO cycle (graph is DAG)
    int _c, _init;
    std::vector<int> _ret_cycle;
    bool _dfs_detectcycle(int now, bool b0) {
        if (now == _init and b0) return true;
        for (auto nxt : to[now])
            if (cmp[nxt] == _c and !used[nxt]) {
                _ret_cycle.emplace_back(nxt), used[nxt] = 1;
                if (_dfs_detectcycle(nxt, true)) return true;
                _ret_cycle.pop_back();
            }
        return false;
    }
    std::vector<int> DetectCycle() {
        int ns = FindStronglyConnectedComponents();
        if (ns == V) return {};
        std::vector<int> cnt(ns);
        for (auto x : cmp) cnt[x]++;
        _c = std::find_if(cnt.begin(), cnt.end(), [](int x) { return x > 1; }) - cnt.begin();
        _init = std::find(cmp.begin(), cmp.end(), _c) - cmp.begin();
        used.assign(V, false);
        _ret_cycle.clear();
        _dfs_detectcycle(_init, false);
        return _ret_cycle;
    }

    // After calling `FindStronglyConnectedComponents()`, generate a new graph by uniting all
    // vertices belonging to the same component(The resultant graph is DAG).
    DirectedGraphSCC GenerateTopologicalGraph() {
        DirectedGraphSCC newgraph(scc_num);
        for (int s = 0; s < V; s++)
            for (auto t : to[s]) {
                if (cmp[s] != cmp[t]) newgraph.add_edge(cmp[s], cmp[t]);
            }
        return newgraph;
    }
};

// 2-SAT solver: Find a solution for  `(Ai v Aj) ^ (Ak v Al) ^ ... = true`
// - `nb_sat_vars`: Number of variables
// - Considering a graph with `2 * nb_sat_vars` vertices
// - Vertices [0, nb_sat_vars) means `Ai`
// - vertices [nb_sat_vars, 2 * nb_sat_vars) means `not Ai`
struct SATSolver : DirectedGraphSCC {
    int nb_sat_vars;
    std::vector<int> solution;
    SATSolver(int nb_variables = 0)
        : DirectedGraphSCC(nb_variables * 2), nb_sat_vars(nb_variables), solution(nb_sat_vars) {}
    void add_x_or_y_constraint(bool is_x_true, int x, bool is_y_true, int y) {
        assert(x >= 0 and x < nb_sat_vars);
        assert(y >= 0 and y < nb_sat_vars);
        if (!is_x_true) x += nb_sat_vars;
        if (!is_y_true) y += nb_sat_vars;
        add_edge((x + nb_sat_vars) % (nb_sat_vars * 2), y);
        add_edge((y + nb_sat_vars) % (nb_sat_vars * 2), x);
    }
    // Solve the 2-SAT problem. If no solution exists, return `false`.
    // Otherwise, dump one solution to `solution` and return `true`.
    bool run() {
        FindStronglyConnectedComponents();
        for (int i = 0; i < nb_sat_vars; i++) {
            if (cmp[i] == cmp[i + nb_sat_vars]) return false;
            solution[i] = cmp[i] > cmp[i + nb_sat_vars];
        }
        return true;
    }
};

#include <cassert>
#include <iostream>
#include <vector>

// Bipartite matching of undirected bipartite graph (Hopcroft-Karp)
// https://ei1333.github.io/luzhiled/snippets/graph/hopcroft-karp.html
// Comprexity: O((V + E)sqrtV)
// int solve(): enumerate maximum number of matching / return -1 (if graph is not bipartite)
struct BipartiteMatching {
    int V;
    std::vector<std::vector<int>> to; // Adjacency list
    std::vector<int> dist;            // dist[i] = (Distance from i'th node)
    std::vector<int> match;           // match[i] = (Partner of i'th node) or -1 (No parter)
    std::vector<int> used, vv;
    std::vector<int> color; // color of each node(checking bipartition): 0/1/-1(not determined)

    BipartiteMatching() = default;
    BipartiteMatching(int V_) : V(V_), to(V_), match(V_, -1), used(V_), color(V_, -1) {}

    void add_edge(int u, int v) {
        assert(u >= 0 and u < V and v >= 0 and v < V and u != v);
        to[u].push_back(v);
        to[v].push_back(u);
    }

    void _bfs() {
        dist.assign(V, -1);
        std::vector<int> q;
        int lq = 0;
        for (int i = 0; i < V; i++) {
            if (!color[i] and !used[i]) q.push_back(i), dist[i] = 0;
        }

        while (lq < int(q.size())) {
            int now = q[lq++];
            for (auto nxt : to[now]) {
                int c = match[nxt];
                if (c >= 0 and dist[c] == -1) q.push_back(c), dist[c] = dist[now] + 1;
            }
        }
    }

    bool _dfs(int now) {
        vv[now] = true;
        for (auto nxt : to[now]) {
            int c = match[nxt];
            if (c < 0 or (!vv[c] and dist[c] == dist[now] + 1 and _dfs(c))) {
                match[nxt] = now, match[now] = nxt;
                used[now] = true;
                return true;
            }
        }
        return false;
    }

    bool _color_bfs(int root) {
        color[root] = 0;
        std::vector<int> q{root};
        int lq = 0;
        while (lq < int(q.size())) {
            int now = q[lq++], c = color[now];
            for (auto nxt : to[now]) {
                if (color[nxt] == -1) {
                    color[nxt] = !c, q.push_back(nxt);
                } else if (color[nxt] == c) {
                    return false;
                }
            }
        }
        return true;
    }

    int solve() {
        for (int i = 0; i < V; i++) {
            if (color[i] == -1 and !_color_bfs(i)) return -1;
        }
        int ret = 0;
        while (true) {
            _bfs();
            vv.assign(V, false);
            int flow = 0;
            for (int i = 0; i < V; i++) {
                if (!color[i] and !used[i] and _dfs(i)) flow++;
            }
            if (!flow) break;
            ret += flow;
        }
        return ret;
    }

    template <class OStream> friend OStream &operator<<(OStream &os, const BipartiteMatching &bm) {
        os << "{N=" << bm.V << ':';
        for (int i = 0; i < bm.V; i++) {
            if (bm.match[i] > i) os << '(' << i << '-' << bm.match[i] << "),";
        }
        return os << '}';
    }
};

// UnionFind Tree (0-indexed), based on size of each disjoint set
struct UnionFind {
    std::vector<int> par, cou;
    UnionFind(int N = 0) : par(N), cou(N, 1) { iota(par.begin(), par.end(), 0); }
    int find(int x) { return (par[x] == x) ? x : (par[x] = find(par[x])); }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (cou[x] < cou[y]) std::swap(x, y);
        par[y] = x, cou[x] += cou[y];
        return true;
    }
    int count(int x) { return cou[find(x)]; }
    bool same(int x, int y) { return find(x) == find(y); }
    std::vector<std::vector<int>> groups() {
        std::vector<std::vector<int>> ret(par.size());
        for (int i = 0; i < int(par.size()); ++i) ret[find(i)].push_back(i);
        ret.erase(std::remove_if(ret.begin(), ret.end(),
                                 [&](const std::vector<int> &v) { return v.empty(); }),
                  ret.end());
        return ret;
    }
};

template <typename T, T INF = std::numeric_limits<T>::max() / 2, int INVALID = -1>
struct shortest_path {
    int V, E;
    bool single_positive_weight;
    T wmin, wmax;

    std::vector<std::pair<int, T>> tos;
    std::vector<int> head;
    std::vector<std::tuple<int, int, T>> edges;

    void build_() {
        if (int(tos.size()) == E and int(head.size()) == V + 1) return;
        tos.resize(E);
        head.assign(V + 1, 0);
        for (const auto &e : edges) ++head[std::get<0>(e) + 1];
        for (int i = 0; i < V; ++i) head[i + 1] += head[i];
        auto cur = head;
        for (const auto &e : edges) {
            tos[cur[std::get<0>(e)]++] = std::make_pair(std::get<1>(e), std::get<2>(e));
        }
    }

    shortest_path(int V = 0) : V(V), E(0), single_positive_weight(true), wmin(0), wmax(0) {}
    void add_edge(int s, int t, T w) {
        assert(0 <= s and s < V);
        assert(0 <= t and t < V);
        edges.emplace_back(s, t, w);
        ++E;
        if (w > 0 and wmax > 0 and wmax != w) single_positive_weight = false;
        wmin = std::min(wmin, w);
        wmax = std::max(wmax, w);
    }

    void add_bi_edge(int u, int v, T w) {
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    std::vector<T> dist;
    std::vector<int> prev;

    // Dijkstra algorithm
    // - Requirement: wmin >= 0
    // - Complexity: O(E log E)
    using Pque = std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>,
                                     std::greater<std::pair<T, int>>>;
    template <class Heap = Pque> void dijkstra(int s, int t = INVALID) {
        assert(0 <= s and s < V);
        build_();
        dist.assign(V, INF);
        prev.assign(V, INVALID);
        dist[s] = 0;
        Heap pq;
        pq.emplace(0, s);
        while (!pq.empty()) {
            T d;
            int v;
            std::tie(d, v) = pq.top();
            pq.pop();
            if (t == v) return;
            if (dist[v] < d) continue;
            for (int e = head[v]; e < head[v + 1]; ++e) {
                const auto &nx = tos[e];
                T dnx = d + nx.second;
                if (dist[nx.first] > dnx) {
                    dist[nx.first] = dnx, prev[nx.first] = v;
                    pq.emplace(dnx, nx.first);
                }
            }
        }
    }

    // Dijkstra algorithm
    // - Requirement: wmin >= 0
    // - Complexity: O(V^2 + E)
    void dijkstra_vquad(int s, int t = INVALID) {
        assert(0 <= s and s < V);
        build_();
        dist.assign(V, INF);
        prev.assign(V, INVALID);
        dist[s] = 0;
        std::vector<char> fixed(V, false);
        while (true) {
            int r = INVALID;
            T dr = INF;
            for (int i = 0; i < V; i++) {
                if (!fixed[i] and dist[i] < dr) r = i, dr = dist[i];
            }
            if (r == INVALID or r == t) break;
            fixed[r] = true;
            int nxt;
            T dx;
            for (int e = head[r]; e < head[r + 1]; ++e) {
                std::tie(nxt, dx) = tos[e];
                if (dist[nxt] > dist[r] + dx) dist[nxt] = dist[r] + dx, prev[nxt] = r;
            }
        }
    }

    // Bellman-Ford algorithm
    // - Requirement: no negative loop
    // - Complexity: O(VE)
    bool bellman_ford(int s, int nb_loop) {
        assert(0 <= s and s < V);
        build_();
        dist.assign(V, INF), prev.assign(V, INVALID);
        dist[s] = 0;
        for (int l = 0; l < nb_loop; l++) {
            bool upd = false;
            for (int v = 0; v < V; v++) {
                if (dist[v] == INF) continue;
                for (int e = head[v]; e < head[v + 1]; ++e) {
                    const auto &nx = tos[e];
                    T dnx = dist[v] + nx.second;
                    if (dist[nx.first] > dnx) dist[nx.first] = dnx, prev[nx.first] = v, upd = true;
                }
            }
            if (!upd) return true;
        }
        return false;
    }

    // Bellman-ford algorithm using deque
    // - Requirement: no negative loop
    // - Complexity: O(VE)
    void spfa(int s) {
        assert(0 <= s and s < V);
        build_();
        dist.assign(V, INF);
        prev.assign(V, INVALID);
        dist[s] = 0;
        std::deque<int> q;
        std::vector<char> in_queue(V);
        q.push_back(s), in_queue[s] = 1;
        while (!q.empty()) {
            int now = q.front();
            q.pop_front(), in_queue[now] = 0;
            for (int e = head[now]; e < head[now + 1]; ++e) {
                const auto &nx = tos[e];
                T dnx = dist[now] + nx.second;
                int nxt = nx.first;
                if (dist[nxt] > dnx) {
                    dist[nxt] = dnx;
                    if (!in_queue[nxt]) {
                        if (q.size() and dnx < dist[q.front()]) { // Small label first optimization
                            q.push_front(nxt);
                        } else {
                            q.push_back(nxt);
                        }
                        prev[nxt] = now, in_queue[nxt] = 1;
                    }
                }
            }
        }
    }

    // 01-BFS
    // - Requirement: all weights must be 0 or w (positive constant).
    // - Complexity: O(V + E)
    void zero_one_bfs(int s, int t = INVALID) {
        assert(0 <= s and s < V);
        build_();
        dist.assign(V, INF), prev.assign(V, INVALID);
        dist[s] = 0;
        std::vector<int> q(V * 4);
        int ql = V * 2, qr = V * 2;
        q[qr++] = s;
        while (ql < qr) {
            int v = q[ql++];
            if (v == t) return;
            for (int e = head[v]; e < head[v + 1]; ++e) {
                const auto &nx = tos[e];
                T dnx = dist[v] + nx.second;
                if (dist[nx.first] > dnx) {
                    dist[nx.first] = dnx, prev[nx.first] = v;
                    if (nx.second) {
                        q[qr++] = nx.first;
                    } else {
                        q[--ql] = nx.first;
                    }
                }
            }
        }
    }

    // Dial's algorithm
    // - Requirement: wmin >= 0
    // - Complexity: O(wmax * V + E)
    void dial(int s, int t = INVALID) {
        assert(0 <= s and s < V);
        build_();
        dist.assign(V, INF), prev.assign(V, INVALID);
        dist[s] = 0;
        std::vector<std::vector<std::pair<int, T>>> q(wmax + 1);
        q[0].emplace_back(s, dist[s]);
        int ninq = 1;

        int cur = 0;
        T dcur = 0;
        for (; ninq; ++cur, ++dcur) {
            if (cur == wmax + 1) cur = 0;
            while (!q[cur].empty()) {
                int v = q[cur].back().first;
                T dnow = q[cur].back().second;
                q[cur].pop_back(), --ninq;
                if (v == t) return;
                if (dist[v] < dnow) continue;

                for (int e = head[v]; e < head[v + 1]; ++e) {
                    const auto &nx = tos[e];
                    T dnx = dist[v] + nx.second;
                    if (dist[nx.first] > dnx) {
                        dist[nx.first] = dnx, prev[nx.first] = v;
                        int nxtcur = cur + int(nx.second);
                        if (nxtcur >= int(q.size())) nxtcur -= q.size();
                        q[nxtcur].emplace_back(nx.first, dnx), ++ninq;
                    }
                }
            }
        }
    }

    // Solver for DAG
    // - Requirement: graph is DAG
    // - Complexity: O(V + E)
    bool dag_solver(int s) {
        assert(0 <= s and s < V);
        build_();
        dist.assign(V, INF), prev.assign(V, INVALID);
        dist[s] = 0;
        std::vector<int> indeg(V, 0);
        std::vector<int> q(V * 2);
        int ql = 0, qr = 0;
        q[qr++] = s;
        while (ql < qr) {
            int now = q[ql++];
            for (int e = head[now]; e < head[now + 1]; ++e) {
                const auto &nx = tos[e];
                ++indeg[nx.first];
                if (indeg[nx.first] == 1) q[qr++] = nx.first;
            }
        }
        ql = qr = 0;
        q[qr++] = s;
        while (ql < qr) {
            int now = q[ql++];
            for (int e = head[now]; e < head[now + 1]; ++e) {
                const auto &nx = tos[e];
                --indeg[nx.first];
                if (dist[nx.first] > dist[now] + nx.second)
                    dist[nx.first] = dist[now] + nx.second, prev[nx.first] = now;
                if (indeg[nx.first] == 0) q[qr++] = nx.first;
            }
        }
        return *max_element(indeg.begin(), indeg.end()) == 0;
    }

    // Retrieve a sequence of vertex ids that represents shortest path [s, ..., goal]
    // If not reachable to goal, return {}
    std::vector<int> retrieve_path(int goal) const {
        assert(int(prev.size()) == V);
        assert(0 <= goal and goal < V);
        if (dist[goal] == INF) return {};
        std::vector<int> ret{goal};
        while (prev[goal] != INVALID) {
            goal = prev[goal];
            ret.push_back(goal);
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
    }

    void solve(int s, int t = INVALID) {
        if (wmin >= 0) {
            if (single_positive_weight) {
                zero_one_bfs(s, t);
            } else if (wmax <= 10) {
                dial(s, t);
            } else {
                if ((long long)V * V < (E << 4)) {
                    dijkstra_vquad(s, t);
                } else {
                    dijkstra(s, t);
                }
            }
        } else {
            bellman_ford(s, V);
        }
    }

    // Warshall-Floyd algorithm
    // - Requirement: no negative loop
    // - Complexity: O(E + V^3)
    std::vector<std::vector<T>> floyd_warshall() {
        build_();
        std::vector<std::vector<T>> dist2d(V, std::vector<T>(V, INF));
        for (int i = 0; i < V; i++) {
            dist2d[i][i] = 0;
            for (const auto &e : edges) {
                int s = std::get<0>(e), t = std::get<1>(e);
                dist2d[s][t] = std::min(dist2d[s][t], std::get<2>(e));
            }
        }
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                if (dist2d[i][k] == INF) continue;
                for (int j = 0; j < V; j++) {
                    if (dist2d[k][j] == INF) continue;
                    dist2d[i][j] = std::min(dist2d[i][j], dist2d[i][k] + dist2d[k][j]);
                }
            }
        }
        return dist2d;
    }

    void to_dot(std::string filename = "shortest_path") const {
        std::ofstream ss(filename + ".DOT");
        ss << "digraph{\n";
        build_();
        for (int i = 0; i < V; i++) {
            for (int e = head[i]; e < head[i + 1]; ++e) {
                ss << i << "->" << tos[e].first << "[label=" << tos[e].second << "];\n";
            }
        }
        ss << "}\n";
        ss.close();
        return;
    }
};




int main() {
    int N;
    cin >> N;


    constexpr int D = 26;

    shortest_path<int> sp(D);
    DirectedGraphSCC graph(D);

    vector<int> has(D);

    vector<pint> edges;

    UnionFind uf(D);
    REP(_, N) {
        char a, b;
        cin >> a >> b;
        int i = a - 'A', j = b - 'A';
        sp.add_edge(i, j, 0);
        graph.add_edge(i, j);
        has.at(i) = has.at(j) = 1;
        uf.unite(i, j);
        edges.emplace_back(i, j);
    }
    dbg(edges);

    const auto wf = sp.floyd_warshall();

    const int V = graph.FindStronglyConnectedComponents();
    dbg(V);

    vector<pint> bs;
    vector<int> has_outer(D);
    for (auto [a, b] : edges) {
        if (graph.cmp.at(a) != graph.cmp.at(b)) {
            bs.emplace_back(a, b);
            has_outer.at(a) = has_outer.at(b) = 1;
        }
    }

    dbg(bs);

    BipartiteMatching bm(bs.size() * 2);


    REP(i, bs.size()) {
        REP(j, bs.size()) {
            auto [si, ti] = bs.at(i);
            auto [sj, tj] = bs.at(j);
            if (wf.at(ti).at(sj) == 0 and wf.at(tj).at(si) > 0)  bm.add_edge(i, j + bs.size());
        }
    }

    int ret = 0;

    for (auto v : uf.groups()) {
        int r = v.front();
        bool has_out = false;
        for (int i : v) {
            if (has_outer.at(i)) has_out = true;
        }
        if (has.at(r) and !has_out) ++ret;
    }

    dbg(ret);

    ret += bs.size();
    dbg(ret);
    ret -= bm.solve();
    dbg(ret);
    if (ret == 0) ++ret;
    cout << ret << '\n';
}
