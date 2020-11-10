#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  vector<bool> used(n);
  vector<int> d(n, INT_MAX);

  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    l--; r--;

    g[l].push_back(r);
    g[r].push_back(l);
  }

  queue<int> q;
  q.push(0);
  used[0] = true;
  d[0] = 0;

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (int to : g[v]) {
      if (!used[to]) {
        used[to] = true;
        q.push(to);

        d[to] = d[v] + 1;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    cout << d[i] << ' ';
  }
  return 0;
}
