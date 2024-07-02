#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "./lib/debug.h"
#else
#define debug(...)
#endif

static void lowStr(string& s) {
  for (auto& i : s) {
    i = char(tolower(i));
  }
}

static void upStr(string& s) {
  for (auto& i : s) {
    i = char(toupper(i));
  }
}

static void ReadSortReturnPair(vector<pair<string, string>>& product_task_pair,
                               int& sz) {
  string s;

  while (getline(cin, s)) {
    if (s.find("TWFCD") != string::npos) break;
    product_task_pair.emplace_back("", s);
  }

  sz = (int)product_task_pair.size();
  int ix = 0;
  cout << "Count = " << sz << '\n';

  product_task_pair[ix] = {product_task_pair[ix].second,
                           s + ", " + product_task_pair[ix].second};
  ++ix;
  while (getline(cin, s)) {
    product_task_pair[ix] = {product_task_pair[ix].second,
                             s + ", " + product_task_pair[ix].second};
    ++ix;
  }
  sort(product_task_pair.begin(), product_task_pair.end(),
       [&](const pair<string, string>& lhs, const pair<string, string>& rhs) {
         string l = lhs.first;
         string r = rhs.first;
         lowStr(l);
         lowStr(r);
         return l < r;
       });
}

static void Get_all_tasks(vector<pair<string, string>>& csp, vector<string>& cs,
                          int& sz) {
  for (int i = 0; i < sz; ++i) {
    cs[i] = csp[i].second;
  }
}

static void getSplit(string& i, vector<string>& sp) {
  string ss;
  stringstream x(i);

  while (getline(x, ss, ',')) {
    sp.push_back(ss);
  }
}

static void upProName(string& i, string& ii, vector<string>& sp) {
  auto it = ii.find(sp[1]);
  for (int k = 0; k < (int)sp[1].size(); ++k) {
    i[it + k] = char(toupper(i[it + k]));
  }
}

static void ClassifyByProductline(const vector<string>& pdline,
                                  vector<string>& cs,
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

static void PrintByProductline(
    const map<string, vector<string>>& product_line_tasks) {
  for (auto& [product_line_, tickets] : product_line_tasks) {
    string product_line = product_line_;
    upStr(product_line);
    cout << product_line << '\n';

    auto tickets_ = tickets;
    sort(tickets_.begin(), tickets_.end(),
         [&](const auto& lhs, const auto& rhs) { return lhs < rhs; });

    for (auto& ticket : tickets_) {
      cout << ticket << '\n';
    }
    cout << '\n';
  }
}

static inline void LenOfSizeShoudZero(int& sz) {
  assert(!sz && "Should be Zero\n");
}

static void print_report() {
  const vector<string> All_product_lines{"uisp", "usw", "usp", "uled",
                                         "uacc", "uis", "usc", "ev"};

  int all_task_counts = 0;
  map<string, vector<string>> product_line_tasks;
  vector<pair<string, string>> product_task_pair;
  vector<string> all_tasks;

  ReadSortReturnPair(product_task_pair, all_task_counts);
  all_tasks.resize(all_task_counts);
  Get_all_tasks(product_task_pair, all_tasks, all_task_counts);

  ClassifyByProductline(All_product_lines, all_tasks, product_line_tasks,
                        all_task_counts);
  LenOfSizeShoudZero(all_task_counts);
  PrintByProductline(product_line_tasks);
}

static inline void FastIo() {
  ios::sync_with_stdio(false);
  cin.tie(0);
}

int32_t main() {
  FastIo();

  int test_count = 1;
  while (test_count--) {
    print_report();
  }

  return 0;
}
