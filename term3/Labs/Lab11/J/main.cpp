#include <bits/stdc++.h>

using namespace std;

struct edge {
  int from;
  int to;
  int val;

  bool operator<(const edge &other) const {
    return val < other.val;
  }

  edge(int from, int to, int val)
    : from(from), to(to), val(val) {}
};

int n, s, t;
vector<vector<int>> g, c, f;
vector<int> d, p;

bool bfs() {
  for (int i = 0; i < n; i++) {
    p[i] = 0;
    d[i] = INT_MAX;
  }
  p[s] = 0;
  d[s] = 0;

  queue<int> q;
  q.push(s);
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

  return d[t] != INT_MAX;
}

int dfs(int u, int min_c) {
  if (u == t || min_c == 0) {
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

int dinic() {
  int max_flow = 0;

  while (bfs()) {
    int cur_flow = dfs(s, INT_MAX);

    while (cur_flow != 0) {
      max_flow += cur_flow;
      cur_flow = dfs(s, INT_MAX);
    }
  }

  return max_flow;
}

vector<edge> edges;

int old_n;

bool check(int cur) {
  g.assign(n, vector<int>());
  d.assign(n, 0);
  p.assign(n, 0);
  c.assign(n, vector<int>(n));
  f.assign(n, vector<int>(n));

  for (size_t i = cur; i < edges.size(); i++) {
    g[edges[i].from].push_back(edges[i].to);
    g[edges[i].to].push_back(edges[i].from);
    c[edges[i].from][edges[i].to] += 1;
  }

  return dinic() == old_n;
}

int bin_search() {
  int l = 0;
  int r = ((int)edges.size() - old_n * 2);

  while (r - l > 1) {
    int m = (l + r) / 2;

    if (check(m)) {
      l = m;
    } else {
      r = m;
    }
  }

  return edges[l].val;
}

void input() {
  cin >> n;
  old_n = n;
  s = n * 2;
  t = s + 1;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int val;
      cin >> val;

      edges.emplace_back(i, j + n, val);
    }
  }

  for (int i = 0; i < n; i++) {
    edges.emplace_back(s, i, INT_MAX);
    edges.emplace_back(i + n, t, INT_MAX);
  }

  sort(edges.begin(), edges.end());
  n *= 2;
  n += 2;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  cout << bin_search();

  return 0;
}
