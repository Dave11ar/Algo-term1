#include <bits/stdc++.h>

using namespace std;

const long long mod = 1e9;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;

  vector<int> vec(n);
  for (int i = 0; i < n; i++) {
    cin >> vec[i];
  }

  vector<vector<long long>> dp(n, vector<long long>(n));
  for (int i = 0; i < n; i++) {
    dp[i][i] = 1;
  }

  for (int j = 1; j < n; j++) {
    for (int i = j - 1; i >= 0; i--) {
      if (vec[i] == vec[j]) {
        dp[i][j] = dp[i + 1][j] + dp[i][j - 1] + 1;
      } else {
        dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
      }

      dp[i][j] = (dp[i][j] +  mod) % mod;
    }
  }

  cout << dp[0][n - 1];

  return 0;
}
