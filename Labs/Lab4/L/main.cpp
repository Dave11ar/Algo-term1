#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<pair<int, int>>> g;
vector<vector<long long>> dp;

void dfs(int v, int p) {
  long long full_sum = 0;

  for (int i = 0; i < (int)g[v].size(); i++) {
    if (g[v][i].first != p) {
      dfs(g[v][i].first, v);

      long long mx = max(dp[g[v][i].first][0], dp[g[v][i].first][1]);
      dp[v][0] += mx; full_sum += mx;
    }
  }

  long long max_dp1 = -1;

  for (int i = 0; i < (int)g[v].size(); i++) {
    long long mx = full_sum -
        max(dp[g[v][i].first][0], dp[g[v][i].first][1])
        + dp[g[v][i].first][0] + g[v][i].second;

    if (g[v][i].first != p && mx > max_dp1) {
      max_dp1 = mx;
    }
  }
  dp[v][1] = max_dp1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("matching.in", "r", stdin);
  freopen("matching.out", "w", stdout);

  cin >> n;

  g.resize(n);
  dp.resize(n, vector<long long>(2));

  for (int i = 1; i < n; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    x--; y--;

    g[x].push_back({ y , w });
    g[y].push_back({ x , w });
  }

  dfs(0, 0);

  cout << max(dp[0][0], dp[0][1]);

  return 0;
}
