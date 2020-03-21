#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("levenshtein.in", "r", stdin);
  freopen("levenshtein.out", "w", stdout);
  string s1, s2;
  cin >> s1 >> s2;

  int m = s1.length(), n = s2.length();
  s1 = " " + s1; s2 = " " + s2;

  vector<vector<int>> dp(m + 1, vector<int>(n + 1));
  dp[0][0] = 0;
  for (int j = 1; j <= n; j++) dp[0][j] = j;
  for (int i = 1; i <= m; i++) dp[i][0] = i;

  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      dp[i][j] = min(min(dp[i - 1][j] + 1, dp[i][j - 1] + 1),
          dp[i - 1][j - 1] + (s1[i] == s2[j] ? 0 : 1));
    }
  }

  cout << dp[m][n];

  return 0;
}
