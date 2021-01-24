#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g, g_or;
vector<bool> used;

void dfs(int v) {
  used[v] = true;

  for (int to : g_or[v]) {
    if (!used[to]) {
      dfs(to);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int m, n;
  cin >> m >> n;

  g.resize(n + m);
  g_or.resize(n + m);
  used.resize(n + m);

  for (int i = 0; i < m; i++) {
    int k;
    cin >> k;

    for (int j = 0; j < k; j++) {
      int to;
      cin >> to;
      to = to - 1 + m;

      g[i].push_back(to);
      g[to].push_back(i);
    }
  }

  vector<int> free;
  for (int i = 0; i < m; i++) {
    int edge;
    cin >> edge;

    if (edge != 0) {
      edge = edge - 1 + m;
    } else {
      edge = -1;
    }

    if (edge == -1) {
      free.push_back(i);
    }

    for (int to : g[i]) {
      if (to == edge) {
        g_or[to].push_back(i);
      } else {
        g_or[i].push_back(to);
      }
    }
  }

  for (int vertex : free) {
    dfs(vertex);
  }

  vector<int> fir, sec;
  int ans = 0;
  for (int i = 0; i < m; i++) {
    if (!used[i]) {
      ans++;
      fir.push_back(i + 1);
    }
  }

  for (int i = m; i < m + n; i++) {
    if (used[i]) {
      ans++;
      sec.push_back(i - m + 1);
    }
  }

  cout << ans << '\n';

  cout << fir.size();
  for (int vertex : fir) {
    cout << ' ' << vertex;
  }
  cout << '\n';

  cout << sec.size();
  for (int vertex : sec) {
    cout << ' ' << vertex;
  }

  return 0;
}
