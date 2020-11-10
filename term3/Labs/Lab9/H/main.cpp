#include <bits/stdc++.h>

using namespace std;

vector<int> parent, siz;
int find_set(int v) {
  if (v == parent[v]) {
    return v;
  }
  return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
  a = find_set(a);
  b = find_set(b);

  if (siz[a] < siz[b]) {
    swap(a, b);
  }
  parent[b] = a;
  siz[a] += siz[b];
}

struct edge {
  int l, r;
  int len;

  edge(int l, int r, int len) : l(l), r(r), len(len) {}
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  parent.resize(n);
  siz.resize(n);

  for (int i = 0; i < n; i++) {
    parent[i] = i;
    siz[i] = 1;
  }

  vector<pair<int, int>> vec(n);
  vector<edge> edges;
  for (int i = 0; i < m; i++) {
    int l, r, x;
    cin >> l >> r >> x;
    l--; r--;

    edges.emplace_back(l, r, x);
  }


  sort(edges.begin(), edges.end(), [](edge const& a, edge const& b) {
    return a.len < b.len;
  });

  long long ans = 0;
  for (edge cur : edges) {
    if (find_set(cur.l) != find_set(cur.r)) {
      ans += cur.len;
      union_sets(cur.l, cur.r);
    }
  }

  cout << ans;

  return 0;
}
