#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, s, f;
  cin >> n >> s >> f;
  s--; f--;
  vector<vector<pair<long long, int>>> g(n);
  vector<long long> d(n, (long long)1e18);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      long long x;
      cin >> x;
      if (i == j || x == -1) {
        continue;
      }

      g[i].push_back({x, j});
    }
  }

  set<pair<long long, int>> st;
  d[s] = 0;
  st.insert({0, s});

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

  if (d[f] == (long long)1e18) {
    cout << -1;
  } else {
    cout << d[f];
  }

  return 0;
}
