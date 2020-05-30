#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> edges;
vector<int> parent, siz, depth, way, mas, borders, tree, light;
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
int seg_ans(int v, int l, int r, int dl, int dr) {
  if (dr < dl) return 0;
  if (l == dl && r == dr) return tree[v];

  int mid = (l + r) / 2;

  return max(seg_ans(v * 2, l, mid, dl, min(mid, dr)),
      seg_ans(v * 2 + 1, mid + 1, r, max(mid + 1, dl), dr));
}

void seg_modify(int v, int l, int r, int tar, long long pl) {
  if (l == r) {
    tree[v] += pl;
    return;
  }
  int mid = (l + r) / 2;

  if (tar <= mid) {
    seg_modify(v * 2, l, mid, tar, pl);
  } else {
    seg_modify(v * 2 + 1, mid + 1, r, tar, pl);
  }
  tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
}
// SEGTREE

// HLD GO
int way_ans(int x, int y) {
  int ans = 0;

  if (x == y) {
    if (way[y] == -1) {
      return light[y];
    } else {
      return seg_ans(1, 0, (int)mas.size() - 1, borders[y], borders[y]);
    }
  }

  while (x != y) {
    if (way[x] == way[y] && way[x] != -1) {
      int dl = min(borders[x], borders[y]);
      int dr = max(borders[x], borders[y]);

      return max(ans, seg_ans(1, 0, (int)mas.size() - 1, dl, dr));
    }

    int x_par = (way[x] == -1 ? parent[x] : parent[way[x]]);
    int y_par = (way[y] == -1 ? parent[y] : parent[way[y]]);

    if (depth[x_par] > depth[y_par] || y == y_par) {
      if (way[x] == -1) {
        ans = max(ans, light[x]);
      } else {
        ans = max(ans, seg_ans(1, 0, (int)mas.size() - 1, borders[way[x]], borders[x]));
      }

      x = x_par;
    } else {
      if (way[y] == -1) {
        ans = max(ans, light[y]);
      } else {
        ans = max(ans, seg_ans(1, 0, (int)mas.size() - 1, borders[way[y]], borders[y]));
      }
      y = y_par;
    }

    if (x == y) {
      if (way[y] == -1) {
        ans = max(ans, light[y]);
      } else {
        ans = max(ans, seg_ans(1, 0, (int) mas.size() - 1, borders[y], borders[y]));
      }
    }
  }

  return ans;
}

void way_modify(int v, int x) {
  if (way[v] == -1) {
    light[v] += x;
  } else {
    seg_modify(1, 0, (int)mas.size() - 1, borders[v], x);
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

  cin >> m;
  for (int i = 0; i < m; i++) {
    char type;
    int u, v;
    cin >> type >> u >> v;

    if (type == 'I') {
      u--;
      way_modify(u, v);
    } else {
      u--; v--;
      cout << way_ans(u, v) << '\n';
    }
  }

  return 0;
}
