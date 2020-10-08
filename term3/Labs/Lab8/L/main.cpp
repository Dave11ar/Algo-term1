#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<pair<int, int>>> g;
vector<bool> used;
vector<int> tin, cl_tin, color;
set<int> ans;
int sc;
void dfs(int v, int p) {
  used[v] = true;
  cl_tin[v] = sc++;
  tin[v] = cl_tin[v];

  int c = 0;
  for (size_t i = 0; i < g[v].size(); i++) {
    if (g[v][i].first == p) {
      continue;
    }

    if (!used[g[v][i].first]) {
      dfs(g[v][i].first, v);
      cl_tin[v] = min(cl_tin[v], cl_tin[g[v][i].first]);

      if (cl_tin[g[v][i].first] >= tin[v] && p != -1) {
        ans.insert(v);
      }
      c++;
    } else {
      cl_tin[v] = min(cl_tin[v], tin[g[v][i].first]);
    }
  }

  if (p == -1 && c > 1) {
    ans.insert(v);
  }
}

void paint(int v, int c) {
  used[v] = true;

  for (size_t i = 0; i < g[v].size(); i++) {
    if (!used[g[v][i].first]) {
      if (cl_tin[g[v][i].first] >= tin[v]) {
        color[g[v][i].second] = ++sc;
        paint(g[v][i].first, sc);
      } else {
        color[g[v][i].second] = c;
        paint(g[v][i].first, c);
      }
    } else if (tin[g[v][i].first] < tin[v]) {
        color[g[v][i].second] = c;
    }
  }
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> m;
  g.resize(n);
  used.resize(n, false);
  tin.resize(n);
  cl_tin.resize(n);
  color.resize(m);

  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    l--; r--;

    g[l].emplace_back(r, i);
    g[r].emplace_back(l, i);
  }

  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      dfs(i,  -1);
    }
  }


  used.assign(n, false);
  sc = 0;
  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      paint(i, sc);
    }
  }

  cout << sc << '\n';
  for (int i = 0; i < m; i++) {
    cout << color[i] << ' ';
  }

  return 0;
}
