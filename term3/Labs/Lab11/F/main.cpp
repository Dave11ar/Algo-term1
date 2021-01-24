#include <bits/stdc++.h>

using namespace std;

struct edge_t {
  int v;
  int num;
  int cap;
  int flow;

  int low;
  int symmetric;
  edge_t(int v, int num, int cap, int flow, int low, int symmetric) :
      v(v), num(num), cap(cap), flow(flow), low(low), symmetric(symmetric) {}
};

int n, m, s, t;
vector<vector<edge_t>> g;
vector<int> d, p;

bool bfs() {
  for (int i = 0; i < n + 2; i++) {
    p[i] = 0;
    d[i] = INT_MAX;
  }
  d[s] = 0;

  queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (edge_t &to : g[u]) {
      if (to.flow < to.cap && d[to.v] == INT_MAX) {
        d[to.v] = d[u] + 1;
        q.push(to.v);
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
    edge_t &to = g[u][i];

    if (d[to.v] == d[u] + 1) {
      int flow_sz = dfs(to.v, min(min_c, to.cap - to.flow));

      if (flow_sz != 0) {
        to.flow += flow_sz;
        g[to.v][to.symmetric].flow -= flow_sz;
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
    int cur_flow = dfs(s, INT_MAX);

    while (cur_flow != 0) {
      max_flow += cur_flow;
      cur_flow = dfs(s, INT_MAX);
    }
  }

  return max_flow;
}

void input() {
  cin >> n >> m;
  s = n;
  t = n + 1;

  g.resize(n + 2);
  d.resize(n + 2);
  p.resize(n + 2);

  for (int i = 0; i < m; i++) {
    int u, v, l, c;
    cin >> u >> v >> l >> c;
    u--; v--;

    // straight edges
    g[u].emplace_back(v, i, c - l, 0, l, g[v].size());
    g[s].emplace_back(v, -42, l, 0, -1, g[v].size() + 1);
    g[u].emplace_back(t, -1, l, 0, -1, g[t].size());

    // symmetric edges
    g[v].emplace_back(u, -1, 0, 0, -1, g[u].size() - 2);
    g[v].emplace_back(s, -1, 0, 0, -1, g[s].size() - 1);
    g[t].emplace_back(u, -1, 0, 0, -1, g[u].size() - 1);
  }
}

void solution() {
  dinic();

  for (edge_t &to : g[s]) {
    if (to.num == -42 && to.flow != to.cap) {
      cout << "NO";
      return;
    }
  }

  vector<int> ans(m);
  for (int i = 0; i < n; i++) {
    for (edge_t &to : g[i]) {
      if (to.num >= 0) {
        ans[to.num] = to.low + to.flow;
      }
    }
  }

  cout << "YES\n";
  for (int i : ans) {
    cout << i << '\n';
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  solution();

  return 0;
}
