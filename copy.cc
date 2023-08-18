
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

const int MAX_N = 100005;

map<pair<int, int>, int> freq;
struct Tuple {
  int x, y, z;
  inline bool operator<(const Tuple &other) const {
    if (x == other.x && z == other.z) {
      return y < other.y;
    }
    if (x == other.x) {
      return z < other.z;
    }
    return x < other.x;
  }
} tuples[MAX_N];

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> tuples[i].x >> tuples[i].y;
    if (!freq.count({tuples[i].x, tuples[i].y})) {
      freq[{tuples[i].x, tuples[i].y}] = 0;
    } else {
      freq[{tuples[i].x, tuples[i].y}] += 1;
    }
    tuples[i].z = freq[{tuples[i].x, tuples[i].y}];
  }
  sort(tuples + 1, tuples + n + 1);
  for (int i = 1; i <= n; ++i) {
    cout << tuples[i].x << ' ' << tuples[i].y << ' ' << tuples[i].z << '\n';
  }
  for (int i = 1; i <= n; ++i) {
    cout << tuples[i].x << " " << tuples[i].y << "\n";
  }
  return 0;
}
