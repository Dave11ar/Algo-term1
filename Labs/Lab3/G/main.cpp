#include<bits/stdc++.h>

using namespace std;

vector<int> p;

int find_dsu(int a) {
  if (a == p[a]) {
    return a;
  }
  return p[a] = find_dsu(p[a]);
}

void unite_dsu(int a, int b) {
  a = find_dsu(a);
  b = find_dsu(b);

  p[a] = b;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m;
  cin >> n >> m;
  vector<pair<int, pair<int, int>>> req(m);

  for (int i = 0; i < m; i++) {
    int l, r, q;
    cin >> l >> r >> q;

    req[i] = { q , { l - 1 , r - 1 } };
  }

  sort(req.begin(), req.end());
  reverse(req.begin(), req.end());

  p.resize(n + 1);
  for (int i = 0; i <= n; i++) {
    p[i] = i;
  }

  vector<int> ans(n + 1);
  for (int i = 0; i < m; i++) {
    int l = req[i].second.first;
    int r = req[i].second.second;

    while (l <= r) {
      l = find_dsu(l);
      if (l > r) {
        break;
      }

      ans[l] = req[i].first;
      unite_dsu(l, l + 1);
    }
  }

  for (int i = 0; i < n; i++) {
    cout << ans[i] << ' ';
  }

  return 0;
}
