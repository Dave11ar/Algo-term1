#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> g, c, f;
vector<int> d, p;

bool bfs() {
  p[0] = 0;
  d[0] = 0;
  for (int i = 1; i < n; i++) {
    p[i] = 0;
    d[i] = INT_MAX;
  }

  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : g[u]) {
      if (f[u][v] < c[u][v] && d[v] == INT_MAX) {
        d[v] = d[u] + 1;
        q.push(v);
      }
    }
  }

  return d[n - 1] != INT_MAX;
}

int dfs(int u, int min_c) {
  if (u == n - 1 || min_c == 0) {
    return min_c;
  }

  for (size_t i = p[u]; i < g[u].size(); i++) {
    int v = g[u][i];

    if (d[v] == d[u] + 1) {
      int flow_sz = dfs(v, min(min_c, c[u][v] - f[u][v]));

      if (flow_sz != 0) {
        f[u][v] += flow_sz;
        f[v][u] -= flow_sz;
        return flow_sz;
      }
    }
    p[u]++;
  }

  return 0;
}

int64_t dinic() {
  int64_t max_flow = 0;

  while (bfs()) {
    int cur_flow = dfs(0, INT_MAX);

    while (cur_flow != 0) {
      max_flow += cur_flow;
      cur_flow = dfs(0, INT_MAX);
    }
  }

  return max_flow;
}

void find_ST() {
  dinic();
  vector<int> ans;
  for (int i = 0; i < n; i++) {
    if (d[i] != INT_MAX) {
      ans.push_back(i);
    }
  }

  cout << ans.size() << '\n';
  for (int i : ans) {
    cout << i + 1<< ' ';
  }
}

void input() {
  cin >> n >> m;

  g.resize(n);
  d.resize(n);
  p.resize(n);
  c.resize(n, vector<int>(n));
  f.resize(n, vector<int>(n));

  for (int i = 0; i < m; i++) {
    int l, r, cl;
    cin >> l >> r >> cl;
    l--; r--;

    g[l].push_back(r);
    g[r].push_back(l);
    c[l][r] += cl;
    c[r][l] += cl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  find_ST();

  return 0;
}
