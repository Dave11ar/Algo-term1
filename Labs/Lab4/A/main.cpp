#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> dp, way;
string ans;

void res(int l, int r) {
  if (l >= r) {
    ans.push_back('A');
    return;
  }

  ans.push_back('(');

  res(l, way[l][r]);
  res(way[l][r] + 1, r);

  ans.push_back(')');
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("matrix.in", "r", stdin);
  freopen("matrix.out", "w", stdout);

  int n;
  cin >> n;
  vector<pair<int, int>> vec(n);
  for (int i = 0; i < n; i++) {
    cin >> vec[i].first >> vec[i].second;
  }
  dp.resize(n, vector<int>(n, 1e9));
  way.resize(n, vector<int>(n));


  for (int l = n - 1; l >= 0; l--) {
    dp[l][l] = 0;
    for (int r = l + 1; r < n; r++) {
      for (int k = l; k < r; k++) {
        int cur = dp[l][k] + dp[k + 1][r] + vec[l].first
            * vec[k].second * vec[r].second;
        if (cur < dp[l][r]) {
          dp[l][r] = cur;
          way[l][r] = k;
        }
      }
    }
  }

  res(0, n - 1);

  for (int i = 0; i < (int)ans.length(); i++) {
    cout << ans[i];
  }
  return 0;
}
