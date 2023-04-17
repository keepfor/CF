#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include"./lib/debug.h"
#else 
#define debug(...) 
#endif

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int TESTCASE = 1;
  auto stolower = [](string& s) {
    for (auto& i : s) i = char(tolower(i));
  };
  auto stoupper = [](string& s) {
    for (auto& i : s) i = char(toupper(i));
  };
  while (TESTCASE--) {
    unordered_map<string, vector<string>> all;
    vector<string> p{"uisp","usw", "usp", "uled", "uacc", "uis", "usc"};

    vector<string> cs;
    string s;

    while (getline(cin, s)) {
      if (s.find("TWFCD") != string::npos) break;
      cs.push_back(s);
    }
    sort(cs.begin(), cs.end());

    int sz = (int) cs.size();
    int ix = 0;
    debug(sz);
    
    cs[ix] = s + ", " + cs[ix];
    ++ix;
    while (getline(cin, s)) {
      cs[ix] = s + ", " + cs[ix];
      ++ix;
    }
    for (auto& i : cs) {
      vector<string> sp;
      string ss;
      stringstream x(i); 
      while (getline(x, ss, ',')) {
        sp.push_back(ss);
      }
      bool ok = false;
      stolower(sp[1]);
      for (auto& j : p) {
        stolower(j);
        if (sp[1].find(j) != string::npos) {

          string ii = i;
          stolower(ii);
          auto it = ii.find(sp[1]);
          for (int k = 0; k < (int) sp[1].size(); ++k) {
            i[it + k] = char(toupper(i[it + k])); 
          }

          all[j].push_back(i);
          --sz;
          ok = true;
          break;
        }
      }
      if (!ok) debug("no", sp);
    }
    debug(sz);
    assert(!sz);
    for (auto& [x, y] : all) {
      string xx = x;
      stoupper(xx);
      cout << xx << '\n';
      for (auto& z : y) {
        cout << z << '\n';
      }
      cout << '\n';
    }
  }
  return 0;
}