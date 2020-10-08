#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g_c, g_t;
vector<int> sorted, ans;
vector<bool> used;
int cur = 1;

void top_sort(int v) {
  used[v] = true;

  for (size_t i = 0; i < g_c[v].size(); i++) {
    if (!used[g_c[v][i]]) {
      top_sort(g_c[v][i]);
    }
  }
  sorted.push_back(v);
}

void dfs(int v) {
  ans[v] = cur;

  for (size_t i = 0; i < g_t[v].size(); i++) {
    if (ans[g_t[v][i]] == 0) {
      dfs(g_t[v][i]);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  g_c.resize(n);
  g_t.resize(n);
  ans.resize(n);
  used.resize(n);

  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    l--; r--;

    g_c[l].push_back(r);
    g_t[r].push_back(l);
  }

  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      top_sort(i);
    }
  }
  reverse(sorted.begin(), sorted.end());

  for (int i = 0; i < n; i++) {
    if (ans[sorted[i]] == 0) {
      dfs(sorted[i]);
      cur++;
    }
  }

  cout << cur - 1 << '\n';

  for (int i = 0; i < n; i++) {
    cout << ans[i] << ' ';
  }

  return 0;
}
