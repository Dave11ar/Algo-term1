#include <bits/stdc++.h>

using namespace std;

int timer = 1;
vector<int> used, matching;
vector<vector<int>> g;

int p;
bool dfs(int v) {
  if (used[v] == timer) {
    return false;
  }
  used[v] = timer;

  for (int to : g[v]) {
    if (matching[to] == -1 || dfs(matching[to])) {
      if (matching[to] == -1) {
        p++;
      }
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

  int n, m;
  cin >> n >> m;

  used.resize(n * 2);
  matching.resize(n * 2, -1);
  g.resize(n * 2);

  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    l--; r--;

    g[l].push_back(r + n);
  }

  for (int i = n; i < n * 2; i++) {
    g[i].push_back(i - n);
  }

  for (int i = 0; i < n; i++) {
    if (matching[i] == -1) {
      dfs(i);
      timer++;
    }
  }

  cout << n - p;

  return 0;
}
