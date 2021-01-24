#include <bits/stdc++.h>

using namespace std;

struct edge {
  int v;
  int cap;
  int old_cap;
  int num;

  edge(int v, int cap, int old_cap, int num)
    : v(v), cap(cap), old_cap(old_cap), num(num) {}
};

struct edge_rev {
  int v;
  int rev;

  edge_rev(int v, int rev)
    : v(v), rev(rev) {}
};

int n, m, L;
int s, t;
int timer = 1;
vector<int> layer, in, from, used, prt;
vector<vector<edge>> g_s;
vector<vector<edge_rev>> g_r;

void input() {
  cin >> n >> m >> L;

  g_s.resize(n);
  g_r.resize(n);
  layer.resize(n);
  in.resize(n);
  from.resize(n);
  used.resize(n);
  prt.resize(n);

  for (int i = 0; i < n; i++) {
    cin >> layer[i];
    if (layer[i] == 1) {
      s = i;
    } else if (layer[i] == L) {
      t = i;
    }
  }

  for (int i = 0; i < m; i++) {
    int v, u, cap;
    cin >> v >> u >> cap;
    v--; u--;

    g_s[v].emplace_back(u, cap, cap, i);
    g_r[u].emplace_back(v, g_s[v].size() - 1);

    in[u] += cap;
    from[v] += cap;
  }
}

bool dfs(int v) {
  used[v] = timer;

  if (v == t) {
    return true;
  }

  for (edge &cur : g_s[v]) {
    if (used[cur.v] != timer && cur.cap > 0) {
      if (dfs(cur.v)) {
        return true;
      }
    }
  }

  return false;
}

int get_min() {
  pair<int, int> mn = {INT_MAX, INT_MAX};
  for (int i = 0; i < n; i++) {
    int cur = min(in[i], from[i]);

    if (i == s) {
      cur = from[i];
    } else if (i == t) {
      cur = in[i];
    }

    if (cur != 0 && cur < mn.first) {
      mn = {cur, i};
    }
  }

  return mn.second;
}

queue<int> q;

void flow_t(int u) {
  q.push(u);

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (edge &edg : g_s[v]) {
      if (edg.cap == 0) {
        continue;
      } else if (used[edg.v] != timer) {
        used[edg.v] = timer;
        q.push(edg.v);
      }

      int fl = min(edg.cap, prt[v]);

      edg.cap -= fl;
      from[v] -= fl;
      in[edg.v] -= fl;
      prt[v] -= fl;
      prt[edg.v] += fl;
    }
  }
}

void flow_s(int u) {
  q.push(u);

  int fl;
  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (edge_rev &edg_r : g_r[v]) {
      edge &edg = g_s[edg_r.v][edg_r.rev];
      if (edg.cap == 0) {
        continue;
      } else if (used[edg_r.v] != timer) {
        used[edg_r.v] = timer;
        q.push(edg_r.v);
      }

      fl = min(edg.cap, prt[v]);

      edg.cap -= fl;
      from[edg_r.v] -= fl;
      in[v] -= fl;
      prt[v] -= fl;
      prt[edg_r.v] += fl;
    }
  }
}

void kill() {
  for (int i = 0; i < n; i++) {
    if (i == s || i == t) {
      continue;
    }

    if (min(in[i], from[i]) == 0) {
      for (edge &edg : g_s[i]) {
        edg.old_cap -= edg.cap;
        in[edg.v] -= edg.cap;
        edg.cap = 0;
      }

      for (edge_rev &edg_r : g_r[i]) {
        edge &edg = g_s[edg_r.v][edg_r.rev];

        edg.old_cap -= edg.cap;
        from[edg_r.v] -= edg.cap;
        edg.cap = 0;
      }
    }
  }
}

void kumar_lounge_algo() {
  int min_pot;
  int prt_cur;

  while (dfs(s)) {
    for (int & i : prt) {
      i = 0;
    }

    min_pot = get_min();
    prt_cur = min(in[min_pot], from[min_pot]);

    if (min_pot == s) {
      prt_cur = from[s];
    } else if (min_pot == t) {
      prt_cur = in[t];
    }

    prt[min_pot] = prt_cur;
    timer++;
    flow_t(min_pot);
    timer++;
    prt[min_pot] = prt_cur;
    flow_s(min_pot);

    kill();
    timer++;
  }

  vector<int> ans(m);
  for (int i = 0; i < n; i++) {
    for (edge &cur : g_s[i]) {
      ans[cur.num] = cur.old_cap - cur.cap;
    }
  }

  for (int i = 0; i < m; i++) {
    cout << ans[i] << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  kumar_lounge_algo();

  return 0;
}
