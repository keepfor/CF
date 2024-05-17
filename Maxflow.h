#include <stdio.h>
#include <vector>
#include <queue>
#include <limits>
#include <string.h>
#include <functional>
#include <algorithm>
using namespace std;
const int MAXN = 205;
//total # of nodes
struct Maxflow {
	struct E {
		int x, inv, cap, flow;
		E(int t, int c, int z) : x(t), inv(z), cap(c), flow(0) {}
		int rest() const { return cap - flow; }
	};
	int V, d[MAXN], e_try[MAXN];
	vector <E> g[MAXN];
	Maxflow(int V) : V(V) {}
	void addedge(int a, int b, int a2b, int b2a = 0) {
		int as = g[a].size(), bs = g[b].size();
		g[a].push_back({ b, a2b, bs });
		g[b].push_back({ a, b2a, as });
	}
	bool bfs(int S, int T) {
		memset(d, -1, sizeof(d));
		queue <int> q; q.push(S);
		d[S] = 0;
		while (!q.empty()) {
			int x = q.front(); q.pop();
			for (auto &e : g[x]) {
				if (d[e.x] == -1 && e.rest() > 0) {
					d[e.x] = d[x] + 1;
					q.push(e.x);
				}
			}
		}
		return d[T] != -1;
	}
	int dfs(int x, int T, int flow) {
		if (x == T) return flow;
		for (int& i = e_try[x]; i < g[x].size(); i++) {
			E &e = g[x][i];
			if (e.rest() > 0 && d[e.x] == d[x] + 1) {
				int t = dfs(e.x, T, min(flow, e.rest()));
				if (t > 0) {
					E &re = g[e.x][e.inv];
					e.flow += t;
					re.flow = -e.flow;
					return t;
				}
			}
		}
		return 0;
	}
	int go(int S, int T) {
		int res = 0, t = 0;
		while (bfs(S, T)) {
			memset(e_try, 0, sizeof(e_try));
			do {
				t = dfs(S, T, numeric_limits<int>::max());
				res += t;
			} while (t);
		}
		return res;
	}
};
const int inf = 1e6;
int n, m;
int a[MAXN], b[MAXN], ans[MAXN][MAXN];
int main() {
	scanf("%d%d", &n, &m);
	Maxflow f(2 * n + 2);
	int as = 0, bs = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		f.addedge(0, i, a[i]);
		as += a[i];
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &b[i]);
		f.addedge(n + i, 2 * n + 1, b[i]);
		bs += b[i];
	}
	if (as != bs) {
		puts("NO");
		return 0;
	}
	for (int i = 1; i <= m; i++) {
		int x, y; scanf("%d%d", &x, &y);
		f.addedge(x, n + y, inf);
		f.addedge(y, n + x, inf);
	}
	for (int i = 1; i <= n; i++) {
		f.addedge(i, n + i, a[i]);
	}
	int flow = f.go(0, 2 * n + 1);
	if (flow == as) {
		puts("YES");
		for (int i = 1; i <= n; i++) {
			for (auto &e : f.g[i]) {
				int j = e.x, w = e.flow;
				if (n + 1 <= j && j <= 2 * n) ans[i][j - n] = w;
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) printf("%d ", ans[i][j]);
			puts("");
		}
	}
	else puts("NO");
}