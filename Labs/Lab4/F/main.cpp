#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  string P, S;
  getline(cin, P);
  getline(cin, S);

  vector<vector<bool>> dp((int)P.length() + 1,
      vector<bool>((int)S.length() + 1));

  dp[0][0] = true;
  if ((int)P.size() > 0 && P[0] == '*') {
    for (int j = 0; j < (int)S.size(); j++) {
      dp[1][j] = true;
    }
  }

  if ((int)S.length() == 0) {
    for (int i = 0; i < (int)P.length(); i++) {
      if (P[i] != '*') {
        cout << "NO";
        return 0;
      }
    }
    cout << "YES";
    return 0;
  }

  for (int i = 1; i <= (int)P.length(); i++) {
    for (int j = 0; j <= (int)S.length(); j++) {
      int v = i - 1, u = j - 1;

      if (P[v] == '*') {
        if (j > 0) {
          dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
          continue;
        }
        dp[i][j] = dp[i - 1][j];
      } else if (P[v] == '?') {
        if (j > 0) {
          dp[i][j] = dp[i - 1][j - 1];
        }
      } else {
        if (j > 0) {
          dp[i][j] = dp[i - 1][j - 1] && (P[v] == S[u]);
        }
      }
    }
  }

  cout << (dp[(int)P.length()][(int)S.length()] ? "YES" : "NO");

  return 0;
}
