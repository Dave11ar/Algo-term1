#include <bits/stdc++.h>

using namespace std;

vector<set<int>> g;

vector<int> ans;

void path(int v = 0) {
  while (!g[v].empty()) {
    int to = *g[v].begin();
    g[v].erase(to);
    path(to);
  }

  ans.push_back(v);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int d, k;
  cin >> d >> k;

  if (k == 1) {
    for (int i = 0; i < d; i++) {
      cout << i;
    }
    return 0;
  }

  int k_mod = (int) pow(d, k - 1);
  g.resize(k_mod);

  for (int i = 0; i < k_mod * d; i++) {
    for (int j = 0; j < d; j++) {
      int from = i / d;
      int to = i % k_mod;

      g[from].insert(to);
    }
  }

  path();
  reverse(ans.begin(), ans.end());

  for (int i = 0; i < k - 1; i++) {
    cout << 0;
  }

  for (size_t i = 1; i < ans.size(); i++) {
    cout << ans[i] % d;
  }

  return 0;
}
