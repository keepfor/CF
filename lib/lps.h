#include <bits/stdc++.h>
using namespace std;
class LPS {
 public:
  vector<int> get(string& l) {
    vector<int> p(l.size(), 0);
    for (int i = 1; i < l.size(); i++) {
      int j = p[i - 1];
      while (j > 0 && l[i] != l[j]) j = p[j - 1];
      p[i] = (j += l[i] == l[j]);
    }
    return p;
  }
};
