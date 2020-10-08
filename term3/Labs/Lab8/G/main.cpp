#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> g;
vector<bool> used;
vector<int> ans;
int k = 1;

void dfs(int v) {
  used[v] = true;
  ans[v] = k;

  for (size_t i = 0; i < g[v].size(); i++) {
    if (!used[g[v][i]]) {
      dfs(g[v][i]);
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
  ans.resize(n);

  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    l--; r--;

    g[l].push_back(r);
    g[r].push_back(l);
  }

  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      dfs(i);
      k++;
    }
  }

  cout << k - 1 << '\n';
  for (int i = 0; i < n; i++) {
    cout << ans[i] << ' ';
  }

  return 0;
}
