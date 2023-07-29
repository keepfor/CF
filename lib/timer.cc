#include <bits/stdc++.h>
using namespace std;
#include <unistd.h>
int32_t main() {
  int count = 0;
  while (1) {
    int sec = count % 60;
    int min = count / 60;
    system("clear");
    cout << min << ':' << sec << '\n';
    usleep(1e6);
    ++count;
  }
  return 0;
}
