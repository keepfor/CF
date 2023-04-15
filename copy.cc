#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include"lib/debug.h"
#else
#define debug(...) 
#endif

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int TESTCASES = 1;
  cin >> TESTCASES;
  while (TESTCASES--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto & i : a) 
        cin >> i;

    long long sum = 0;
    for (int i = 0; i < n; ++i) 
        if (i % 2 == 0 and i + 1 < n)
            sum += 1ll * a[i + 1] - a[i];

    if (n % 2 == 0 and sum < 0) 
        cout << "NO";
    else 
        cout << "Yes";

    cout << '\n';
  }
  return 0;
}
