#include <bits/stdc++.h>

using namespace std;

struct edge {
  int l, r;
  int len;

  edge(int l, int r, int len) : l(l), r(r), len(len) {}
};

vector<bool> used;
vector<int> p;


int cyc;
vector<int> ans;
void dfs_cyc(int v) {
  ans.push_back(v);
  if (v == cyc) {
    return;
  }
  dfs_cyc(p[v]);
}

void dfs(int v) {
  used[v] = true;

  if (used[p[v]]) {
    cyc = v;
    ans.push_back(v);
    dfs_cyc(p[v]);
    return;
  }
  dfs(p[v]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;

  used.resize(n);
  p.resize(n);

  vector<edge> edges;
  vector<long long> d(n, (long long)1e18);

  for (int l = 0; l < n; l++) {
    for (int r = 0; r < n; r++) {
      int len;
      cin >> len;
      if (len == (int)1e9) {
        continue;
      }

      edges.emplace_back(l, r, len);
    }
  }

  d[0] = 0;
  p[0] = 0;

  for (int i = 1; i < n; i++) {
    for (edge cur : edges) {
      if (d[cur.l] != (int)1e18) {
        if (d[cur.l] + cur.len < d[cur.r]) {
          d[cur.r] = d[cur.l] + cur.len;
          p[cur.r] = cur.l;
        }
      }
    }
  }

  int cycle = -1;
  for (edge cur : edges) {
    if (d[cur.l] != (int)1e18) {
      if (d[cur.l] + cur.len < d[cur.r]) {
        d[cur.r] = d[cur.l] + cur.len;
        p[cur.r] = cur.l;

        cycle = cur.r;
      }
    }
  }

  if (cycle == -1) {
    cout << "NO";
    return 0;
  }

  cout << "YES\n";
  dfs(cycle);

  reverse(ans.begin(), ans.end());
  cout << ans.size() << '\n';
  for (int an : ans) {
    cout << an + 1 << ' ';
  }

  return 0;
}
