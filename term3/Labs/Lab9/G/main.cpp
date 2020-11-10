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

  int n;
  cin >> n;
  parent.resize(n);
  siz.resize(n);

  for (int i = 0; i < n; i++) {
    parent[i] = i;
    siz[i] = 1;
  }

  vector<pair<int, int>> vec(n);
  vector<edge> edges;
  for (int i = 0; i < n; i++) {
    cin >> vec[i].first >> vec[i].second;
  }

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n ; j++) {
      edges.emplace_back(i, j, (vec[i].first - vec[j].first) * (vec[i].first - vec[j].first)
      + (vec[i].second - vec[j].second) * (vec[i].second - vec[j].second));
    }
  }

  sort(edges.begin(), edges.end(), [](edge const& a, edge const& b) {
    return a.len < b.len;
  });

  double ans = 0;
  for (edge cur : edges) {
    if (find_set(cur.l) != find_set(cur.r)) {
      ans += sqrt(cur.len);
      union_sets(cur.l, cur.r);
    }
  }

  cout << fixed;
  cout.precision(10);
  cout << ans;

  return 0;
}
