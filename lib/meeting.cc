#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "./lib/debug.h"
#else
#define debug(...)
#endif

static inline void lowStr(string& s) {
  for (auto& i : s) {
    i = char(tolower(i));
  }
}

static inline void upStr(string& s) {
  for (auto& i : s) {
    i = char(toupper(i));
  }
}

static inline void readSortedPair(vector<pair<string, string>>& csp, int& sz) {
  string s;

  while (getline(cin, s)) {
    if (s.find("TWFCD") != string::npos) break;
    csp.emplace_back("", s);
  }

  sz = (int)csp.size();
  int ix = 0;
  cout << "Count = " << sz << '\n';

  csp[ix] = {csp[ix].second, s + ", " + csp[ix].second};
  ++ix;
  while (getline(cin, s)) {
    csp[ix] = {csp[ix].second, s + ", " + csp[ix].second};
    ++ix;
  }
  sort(csp.begin(), csp.end(),
       [&](const pair<string, string>& lhs, const pair<string, string>& rhs) {
         string l = lhs.first;
         string r = rhs.first;
         lowStr(l);
         lowStr(r);
         return l < r;
       });
}

static inline void getList(vector<pair<string, string>>& csp,
                           vector<string>& cs, int& sz) {
  for (int i = 0; i < sz; ++i) {
    cs[i] = csp[i].second;
  }
}

static inline void getSplit(string& i, vector<string>& sp) {
  string ss;
  stringstream x(i);

  while (getline(x, ss, ',')) {
    sp.push_back(ss);
  }
}

static inline void upProName(string& i, string& ii, vector<string>& sp) {
  auto it = ii.find(sp[1]);
  for (int k = 0; k < (int)sp[1].size(); ++k) {
    i[it + k] = char(toupper(i[it + k]));
  }
}

static inline void classify(const vector<string>& pdline, vector<string>& cs,
                            map<string, vector<string>>& all, int& sz) {
  for (auto& i : cs) {
    vector<string> sp;
    getSplit(i, sp);

    bool ok = false;
    lowStr(sp[1]);

    for (auto& jj : pdline) {
      string j = jj;
      lowStr(j);

      if (sp[1].find(j) != string::npos) {
        string ii = i;
        lowStr(ii);

        upProName(i, ii, sp);
        all[j].push_back(i);

        --sz;
        ok = true;
        break;
      }
    }
    assert(ok && "No productline match");
  }
}

static inline void outP(const map<string, vector<string>>& all) {
  for (auto& [x, y] : all) {
    string xx = x;
    upStr(xx);
    cout << xx << '\n';

    for (auto& z : y) {
      cout << z << '\n';
    }
    cout << '\n';
  }
}

static inline void shoudZero(int& sz) { assert(!sz && "Should be Zero\n"); }

static inline void genReport() {
  const vector<string> pdline{"uisp", "usw", "usp", "uled",
                              "uacc", "uis", "usc", "ev"};

  int sz = 0;
  map<string, vector<string>> all;
  vector<pair<string, string>> csp;
  vector<string> cs;

  readSortedPair(csp, sz);
  cs.resize(sz);
  getList(csp, cs, sz);

  classify(pdline, cs, all, sz);
  shoudZero(sz);
  outP(all);
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int TESTCASE = 1;
  while (TESTCASE--) {
    genReport();
  }
  return 0;
}
