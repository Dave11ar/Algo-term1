#include <bits/stdc++.h>

using namespace std;

int timer = 1;
vector<int> used, matching;
vector<vector<int>> g;

bool dfs(int v) {
  if (used[v] == timer) {
    return false;
  }
  used[v] = timer;

  for (int to : g[v]) {
    if (matching[to] == -1 || dfs(matching[to])) {
      matching[to] = v;
      matching[v] = to;
      return true;
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;

  used.resize(n + m);
  matching.resize(n + m, -1);
  g.resize(n + m);

  for (int i = 0; i < k; i++) {
    int l, r;
    cin >> l >> r;
    l--; r = r - 1 + n;

    g[l].push_back(r);
    g[r].push_back(l);
  }

  for (int i = 0; i < n; i++) {
    if (matching[i] == -1) {
      dfs(i);
      timer++;
    }
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (matching[i] != -1) {
      ans++;
    }
  }
  cout << ans;

  return 0;
}