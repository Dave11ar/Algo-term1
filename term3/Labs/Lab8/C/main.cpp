#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int>>> g;
vector<int> sorted, dp;
vector<bool> used;

void top_sort(int v) {
  used[v] = true;

  for (auto & i : g[v]) {
    if (!used[i.first]) {
      top_sort(i.first);
    }
  }
  sorted.push_back(v);
}

void dfs(int v) {
  used[v] = true;

  for (auto & i : g[v]) {
    if (!used[i.first]) {
      dfs(i.first);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m, s, t;
  cin >> n >> m >> s >> t;
  s--; t--;
  g.resize(n);
  dp.resize(n, INT_MAX);
  used.resize(n);

  for (int i = 0; i < m; i++) {
    int l, r, w;
    cin >> l >> r >> w;
    l--; r--;

    g[l].push_back({r, w});
  }

  top_sort(s);
  reverse(sorted.begin(), sorted.end());

  dp[s] = 0;
  for (int i : sorted) {
    for (size_t j = 0; j < g[i].size(); j++) {
      dp[g[i][j].first] = min(dp[g[i][j].first], dp[i] + g[i][j].second);
    }
  }

  if (dp[t] == INT_MAX) {
    cout << "Unreachable";
  } else {
    cout << dp[t];
  }

  return 0;
}
