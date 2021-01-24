#include <bits/stdc++.h>

using namespace std;

typedef int64_t ll;

struct edge {
  ll v;
  ll cap;
  ll cost;

  ll rev;

  edge() = default;

  edge(ll v, ll cap, ll cost, ll rev)
    : v(v), cap(cap), cost(cost), rev(rev) {}
};

int n, m, s, t;
vector<vector<edge>> g;
vector<ll> pot, d;
vector<pair<ll, edge*>> parent;

void input() {
  cin >> n >> m;
  s = 0;
  t = n - 1;

  g.resize(n);
  pot.resize(n, INT64_MAX);
  parent.resize(n);

  for (int i = 0; i < m; i++) {
    ll v, u, cap, cost;
    cin >> v >> u >> cap >> cost;
    v--; u--;

    g[(size_t)v].emplace_back(u, cap, cost, g[(size_t)u].size());
    g[(size_t)u].emplace_back(v, 0, -cost, g[(size_t)v].size() - 1);
  }
}

void ford_bellman() {
  pot[s] = 0;

  for (int i = 0; i < n - 1; i++) {
    // edges
    for (int j = 0; j < n; j++) {
      for (edge &cur : g[j]) {
        if (cur.cap > 0 && pot[j] < INT64_MAX) {
          pot[(size_t)cur.v] = min(pot[(size_t)cur.v], pot[j] + cur.cost);
        }
      }
    }
  }
}

bool dijkstra() {
  set<pair<ll, ll>> q;
  q.insert({0, s});
  d.assign(n, INT64_MAX);
  d[s] = 0;

  while (!q.empty()) {
    ll vrtx = q.begin()->second;
    q.erase(q.begin());

    for (edge &cur : g[(size_t)vrtx]) {
      if (pot[(size_t)cur.v] < INT64_MAX && cur.cap > 0 &&
        d[(size_t)vrtx] + cur.cost + pot[(size_t)vrtx] - pot[(size_t)cur.v] < d[(size_t)cur.v]) {
        q.erase({d[(size_t)cur.v], cur.v});
        d[(size_t)cur.v] = d[(size_t)vrtx] + cur.cost + pot[(size_t)vrtx] - pot[(size_t)cur.v];
        parent[(size_t)cur.v] = {vrtx, &cur};
        q.insert({d[(size_t)cur.v], cur.v});
      }
    }
  }

  return d[t] != INT64_MAX;
}

void min_cost_max_flow() {
  ll ans = 0;

  while (dijkstra()) {
    ll min_cap = INT64_MAX;

    for (ll u = t; u != s; u = parent[(size_t)u].first) {
      min_cap = min(min_cap, parent[(size_t)u].second->cap);
    }

    for (ll u = t; u != s; u = parent[(size_t)u].first) {
      edge *cur = parent[(size_t)u].second;

      cur->cap -= min_cap;
      g[(size_t)cur->v][(size_t)cur->rev].cap += min_cap;
      ans += cur->cost * min_cap;
    }
  }

  cout << ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  ford_bellman();
  min_cost_max_flow();

  return 0;
}
