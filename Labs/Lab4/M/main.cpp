#include<bits/stdc++.h>

using namespace std;

bool contains(int mask, int n) {
  return ((mask >> n) & 1) == 1;
}

const long long  INF = 1e18;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("salesman.in", "r", stdin);
  freopen("salesman.out", "w", stdout);

  int n, m;
  cin >> n >> m;

  int mask_size = 1 << n;

  vector<vector<long long>> g(n, vector<long long>(n, -1)),
                      dp(n, vector<long long>(mask_size, INF));

  for (int i = 0; i < m; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    a--; b--;

    g[a][b] = w;
    g[b][a] = w;
  }

  for (int i = 0; i < n; i++) {
    dp[i][1 << i] = 0;
  }

  for (int mask = 1; mask < mask_size; mask++) {
    for (int i = 0; i < n; i++) {
      if (!contains(mask, i)) {
        continue;
      }
      int new_mask = mask - (1 << i);

      for (int j = 0; j < n; j++) {
        if (contains(new_mask, j) && g[j][i] != -1) {
          dp[i][mask] = min(dp[i][mask], dp[j][new_mask] + g[j][i]);
        }
      }
    }
  }

  long long ans = INF;
  for (int i = 0; i < n; i++) {
    ans = min(ans, dp[i][mask_size - 1]);
  }

  cout << (ans == INF ? -1 : ans);

  return 0;
}
