#include <bits/stdc++.h>
using namespace std;

template <typename T>
using vc = vector<T>;

using ll = int64_t;

// select(i,j,k) : (i,j) -> (i,k)
template <typename F>
vc<ll> monotone_minima(int H, int W, F select) {
  vc<ll> min_col(H);
  auto dfs = [&](auto& dfs, int x1, int x2, int y1, int y2) -> void {
    if (x1 == x2) return;
    int x = (x1 + x2) / 2;
    int best_y = y1;
    for (int y = y1 + 1; y < y2; ++y) {
      if (select(x, best_y, y)) best_y = y;
    }
    min_col[x] = best_y;
    dfs(dfs, x1, x, y1, best_y + 1);
    dfs(dfs, x + 1, x2, best_y, y2);
  };
  dfs(dfs, 0, H, 0, W);
  return min_col;
}

vc<ll> min_plus_convolution(vc<ll> A, vc<ll> B) {
  int N = A.size(), M = B.size();
  // B is convex
  for (int i = 0; i < M - 2; ++i) assert(B[i] + B[i + 2] >= 2 * B[i + 1]);
  auto select = [&](int i, int j, int k) -> bool {
    if (i < k) return false;
    if (i - j >= M) return true;
    return A[j] + B[i - j] >= A[k] + B[i - k];
  };
  vc<ll> J = monotone_minima(N + M - 1, N, select);
  vc<ll> C(N + M - 1);
  for (int i = 0; i < N + M - 1; ++i) {
    int j = J[i];
    C[i] = A[j] + B[i - j];
  }
  return C;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(nullptr);
  int N, W;
  cin >> N >> W;
  vector<ll> dp(W + 1, 1e18);
  dp[0] = 0;
  // max
  for (int i = 0; i < N; i++) {
    int w;
    ll v;
    cin >> w >> v;
    for (int d = 0; d < w; d++) {
      vector<ll> cost;
      vector<ll> pdp;
      for (int x = d; x <= W; x += w) {
        int cnt = x / w;
        cost.push_back(-(v * cnt - cnt * cnt));
        pdp.push_back(dp[x]);
      }
      vector<ll> ndp = min_plus_convolution(pdp, cost);
      for (int x = d; x <= W; x += w) {
        dp[x] = ndp[x / w];
      }
    }
  }
  ll ans = 0;
  for (int i = 0; i <= W; i++) {
    ans = max(ans, -dp[i]);
  }
  cout << (ans) << '\n';
}
