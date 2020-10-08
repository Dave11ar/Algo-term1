#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> parent, siz;

int neg(int x) {
  return n + x;
}
int find_set(int v) {
  if (v == parent[v]) {
    return v;
  }

  return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
  a = find_set(a);
  b = find_set(b);

  if (a == b) {
    return;
  }

  if (siz[a] < siz[b]) {
    swap(a, b);
  }
  parent[b] = a;
}

void init_sets() {
  parent.resize(n * 2);
  siz.resize(n * 2);
  for (int i = 0; i < n * 2; i++) {
    parent[i] = i;
    siz[i] = 1;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> m;
  init_sets();
  int ans = -1;
  for (int i = 0; i < m; i++) {
    int x, y;
    char expr;

    cin >> x >> y >> expr;
    x--; y--;

    if (ans == -1) {
      if (expr == 'L') {
        union_sets(neg(x), y);
        union_sets(x, neg(y));
      } else {
        union_sets(x, y);
        union_sets(neg(x), neg(y));
      }

      for (int j = 0; j < n; j++) {
        if (find_set(j) == find_set(neg(j))) {
          ans = i;
          break;
        }
      }
    }
  }

  cout << (ans == -1 ? m : ans);
  return 0;
}
