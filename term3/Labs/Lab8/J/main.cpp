#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> g;
vector<bool> used, color;

void dfs(int v) {
  used[v] = true;

  for (size_t i = 0; i < g[v].size(); i++) {
    if (!used[g[v][i]]) {
      color[g[v][i]] = !color[v];
      dfs(g[v][i]);
    } else {
      if (color[v] == color[g[v][i]]) {
        cout << "NO";
        exit(0);
      }
    }
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> m;
  g.resize(n);
  used.resize(n);
  color.resize(n);

  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    l--; r--;

    g[l].push_back(r);
    g[r].push_back(l);
  }

  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      color[i] = false;
      dfs(i);
    }
  }

  cout << "YES";

  return 0;
}
