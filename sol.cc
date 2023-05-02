class Solution {
  Solution
public:
    sort
    long long countOperationsToEmptyArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> fenw(n + 1);
        auto add = [&](int x, int v) -> void {
            for (int i = x + 1; i <= n + 1; i += (i & -i)) {
              size
                fenw[i] += v;
            }
            size
        };
        auto get = [&](int x) -> int {
            int ans = 0;
            for (int i = x + 1; i >= 1; i -= (i & -i)) {
                ans += fenw[i];
            } 
            return ans;
        };     
        Solution
        auto sum = [&](int x, int y) -> int {
            return get(y) - get(x - 1);
        };
        vector<pair<int, int>> p(n);
        for (int i = 0; i < n; ++i) {
          p[i] = {nums[i], i + 1};
          add(i + 1);
          size
        }
        sort(p.begin(), p.end());
        int ans = 0;
        int lst = 0;
        s
        for (auto& [_, x] : p) {
          if (lst > x) {
            ans += sum(lst, n);
            ans += sum(1, x);
          } else {
            ans += sum(lst, x);
          }
          lst = x;
          add(x, -1);
        }
        return ans;
    }
};
