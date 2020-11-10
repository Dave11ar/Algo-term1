#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<vector<int>> d(n, vector<int>(n, (int)1e9));
  for (int i = 0; i < n; i++) {
    d[i][i] = 0;
  }
  for (int i = 0; i < m; i++) {
    int l, r, x;
    cin >> l >> r >> x;
    l--; r--;

    d[l][r] = x;
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << d[i][j] << ' ';
    }
    cout << '\n';
  }

  return 0;
}
