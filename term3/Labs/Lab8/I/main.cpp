#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> g;
vector<bool> used;
vector<int> tin, cl_tin;
set<int> ans;
int sc;

void dfs(int v, int p) {
  used[v] = true;
  cl_tin[v] = sc++;
  tin[v] = cl_tin[v];

  int c = 0;
  for (size_t i = 0; i < g[v].size(); i++) {
    if (g[v][i] == p) {
      continue;
    }

    if (!used[g[v][i]]) {
      dfs(g[v][i], v);
      cl_tin[v] = min(cl_tin[v], cl_tin[g[v][i]]);

      if (cl_tin[g[v][i]] >= tin[v] && p != -1) {
        ans.insert(v + 1);
      }
      c++;
    } else {
      cl_tin[v] = min(cl_tin[v], tin[g[v][i]]);
    }
  }

  if (p == -1 && c > 1) {
    ans.insert(v + 1);
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

    g[l].push_back(r);
    g[r].push_back(l);
  }

  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      dfs(i,  -1);
    }
  }

  cout << ans.size() << '\n';
  for (int i : ans) {
    cout << i << ' ';
  }

  return 0;
}
