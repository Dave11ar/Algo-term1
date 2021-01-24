#include <bits/stdc++.h>

using namespace std;

struct edge {
  int v;
  int64_t cap;
  int64_t cost;
  int rev;

  edge() = default;
  edge(edge const&) = default;
  ~edge() = default;
  edge(int v, int64_t cap, int64_t cost, int rev)
      : v(v), cap(cap), cost(cost), rev(rev) {}
};

struct task {
  int64_t l;
  int64_t r;
  int64_t cost;
  int num;

  task(int64_t l, int64_t r, int64_t cost, int num)
    : l(l), r(r), cost(cost), num(num) {}

  bool operator<(task const &other) const {
    return l < other.l;
  }
};

int n, k;
int s, t;
int old_n;

vector<vector<edge>> g;
vector<int64_t> d, pot;
vector<pair<int, int>> parent;
vector<task> tasks;

void input() {
  cin >> n >> k;
  old_n = n;
  s = n * 2;
  t = n * 2 + 1;
  int ps = n * 2 + 2;
  n = n * 2 + 3;

  g.resize(n);
  parent.resize(n);
  pot.resize(n, INT64_MAX);

  g[s].emplace_back(ps, k, 0, g[ps].size());
  g[ps].emplace_back(s, 0, 0, g[s].size() - 1);

  g[ps].emplace_back(t, k, 0, g[t].size());
  g[t].emplace_back(ps, 0, 0, g[ps].size() - 1);

  for (int i = 0; i < old_n; i++) {
    int64_t l, ti, cost;
    cin >> l >> ti >> cost;
    int64_t r = l + ti - 1;
    tasks.emplace_back(l, r, cost, i);

    g[i].emplace_back(i + old_n, 1, -cost, g[i + old_n].size());
    g[i + old_n].emplace_back(i, 0, cost, g[i].size() - 1);

    g[ps].emplace_back(i, k, 0, g[i].size());
    g[i].emplace_back(ps, 0, 0, g[ps].size() - 1);

    g[i + old_n].emplace_back(t, 1, 0, g[t].size());
    g[t].emplace_back(i + old_n, 0, 0, g[i + old_n].size() - 1);
  }

  sort(tasks.begin(), tasks.end());
  for (int i = 0; i < old_n - 1; i++) {
    g[tasks[i].num].emplace_back(tasks[i + 1].num, k, 0, g[tasks[i + 1].num].size());
    g[tasks[i + 1].num].emplace_back(tasks[i].num, 0, 0, g[tasks[i].num].size() - 1);
  }

  for (int i = 0; i < old_n; i++) {
    for (int j = i + 1; j < old_n; j++) {
      if (tasks[i].r < tasks[j].l) {
        g[tasks[i].num + old_n].emplace_back(tasks[j].num, 1, 0, g[tasks[j].num].size());
        g[tasks[j].num].emplace_back(tasks[i].num + old_n, 0, 0,
                                     g[tasks[i].num + old_n].size() - 1);
        break;
      }
    }
  }
}

void ford_bellman() {
  pot[s] = 0;

  for (int i = 0; i < n - 1; i++) {
    // edges
    for (int j = 0; j < n; j++) {
      for (edge &cur : g[j]) {
        if (cur.cap > 0 && pot[j] < INT64_MAX) {
          pot[cur.v] = min(pot[cur.v], pot[j] + cur.cost);
        }
      }
    }
  }
}

bool dijkstra() {
  set<pair<int64_t, int>> q;
  q.emplace(0, s);
  d.assign(n, INT64_MAX);
  d[s] = 0;

  while (!q.empty()) {
    int vrtx = q.begin()->second;
    q.erase(q.begin());

    for (size_t i = 0; i < g[vrtx].size(); i++) {
      edge &cur = g[vrtx][i];

      if (pot[cur.v] < INT64_MAX && cur.cap > 0
        && d[vrtx] + cur.cost + pot[vrtx] - pot[cur.v] < d[cur.v]) {
        q.erase({d[cur.v], cur.v});
        d[cur.v] = d[vrtx] + cur.cost + pot[vrtx] - pot[cur.v];
        parent[cur.v] = {vrtx, i};
        q.emplace(d[cur.v], cur.v);
      }
    }
  }

  return d[t] != INT64_MAX;
}

int64_t min_cost_max_flow() {
  int64_t ans = 0;

  while (dijkstra()) {
    for (int i = 0; i < n; i++) {
      if (d[i] == INT64_MAX) {
        pot[i] = INT64_MAX;
      } else {
        pot[i] += d[i];
      }
    }

    int64_t min_cap = INT64_MAX;

    for (int u = t; u != s; u = parent[u].first) {
      min_cap = min(min_cap, g[parent[u].first][parent[u].second].cap);
    }

    for (int u = t; u != s; u = parent[u].first) {
      g[parent[u].first][parent[u].second].cap -= min_cap;
      g[g[parent[u].first][parent[u].second].v]
      [g[parent[u].first][parent[u].second].rev].cap += min_cap;
      ans += g[parent[u].first][parent[u].second].cost * min_cap;
    }
  }

  return ans;
}

void solution() {
  min_cost_max_flow();

  for (int i = 0; i < old_n; i++) {
    for (edge &cur : g[i]) {
      if (cur.cost < 0) {
        cout << (cur.cap == 0 ? 1 : 0) <<  ' ';
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  ford_bellman();
  solution();

  return 0;
}
