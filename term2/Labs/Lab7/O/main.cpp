#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<pair<int, int>>> edges;
vector<int> parent, siz, depth, way, mas, borders, tree, par_cost;
// BUILD HLD
void dfs_size(int v, int d) {
  depth[v] = d;
  siz[v] = 1;

  for (int i = 0; i < (int)edges[v].size(); i++) {
    dfs_size(edges[v][i].first, d + 1);
    siz[v] += siz[edges[v][i].first];
  }
}

int cur_way = -1;
void dfs_build(int v) {
  pair<int, int> mx = {-1, -1};
  int go_to = 0;

  for (int i = 0; i < (int)edges[v].size(); i++) {
    if (siz[edges[v][i].first] > mx.first) {
      mx = {siz[edges[v][i].first], edges[v][i].first};
      go_to = i;
    }
  }

  if (mx.first >= siz[v] / 2) {
    if (cur_way == -1) {
      cur_way = v;
      way[v] = v;
    }
    way[mx.second] = cur_way;
    borders[v] = (int)mas.size();
    mas.push_back(INT_MAX);
    mas.push_back(edges[v][go_to].second);
  } else {
    if (way[v] != -1) {
      borders[v] = (int)mas.size();
      mas.push_back(INT_MAX);
    }
    cur_way = -1;
  }
  if (mx.second != -1) {
    dfs_build(mx.second);
  }

  for (int i = 0; i < (int)edges[v].size(); i++) {
    if (mx.second != edges[v][i].first) {
      dfs_build(edges[v][i].first);
    }
  }
}
// BUILD HLD

// SEGTREE
void seg_build(int v, int l, int r) {
  if (l == r) {
    tree[v] = mas[l];
    return;
  }
  int mid = (l + r) / 2;

  seg_build(v * 2, l, mid);
  seg_build(v * 2 + 1, mid + 1, r);
  tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
}

int seg_ans(int v, int l, int r, int dl, int dr) {
  if (dr < dl) return INT_MAX;
  if (l == dl && r == dr) {
    return tree[v];
  }

  int mid = (l + r) / 2;

  return min(seg_ans(v * 2, l, mid, dl, min(mid, dr)),
             seg_ans(v * 2 + 1, mid + 1, r, max(dl, mid + 1), dr));
}
// SEGTREE

// HLD GO
int go(int x, int y) {
  int ans = INT_MAX;

  while (x != y) {
    if (way[x] == way[y] && way[x] != -1) {
      ans = min(ans, seg_ans(1, 0, (int)mas.size() - 1,
          min(borders[x], borders[y]), max(borders[x], borders[y])));
      x = y;
      continue;
    }

    int x_par = ((way[x] == -1 || way[x] == x) ? parent[x] : way[x]);
    int y_par = ((way[y] == -1 || way[y] == y) ? parent[y] : way[y]);

    if (depth[x_par] > depth[y_par] || y == y_par) {
      if (way[x] == -1 || way[x] == x) {
        ans = min(ans, par_cost[x]);
      } else {
        ans = min(ans, seg_ans(1, 0, (int)mas.size() - 1, borders[x_par], borders[x]));
      }
      x = x_par;
    } else {
      if (way[y] == -1 || way[y] == y) {
        ans = min(ans, par_cost[y]);
      } else {
        ans = min(ans, seg_ans(1, 0, (int)mas.size() - 1, borders[y_par], borders[y]));
      }
      y = y_par;
    }
  }

  return ans;
}

// HLD GO
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n;

  edges.resize(n);
  parent.resize(n);
  siz.resize(n);
  depth.resize(n);
  way.resize(n, -1);
  borders.resize(n);
  par_cost.resize(n, INT_MAX);

  for (int i = 1; i < n; i++) {
    int x, y;
    cin >> x >> y;
    x--;
    parent[i] = x;
    par_cost[i] = y;
    edges[x].push_back({i, y});
  }

  dfs_size(0, 0);
  dfs_build(0);
  if (!mas.empty()) {
    tree.resize(4 * (int) mas.size(), INT_MAX);
    seg_build(1, 0, (int) mas.size() - 1);
  }
  cin >> m;
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    x--; y--;

    cout << go(x, y) << '\n';
  }

  return 0;
}
