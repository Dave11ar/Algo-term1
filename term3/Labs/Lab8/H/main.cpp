#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<pair<int, int>>> g;
vector<bool> used;
vector<int> tin, cl_tin, ans;

int sc;

void dfs(int v, int p) {
  used[v] = true;
  cl_tin[v] = sc++;
  tin[v] = cl_tin[v];

  for (size_t i = 0; i < g[v].size(); i++) {
    if (g[v][i].first == p) {
      continue;
    }

    if (!used[g[v][i].first]) {
      dfs(g[v][i].first, v);

      if (cl_tin[g[v][i].first] > tin[v]) {
        ans.push_back(g[v][i].second);
      } else {
        cl_tin[v] = min(cl_tin[v], cl_tin[g[v][i].first]);
      }
    } else {
      cl_tin[v] = min(cl_tin[v], tin[g[v][i].first]);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> m;
  g.resize(n);
  used.resize(n);
  tin.resize(n);
  cl_tin.resize(n);

  for (int i = 1; i <= m; i++) {
    int l, r;
    cin >> l >> r;
    l--; r--;

    g[l].emplace_back(r, i);
    g[r].emplace_back(l, i);
  }

  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      dfs(i, i);
    }
  }

  sort(ans.begin(), ans.end());
  cout << ans.size() << '\n';
  for (size_t i = 0; i < ans.size(); i++) {
    cout << ans[i] << ' ';
  }

  return 0;
}
