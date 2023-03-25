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
    for (auto& i : s) i = tolower(i);
  };
  auto stoupper = [](string& s) {
    for (auto& i : s) i = toupper(i);
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

    int sz = cs.size();
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
      for (auto& j : p) {
        stolower(sp[1]);
        stolower(j);
        if (sp[1].find(j) != string::npos) {
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

