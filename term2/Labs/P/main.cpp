#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> edges;
vector<int> parent, siz, depth, way, mas, borders;
vector<long long> tree, add, light;
// BUILD HLD
vector<int> used;
void dfs_size(int v, int d) {
  used[v] = 1;
  depth[v] = d;
  siz[v] = 1;

  for (int i = 0; i < (int)edges[v].size(); i++) {
    if (used[edges[v][i]] != 1) {
      parent[edges[v][i]] = v;
      dfs_size(edges[v][i], d + 1);
      siz[v] += siz[edges[v][i]];
    }
  }
}

int cur_way = -1;
void dfs_build(int v) {
  used[v] = 2;
  pair<int, int> mx = {-1, -1};

  for (int i = 0; i < (int)edges[v].size(); i++) {
    if (siz[edges[v][i]] > mx.first && used[edges[v][i]] != 2) {
      mx = {siz[edges[v][i]], edges[v][i]};
    }
  }
  // bruh fix
  if (v == 0) mx = {-1, -1};
  // bruh fix
  if (mx.first >= siz[v] / 2) {
    if (cur_way == -1) {
      cur_way = v;
      way[v] = v;
    }
    way[mx.second] = cur_way;
    borders[v] = (int)mas.size();
    mas.push_back(0);
  } else {
    if (way[v] != -1) {
      borders[v] = (int)mas.size();
      mas.push_back(0);
    }
    cur_way = -1;
  }
  if (mx.second != -1) {
    dfs_build(mx.second);
  }

  for (int i = 0; i < (int)edges[v].size(); i++) {
    if (mx.second != edges[v][i] && used[edges[v][i]] != 2) {
      dfs_build(edges[v][i]);
    }
  }
}
// BUILD HLD

// SEGTREE
void push(int v, int l, int r) {
  tree[v] += add[v];

  if (l != r) {
    add[v * 2] += add[v];
    add[v * 2 + 1] += add[v];
  }
  add[v] = 0;
}

long long seg_ans(int v, int l, int r, int tar) {
  push(v, l, r);
  if (l == r) {
    return tree[v];
  }

  int mid = (l + r) / 2;

  if (tar <= mid) {
    return seg_ans(v * 2, l, mid, tar);
  } else {
    return seg_ans(v * 2 + 1, mid + 1, r, tar);
  }
}

void seg_modify(int v, int l, int r, int dl, int dr, long long x) {
  push(v, l, r);
  if (dr < dl) return;
  if (l == dl && r == dr) {
    add[v] += x;
    return;
  }
  int mid = (l + r) / 2;

  seg_modify(v * 2, l, mid, dl, min(dr, mid), x);
  seg_modify(v * 2 + 1, mid + 1, r, max(dl, mid + 1), dr, x);
}
// SEGTREE

// HLD GO
void way_add(int x, long long pl) {
  if (way[x] == -1) {
    light[x] += pl;
  } else {
    seg_modify(1, 0, (int)mas.size() - 1, borders[way[x]], borders[x], pl);
  }
}

void modify_way(int x, int y, long long pl) {
  if (x == y) {
    if (way[y] == -1) {
      light[y] += pl;
    } else {
      seg_modify(1, 0, (int)mas.size() - 1, borders[x], borders[x], pl);
    }
    return;
  }

  while (x != y) {
    if (way[x] == way[y] && way[x] != -1) {
      int dl = min(borders[x], borders[y]);
      int dr = max(borders[x], borders[y]);

      seg_modify(1, 0, (int)mas.size() - 1, dl, dr, pl);
      return;
    }

    int x_par = (way[x] == -1 ? parent[x] : parent[way[x]]);
    int y_par = (way[y] == -1 ? parent[y] : parent[way[y]]);

    if (depth[x_par] > depth[y_par] || y == y_par) {
      way_add(x, pl);
      x = x_par;
    } else {
      way_add(y, pl);
      y = y_par;
    }

    if (x == y) {
      if (way[y] == -1) {
        light[y] += pl;
      } else {
        seg_modify(1, 0, (int) mas.size() - 1, borders[y], borders[y], pl);
      }
    }
  }
}
// HLD GO
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n;

  used.resize(n);
  light.resize(n);
  edges.resize(n);
  parent.resize(n);
  siz.resize(n);
  depth.resize(n);
  way.resize(n, -1);
  borders.resize(n);

  for (int i = 1; i < n; i++) {
    int x, y;
    cin >> x >> y;
    x--; y--;

    edges[x].push_back(y);
    edges[y].push_back(x);
  }

  dfs_size(0, 0);
  dfs_build(0);

  tree.resize(4 * (int) mas.size());
  add.resize(4 * (int) mas.size());

  cin >> m;
  for (int i = 0; i < m; i++) {
    char type;
    cin >> type;

    if (type == '+') {
      int u, v;
      long long d;
      cin >> u >> v >> d;
      v--; u--;
      modify_way(u, v, d);
    } else {
      int v;
      cin >> v;
      v--;

      if (way[v] == -1) {
        cout << light[v];
      } else {
        cout << seg_ans(1, 0, (int)mas.size() - 1, borders[v]);
      }
      cout << '\n';
    }
  }

  return 0;
}
