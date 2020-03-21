#include <bits/stdc++.h>

using namespace std;

bool comp(string *s1, string *s2) {
  if ((int) (*s1).length() > (int) (*s2).length()) {
    return true;
  }
  if ((int) (*s1).length() < (int) (*s2).length()) {
    return false;
  }

  for (int i = 0; i < (int) (*s1).length(); i++) {
    if ((*s1)[i] - '0' > (*s2)[i] - '0') {
      return true;
    }
    if ((*s1)[i] - '0' < (*s2)[i] - '0') {
      return false;
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  //freopen("number.in", "r", stdin);
  //freopen("number.out", "w", stdout);

  int n;
  cin >> n;

  vector<vector<string>> dp(n + 1, vector<string>(n + 1, "a"));

  for (int i = 0; i <= n && i <= 9; i++) {
    dp[i][i % n] = to_string(i);
  }

  for (int sum = 0; sum <= n; sum++) {
    for (int bal = n - 1; bal >= 0; bal--) {
      if (dp[sum][bal] == "a") {
        continue;
      }
      for (int last = 0; last <= 9; last++) {
        if (sum + last > n) {
          break;
        }
        string s = dp[sum][bal] + to_string(last);

        if (dp[sum + last][(bal * 10 + last) % n] != "a" &&
            !comp(&dp[sum + last][(bal * 10 + last) % n], &s)) {
          continue;
        }

        dp[sum + last][(bal * 10 + last) % n] = dp[sum][bal] + to_string(last);
      }
    }
  }

  cout << dp[n][0];

  return 0;
}
