#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "lib/debug.h"
#else 
#define debug(...) 0
#endif

int32_t main() {
  ios::sync_with_stdio(false), cin.tie(0);

  auto solve = [&]() {
    const string pc_ip = "192.168.1.198";
    const string ap_ip = "192.168.1.40";
    const string dut_mac = "24:5A:4C:2F:EA:0B";
    const string default_clientID = "dbd2a0fe-2cb2-460d-a6e4-58e11cf7a8a2";

    string merge = "";

    for (auto& i : pc_ip) {
      if (i != '.') {
        merge += i;
      }
    }

    for (auto& i : ap_ip) {
      if (i != '.') {
        merge += i;
      }
    }

    for (auto& i : dut_mac) {
      if (i != ':') {
        merge += i;
      }
    }

    const int clientIdLen = (int) default_clientID.size();
    string FinalclinetID = "";

    for (int i = 0, j = 0; i < clientIdLen; ++i) {
      if (default_clientID[i] == '-' or j >= (int) merge.size()) {
        FinalclinetID += default_clientID[i];
        continue;
      }

      FinalclinetID += merge[j];
      ++j;
    }

    cout << "pc ip = " << pc_ip << '\n';
    cout << "ap ip = " << ap_ip << '\n';
    cout << "dut_mac = " << dut_mac << '\n';
    cout << "merge = " << merge << '\n';

    cout << "default client id = " << default_clientID << '\n';
    cout << "final client id = " << FinalclinetID << '\n';

  };

  {
    int tt = 1;
    while (tt--) {
      solve();
    }
  }

  return 0;
}
