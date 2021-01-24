#include <bits/stdc++.h>

using namespace std;

struct edge_t {
  int v;
  int num;
  int cap;
  int flow;

  int symmetric;
  edge_t(int v, int num, int cap, int flow, int symmetric) :
      v(v), num(num), cap(cap), flow(flow), symmetric(symmetric) {}
};

int n, m;
vector<vector<edge_t>> g;
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

    for (edge_t &to : g[u]) {
      if (to.flow < to.cap && d[to.v] == INT_MAX) {
        d[to.v] = d[u] + 1;
        q.push(to.v);
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
    int cur_flow = dfs(0, INT_MAX);

    while (cur_flow != 0) {
      max_flow += cur_flow;
      cur_flow = dfs(0, INT_MAX);
    }
  }

  return max_flow;
}

int timer = 1;
vector<int> used, traffic;
vector<vector<int>> path;

int get_path(int u, int min_c) {
  if (min_c == 0) {
    return 0;
  }

  if (u == n - 1) {
    return min_c;
  }

  used[u] = timer;
  for (edge_t &to : g[u]) {
    if (to.flow <= 0) {
      continue;
    }

    if (used[to.v] != timer && to.flow > 0) {
      int flow = get_path(to.v, min(min_c, to.flow));
      if (flow > 0) {
        to.flow -= flow;
        path[timer - 1].push_back(to.num);
        return flow;
      }
    }
  }
  used[u] = 0;
  return 0;
}

void decomposition() {
  dinic();

  while (true) {
    path.emplace_back();
    int flow = get_path(0, INT_MAX);
    traffic.push_back(flow);

    if (flow == 0) {
      break;
    }
    timer++;
  }
  path.pop_back();
  traffic.pop_back();

  cout << path.size() << '\n';
  for (size_t i = 0; i < path.size(); i++) {
    reverse(path[i].begin(), path[i].end());
    cout << traffic[i] << ' ' <<path[i].size();
    for (int j : path[i]) {
      cout << ' ' << j;
    }
    cout << '\n';
  }
}

void input() {
  cin >> n >> m;

  used.resize(n);
  g.resize(n);
  d.resize(n);
  p.resize(n);

  for (int i = 0; i < m; i++) {
    int l, r, cl;
    cin >> l >> r >> cl;
    l--; r--;

    g[l].emplace_back(r, i + 1, cl, 0, g[r].size());
    g[r].emplace_back(l, -1, 0, 0, g[l].size() - 1);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  decomposition();

  return 0;
}
