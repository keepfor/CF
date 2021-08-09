#include<bits/stdc++.h>
using namespace std;
int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  auto t1 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 1e9; ++i);
  auto t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = t2 - t1;
  std::cout << "duration: " << elapsed.count() << " ms" << std::endl;
  return 0;
}

