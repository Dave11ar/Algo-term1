#include <bits/stdc++.h>

using namespace std;

struct edge {
  int v;
  int cap;
  int old_cap;
  int cost;
  int rev;
  bool straight;
  int bruh;

  edge() = default;
  edge(edge const&) = default;
  ~edge() = default;

  edge(int v, int cap, int cost, int rev, bool straight)
    : v(v), cap(cap), old_cap(cap), cost(cost), rev(rev), straight(straight), bruh(0) {}
};

int n, k;
int s, t;
int old_n;

vector<vector<edge>> g;
vector<int> d;
vector<pair<int, edge*>> parent;

void input() {
  cin >> n >> k;
  old_n = n;
  s = n * 2;
  t = n * 2 + 1;
  n = n * 2 + 2;

  g.resize(n);
  parent.resize(n);

  for (int i = 0; i < old_n; i++) {
    for (int j = old_n; j < old_n * 2; j++) {
      int w;
      cin >> w;

      g[i].emplace_back(j, 1, w, g[j].size(), true);
      g[j].emplace_back(i, 0, -w, g[i].size() - 1, false);
    }

    g[s].emplace_back(i, k, 0, g[i].size(), true);
    g[i].emplace_back(s, 0, 0, g[s].size() - 1, false);

    g[i + old_n].emplace_back(t, k, 0, g[t].size(), true);
    g[t].emplace_back(i + old_n, 0, 0, g[i + old_n].size() - 1, false);
  }
}

bool dijkstra() {
  set<pair<int, int>> q;
  q.insert({0, s});
  d.assign(n, INT_MAX);
  d[s] = 0;

  while (!q.empty()) {
    int vrtx = q.begin()->second;
    q.erase(q.begin());

    for (edge &cur : g[vrtx]) {
      if (cur.cap > 0 && d[vrtx] + cur.cost < d[cur.v]) {
        q.erase({d[cur.v], cur.v});
        d[cur.v] = d[vrtx] + cur.cost;
        parent[cur.v] = {vrtx, &cur};
        q.insert({d[cur.v], cur.v});
      }
    }
  }

  return d[t] != INT_MAX;
}

int min_cost_max_flow() {
  int ans = 0;

  while (dijkstra()) {
    int min_cap = INT_MAX;

    for (int u = t; u != s; u = parent[u].first) {
      min_cap = min(min_cap, parent[u].second->cap);
    }

    for (int u = t; u != s; u = parent[u].first) {
      edge *cur = parent[u].second;

      cur->cap -= min_cap;
      cur->bruh -= min_cap;
      g[cur->v][cur->rev].cap += min_cap;
      g[cur->v][cur->rev].bruh += min_cap;
      ans += cur->cost * min_cap;
    }
  }

  return ans;
}

vector<vector<edge>> tmp;

void decrease() {
  for (edge &cur : g[s]) {
    cur.cap = 1;
    cur.old_cap = 1;
  }

  for (edge &cur : g[t]) {
    g[cur.v][cur.rev].cap = 1;
    g[cur.v][cur.rev].old_cap = 1;
  }
}

void prepare() {
  for (int i = 0; i < n; i++) {
    for (edge &cur : g[i]) {
      cur.bruh = 0;
      cur.cap = cur.old_cap;
    }
  }
}

void matching(int sc) {
  vector<int> ans(old_n);

  for (int i = 0; i < old_n; i++) {
    for (edge &cur : g[i]) {
      if (cur.straight) {
        if (cur.bruh == sc) {
          cur.old_cap = 0;
          ans[i] = cur.v - old_n + 1;
        }
      }
    }
  }

  for (int &i : ans) {
    cout << i << ' ';
  }
  cout << '\n';
}

void solution() {
  tmp.resize(n);

  cout << min_cost_max_flow() << '\n';

  for (int i = 0; i < n; i++) {
    for (edge &cur : g[i]) {
      if (cur.straight) {
        if (cur.cap == 0 || i == s || i == t) {
          tmp[i].push_back(cur);
          tmp[cur.v].push_back(g[cur.v][cur.rev]);

          tmp[i][(int)tmp[i].size() - 1].rev = (int)tmp[cur.v].size() - 1;
          tmp[cur.v][(int)tmp[cur.v].size() - 1].rev = (int)tmp[i].size() - 1;
        }
      }
    }
  }

  g.assign(n, vector<edge>());
  for (int i = 0; i < n; i++) {
    for (edge &cur : tmp[i]) {
      g[i].push_back(cur);
    }
  }

  decrease();
  for (int z = 0; z < k; z++) {
    prepare();
    min_cost_max_flow();
    matching(-1);
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
