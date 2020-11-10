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

  long long res = INT64_MAX;
  for (size_t i = 0; i < edges.size() ; i++) {
    long long ans = edges[i].len, last = 0;
    for (int j = 0; j < n; j++) {
      parent[j] = j;
      siz[j] = 1;
    }

    for (size_t k = i; k < edges.size(); k++) {
      if (find_set(edges[k].l) != find_set(edges[k].r)) {
        last = edges[k].len;
        union_sets(edges[k].l, edges[k].r);
      }
    }

    if (siz[find_set(0)] == n) {
      res = min(res, last - ans);
    }
  }


  if (res == INT64_MAX) {
    cout << "NO";
    return 0;
  }

  cout << "YES\n" << res;

  return 0;
}
