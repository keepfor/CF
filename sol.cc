class Solution {
public:
    int numSubarraysWithSum(vector<int>& v, int x) {
      const int n = v.size();
      int c = 0;
      int ans = 0;
      for (int i = 0, j = 0; i < n; ++i) {
        if (v[i]) {
          --x;
          c = 0;
        } 
        while (x < 0) {
          x += v[j];
          ++j;
        }
        while (!x and j <= i) {
          x += v[j];
          ++j;
          ++c;
        }
        ans += c;
      }
      return ans;
    }
};
