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

int n, m, k, s, t;
vector<vector<edge_t>> g;
vector<int> d, p, matching;
vector<vector<int>> bruh_g;

bool bfs() {
  for (int i = 0; i < n + m + 2; i++) {
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

int timer = 1;
vector<int> used;

void input() {
  timer++;
  cin >> m >> k;

  s = n + m;
  t = n + m + 1;
  bruh_g.assign(n + m, vector<int>());
  matching.assign(n, -1);
  used.assign(n + m + 2, 0);
  g.assign(n + m + 2, vector<edge_t>());
  d.resize(n + m + 2, 0);
  p.resize(n + m + 2, 0);

  for (int i = 0; i < k; i++) {
    int l, r;
    cin >> l >> r;
    l--; r--;
    r += n;

    bruh_g[l].push_back(r);
    bruh_g[r].push_back(l);
    g[l].emplace_back(r, i, 1, 0, g[r].size());
    g[r].emplace_back(l, -1, 0, 0, g[l].size() - 1);
  }

  for (int i = 0; i < n; i++) {
    g[s].emplace_back(i, -1, 1, 0, g[i].size());
    g[i].emplace_back(s, -1, 0, 0, g[s].size() - 1);
  }

  for (int i = n; i < n + m; i++) {
    g[i].emplace_back(t, -1, 1, 0, g[t].size());
    g[t].emplace_back(i, -1, 0, 0, g[i].size() - 1);
  }
}

void dfs_reachable(int v) {
  used[v] = timer;

  for (int &to : bruh_g[v]) {
    used[to] = timer;
    if (matching[to] != -1 && used[matching[to]] != timer) {
      dfs_reachable(matching[to]);
    }
  }
}

void solution() {
  while (cin >> n) {
    input();
    dinic();

    for (int i = 0; i < n; i++) {
      for (edge_t &to : g[i]) {
        if (to.num != -1 && to.flow == 1) {
          used[to.v] = timer;
          matching[i] = to.v;
        }
      }
    }

    int not_in_matching = -1;

    for (int i = n; i < m + n; i++) {
      if (used[i] != timer) {
        not_in_matching = i;
        break;
      }
    }
    timer++;

    if (not_in_matching == -1) {
      cout << 0;
    } else {
      dfs_reachable(not_in_matching);

      vector<int> ans;
      for (int i = n; i < n + m; i++) {
        if (used[i] == timer) {
          ans.push_back(i + 1);
        }
      }

      cout << ans.size() << '\n';
      for (int &i : ans) {
        cout << i - n << ' ';
      }
    }
    cout << "\n\n";
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solution();
  return 0;
}
