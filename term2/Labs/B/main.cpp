#include <bits/stdc++.h>

using namespace std;

int MOD = 16714589;

int n, m;
vector<int> a;
int u, v;
vector<vector<int>> sparse;

void build_sparse() {
  for (int i = n - 1; i >= 0; i--) {
    sparse[i][0] = a[i];
    for (int j = 1; i + (1 << j) <= n; j++) {
      sparse[i][j] = min(sparse[i][j - 1], sparse[i + (1 << (j - 1))][j - 1]);
      }
    }
}

int fl_log(int t) {
  if (t == 1) return 0;
  return fl_log(t / 2) + 1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> m;
  a.resize(n);
  sparse.resize(n, vector<int>(fl_log(n) + 1));
  cin >> a[0];
  for (int i = 1; i < n; i++) {
    a[i] = (23 * a[i - 1] + 21563) % MOD;
  }

  cin >> u >> v;

  build_sparse();
  int ans = 0;

  for (int i = 1; i <= m; i++) {
    int l = min(u - 1, v - 1);
    int r = max(u - 1, v - 1);

    int fl = fl_log(r - l + 1);
    ans = min(sparse[l][fl], sparse[r - (1 << fl) + 1][fl]);

    if (i == m) break;
    u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
    v = ((13 * v + 593 + ans + 5 * i) % n) + 1;
  }

  cout << u << ' ' << v << ' ' << ans;

  return 0;
}