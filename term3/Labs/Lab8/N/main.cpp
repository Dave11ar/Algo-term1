#include <bits/stdc++.h>

using namespace std;

int n;
vector<pair<int, pair<int, int>>> g;
vector<bool> used;
vector<vector<int>> vec, vec_rev;

int sc, mx;
void dfs(int v) {
  used[v] = true;

  for (int to : vec_rev[v]) {
    if (!used[to]) {
      dfs(to);
    }
  }
  sc++;
  mx = v;
}

void dfs_check(int v) {
  used[v] = true;

  for (int to : vec[v]) {
    if (!used[to]) {
      dfs_check(to);
    }
  }
}

bool check(int mid) {
  sc = 0;
  used.assign(n, false);
  for (int i = 0; i < n; i++) {
    vec[i].clear();
    vec_rev[i].clear();
  }

  for (int i = 0; i <= mid; i++) {
    vec[g[i].second.first].push_back(g[i].second.second);
    vec_rev[g[i].second.second].push_back(g[i].second.first);
  }

  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      dfs(i);
    }
  }

  used.assign(n, false);
  dfs_check(mx);

  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      return false;
    }
  }
  return true;
}

int bin_search(int l, int r) {
  while (l != r - 1) {
    int mid = (l + r) / 2;

    if (check(mid)) {
      r = mid;
    } else {
      l = mid;
    }
  }

  return r;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n;
  if (n == 1) {
    cout << 0;
    return 0;
  }

  used.resize(n);
  vec.resize(n);
  vec_rev.resize(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int x;
      cin >> x;
      if (i != j) {
        g.push_back({x, {i, j}});
      }
    }
  }

  sort(g.begin(), g.end());
  cout << g[bin_search(0, n * n - n - 1)].first;

  return 0;
}
