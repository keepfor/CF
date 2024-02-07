#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
  long long maximumSubarraySum(vector<int>& v, int k) {
    using ll = long long;
    map<ll, ll> vis;
    const int n = v.size();
    const ll inf = 1e15;
    ll ans = -inf;
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
      if (vis.count(v[i])) {
        vis[v[i]] = min(vis[v[i]], sum);
      } else {
        vis[v[i]] = sum;
      }
      sum += (ll)v[i];
      if (vis.count(v[i] - k)) {
        ans = max(ans, sum - vis[v[i] - k]);
      }
      if (vis.count(v[i] + k)) {
        ans = max(ans, sum - vis[v[i] + k]);
      }
    }
    if (ans <= -inf) {
      ans = 0;
    }
    return ans;
  }
};

void SolveOne() {
  Solution s;
  vector<int> v{1, 2, 3, 4, 5, 6};
  debug(s.maximumSubarraySum(v, 1));
};

void SolveAll() {
  int t{1};
  // cin >> t;
  while (t--) {
    SolveOne();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

signed main() {
  SetIO();
  SolveAll();
  return 0;
}
