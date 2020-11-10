#include <bits/stdc++.h>

using namespace std;

struct edge {
  int l, r;
  long long len;

  edge(int l, int r, long long len) : l(l), r(r), len(len) {}
};

vector<int> p, used;
vector<vector<int>> g;

void dfs(int v) {
  used[v] = true;

  for (int to : g[v]) {
    if (!used[to]) {
      dfs(to);
    }
  }
}

const long long MX = (long long)1e18 * 9;
const long long MIN_MX = -MX / 2;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m, s;
  cin >> n >> m >> s;
  s--;

  used.resize(n);
  p.resize(n);
  g.resize(n);

  vector<edge> edges;
  vector<long long> d(n, MX);

  for (int i = 0; i < m; i++) {
    int l, r;
    long long x;
    cin >> l >> r >> x;
    l--; r--;

    g[l].push_back(r);
    edges.emplace_back(l, r, x);
  }
  d[s] = 0;
  p[s] = 0;

  for (int i = 1; i < n; i++) {
    for (edge cur : edges) {
      if (d[cur.l] != MX) {
        if (d[cur.l] + cur.len < d[cur.r]) {
          d[cur.r] = max(MIN_MX, d[cur.l] + cur.len);
          p[cur.r] = cur.l;
        }
      }
    }
  }

  vector<int> bruh_vert;

  for (edge cur : edges) {
    if (d[cur.l] != MX) {
      if (d[cur.l] + cur.len < d[cur.r]) {
        d[cur.r] = max(MIN_MX, d[cur.l] + cur.len);
        p[cur.r] = cur.l;

        bruh_vert.push_back(cur.r);
      }
    }
  }

  for (int bruh : bruh_vert) {
    dfs(bruh);
  }

  for (int i = 0; i < n; i++) {
    if (used[i]) {
      cout << '-';
    } else if (d[i] == MX) {
      cout << '*';
    } else {
      cout << d[i];
    }

    cout << '\n';
  }

  return 0;
}
