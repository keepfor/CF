#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...) 7
#endif

#include <bits/stdc++.h>

using namespace std;

struct P {
  string s;
  int t;
  int p;
  int g;
  P() {
    s = "";
    t = p = g = 0;
  }
};

void SolveOne() {
  int n;
  cin >> n;
  vector<P> v;
  int mxt = 0;
  int mxp = 0;
  int mxg = 0;
  while (n--) {
    int m;
    string s;
    cin >> m >> s;
    P p;
    p.s = s;
    while (m--) {
      string t;
      cin >> t;
      bool dec = 1;
      bool dif = 1;
      bool eq = 1;
      set<char> vis;
      char pre = -1;
      for (auto& i : t) {
        if (i == '-') {
          continue;
        }
        if (pre != -1 and i != pre) {
          eq = 0;
        }
        if (pre != -1 and i >= pre) {
          dec = 0;
        }
        pre = i;
        if (vis.count(i)) {
          dif = 0;
        }
        vis.insert(i);
      }
      if (eq) {
        p.t += 1;
      } else if (dec and dif) {
        p.p += 1;
      } else {
        p.g += 1;
      }
    }
    v.push_back(p);
    mxt = max(p.t, mxt);
    mxp = max(p.p, mxp);
    mxg = max(p.g, mxg);
  }
  {
    cout << "If you want to call a taxi, you should call: ";
    vector<P> t;
    for (auto& i : v) {
      if (i.t == mxt) {
        t.push_back(i);
      }
    }
    const int z = t.size();
    for (int i = 0; i < z; ++i) {
      cout << t[i].s;
      if (i != z - 1) {
        cout << ", ";
      } else {
        cout << ".\n";
      }
    }
  }
  {
    cout << "If you want to order a pizza, you should call: ";
    vector<P> t;
    for (auto& i : v) {
      if (i.p == mxp) {
        t.push_back(i);
      }
    }
    const int z = t.size();
    for (int i = 0; i < z; ++i) {
      cout << t[i].s;
      if (i != z - 1) {
        cout << ", ";
      } else {
        cout << ".\n";
      }
    }
  }
  {
    cout << "If you want to go to a cafe with a wonderful girl, you should "
            "call: ";
    vector<P> t;
    for (auto& i : v) {
      if (i.g == mxg) {
        t.push_back(i);
      }
    }
    const int z = t.size();
    for (int i = 0; i < z; ++i) {
      cout << t[i].s;
      if (i != z - 1) {
        cout << ", ";
      } else {
        cout << ".\n";
      }
    }
  }
};

void SolveAll() {
  int t = 1;
  // cin >> t;
  while (t--) {
    SolveOne();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

int32_t main() {
  SetIO();
  SolveAll();
  return 0;
}
