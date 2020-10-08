#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<bool> used;
vector<bool> wins;

// true -- first win
// false -- second win
void dfs(int v) {
  used[v] = true;

  if (g[v].empty()) {
    wins[v] = false;
    return;
  }

  for (int i = 0; i < (int)g[v].size(); i++) {
    if (!used[g[v][i]]) {
      dfs(g[v][i]);
    }
    if (!wins[g[v][i]]) {
      wins[v] = true;
      return;
    }
  }

  wins[v] = false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m, s;
  cin >> n >> m >> s;

  s--;
  g.resize(n);
  used.resize(n);
  wins.resize(n);

  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    l--; r--;

    g[l].push_back(r);
  }

  dfs(s);

  if (wins[s]) {
    cout << "First player wins";
  } else {
    cout << "Second player wins";
  }

  return 0;
}
