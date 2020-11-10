#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vector<vector<pair<long long, int>>> g(n);
  vector<long long> d(n, (long long)1e18);

  for (int i = 0; i < m; i++) {
    int l, r, x;
    cin >> l >> r >> x;
    l--; r--;

    g[r].push_back({x, l});
    g[l].push_back({x, r});
  }

  set<pair<long long, int>> st;
  d[0] = 0;
  st.insert({0, 0});

  while (!st.empty()) {
    int v = (int)st.begin()->second;
    st.erase(st.begin());

    for (pair<long long, int> to : g[v]) {
      int to_v = to.second;
      long long len = to.first;

      if (d[v] + len < d[to_v]) {
        st.erase({d[to_v], to_v});
        d[to_v] = d[v] + len;
        st.insert({d[to_v], to_v});
      }
    }
  }

  for (int i = 0; i < n; i++) {
    cout << d[i] << ' ';
  }

  return 0;
}
