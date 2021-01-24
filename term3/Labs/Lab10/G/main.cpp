#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<vector<int>> used;
vector<int> ans;

void path(int v) {
  while (!g[v].empty()) {
    if (used[v][g[v].back()] != 0) {
      used[v][g[v].back()]--;
      used[g[v].back()][v]--;

      path(g[v].back());
    } else {
      g[v].pop_back();
    }
  }

  ans.push_back(v);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  g.resize(n);
  used.resize(n, vector<int>(n));

  vector<int> odd;
  for (int i = 0; i < n; i++) {
    int m;
    cin >> m;
    if (m % 2 != 0) {
      odd.push_back(i);
    }

    for (int j = 0; j < m; j++) {
      int to;
      cin >> to;
      to--;

      g[i].push_back(to);
      used[i][to]++;
    }
  }

  if (odd.size() == 1 || odd.size() > 2) {
    cout << -1;
    return 0;
  }

  path(odd.empty() ? 0 : odd[0]);

  cout << ans.size() - 1 << '\n';

  for (int v : ans) {
    cout << v + 1 << ' ';
  }

  return 0;
}
