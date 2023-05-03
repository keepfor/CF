class Solution {
public:
    long long countOperationsToEmptyArray(vector<int>& nums) {
      int n = nums.size();
      vector<long long> f(n + 1);
      auto add = [&](int x, int v) -> void {
        for (int i = x; i <= n; i += (i & -i)) {
          f[i] += 1ll * v;
        }
      };
      auto get = [&](int x) -> long long {
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
        }
        for (int i = 0; i < n; ++i) {
        }
        auto sum = [&](int x, int y) {
          return get(y) - get(x - 1);
        };
        for (int i = x; i >= 1; i -= (i & -i)) {
          ans += 1ll * f[i];
        }
        return ans;
      };
      auto sum = [&](int x, int y) -> long long {
        return get(y) - get(x - 1);
      };
      vector<pair<int, int>> p(n);
      for (int i = 0; i < n; ++i) {
        p[i] = {nums[i], i + 1};
        add(i + 1);
      }
      long long ans = 0;
      sort(p.begin(), p.end());
      int lst = 0;
      for (auto& [_, i] : p) {
        if (lst > i) {
          ans += get(lst, n) + get(1, i);
        } else {
          ans += get(lst, i);
        }
        lst = i;
        add(i, -1);
      }
      return ans;
    }
};
