// https://codeforces.com/blog/entry/11080

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type,

             // less<int>,
             // set

             less_equal<int>,
             // multiset

             rb_tree_tag, tree_order_statistics_node_update>
    ordered_set;

class Solution {
 public:
  vector<int> resultsArray(vector<vector<int>>& q, int k) {
    ordered_set t;
    const int m = q.size();
    vector<int> ans(m);
    for (int i = 0; i < m; ++i) {
      t.insert(abs(q[i][0]) + abs(q[i][1]));
      if (i < k - 1) {
        ans[i] = -1;
        continue;
      }
      ans[i] = *t.find_by_order(k - 1);
    }
    return ans;
  }
};
