class Solution {
 public:
  int isWinner(vector<int>& player1, vector<int>& player2) {
    int n = player1.size();
    int a = 0;
    for (int i = 0, c = 0; i < n; ++i) {
      if (c) {
        a += 2 * player1[i];
        --c;
      } else {
        a += player1[i];
      }
      if (player1[i] == 10) {
        c = 2;
      }
    }
    int b = 0;
    for (int i = 0, c = 0; i < n; ++i) {
      if (c) {
        b += 2 * player2[i];
        --c;
      } else {
        b += player2[i];
      }
      if (player2[i] == 10) {
        c = 2;
      }
    }
    if (a > b) {
      return 1;
    } else if (a < b) {
      return 2;
    }
    return 0;
  }
};
