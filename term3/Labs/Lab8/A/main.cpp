#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> vec;
vector<int> used, ans;

void dfs(int v) {
  used[v] = 1;

  for (size_t i = 0; i < vec[v].size(); i++) {
    if (used[vec[v][i]] == 1) {
      cout << -1;
      exit(0);
    } else if (used[vec[v][i]] == 0) {
      dfs(vec[v][i]);
    }
  }
  ans.push_back(v);
  used[v] = 2;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vec.resize(n);
  used.resize(n);

  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    l--; r--;

    vec[l].push_back(r);
  }

  for (int i = 0; i < n; i++) {
    if (used[i] != 2) {
      dfs(i);
    }
  }

  reverse(ans.begin(), ans.end());

  for (int i = 0; i < n; i++) {
    cout << ans[i] + 1 << ' ';
  }

  return 0;
}
