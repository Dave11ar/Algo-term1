#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<pair<int, int>>> g;
vector<int> top_sort;
vector<bool> used;
vector<int> srt;

void dfs_top_sort(int v) {
  used[v] = true;

  for (auto to : g[v]) {
    if (!used[to.second]) {
      dfs_top_sort(to.second);
    }
  }
  top_sort.push_back(v);
}

void dfs(int v) {
  used[v] = true;
  if (!g[v].empty()) {
    dfs_top_sort(g[v][0].second);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> m;

  used.resize(n);
  g.resize(n);
  srt.resize(n);

  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    l--; r--;

    g[l].emplace_back(0, r);
  }

  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      dfs_top_sort(i);
    }
  }

  reverse(top_sort.begin(),  top_sort.end());

  for (int i = 0; i < n; i++) {
    srt[top_sort[i]] = i;
  }

  for (int i = 0; i < n; i++) {
    for (size_t j = 0; j < g[i].size(); j++) {
      g[i][j].first = srt[g[i][j].second];
    }
    sort(g[i].begin(), g[i].end());
  }
  used.assign(n, false);

  dfs(top_sort[0]);

  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      cout << "NO";
      return 0;
    }
  }

  cout << "YES";

  return 0;
}
