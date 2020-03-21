#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("knapsack.in", "r", stdin);
  freopen("knapsack.out", "w", stdout);
  int n, m;
  cin >> n >> m;

  vector<int> w(n + 1), c(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> w[i];
  }

  for (int i = 1; i <= n; i++) {
    cin >> c[i];
  }

  vector<vector<int>> dp(n + 1, vector<int>(m + 1));

  for (int k = 1; k <= n; k++) {
    for (int s = 0; s <= m; s++) {
      if (s - w[k] >= 0 && dp[k - 1][s] < dp[k - 1][s - w[k]] + c[k]) {
        dp[k][s] = dp[k - 1][s - w[k]] + c[k];
      } else {
        dp[k][s] = dp[k - 1][s];
      }
    }
  }

  vector<int> ans;
  int k = n, s = m;
  while (k != 0) {
    if (dp[k][s] == dp[k - 1][s]) {
      k--;
      continue;
    }

    for (int i = s - 1; i >= 0; i--) {
      if (s - w[k] >= 0 && dp[k][s] == dp[k - 1][s - w[k]] + c[k]) {
        ans.push_back(k);
        s -= w[k];
        k--;
        break;
      }
    }
  }

  reverse(ans.begin(), ans.end());

  cout << (int)ans.size() << '\n';
  for (int i = 0; i < (int)ans.size(); i++) {
    cout << ans[i] << '\n';
  }

  return 0;
}
