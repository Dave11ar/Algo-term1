#include <bits/stdc++.h>

using namespace std;

int n, m;
struct three {
  int x;
  int y;
  int z;
};

vector<three> vec;
vector<bool> used;
vector<int> top_sort, comp;
vector<vector<int>> g, rev_g;

int cord(int x) {
  return n + x;
}

void input() {
  cin >> n >> m;
  vec.resize(m);
  g.resize(2 * n + 1);
  rev_g.resize(2 * n + 1);
  used.resize(2 * n + 1);
  comp.resize(2 * n + 1);

  for (int i = 0; i < m; i++) {
    cin >> vec[i].x >> vec[i].y >> vec[i].z;
  }
}

void make_g() {
  for (three cur : vec) {
    // cur.x - false
    g[cord(-cur.x)].push_back(cord(cur.y));
    g[cord(-cur.x)].push_back(cord(cur.z));

    rev_g[cord(cur.y)].push_back(cord(-cur.x));
    rev_g[cord(cur.z)].push_back(cord(-cur.x));
    // cur.y - false
    g[cord(-cur.y)].push_back(cord(cur.x));
    g[cord(-cur.y)].push_back(cord(cur.z));

    rev_g[cord(cur.x)].push_back(cord(-cur.y));
    rev_g[cord(cur.z)].push_back(cord(-cur.y));
    // cur.z - false
    g[cord(-cur.z)].push_back(cord(cur.x));
    g[cord(-cur.z)].push_back(cord(cur.y));

    rev_g[cord(cur.x)].push_back(cord(-cur.z));
    rev_g[cord(cur.y)].push_back(cord(-cur.z));
  }
}

void dfs(int v) {
  used[v] = true;

  for (int to : g[v]) {
    if (!used[to]) {
      dfs(to);
    }
  }
  top_sort.push_back(v);
}

int sc = 0;
void dfs_rev(int v) {
  used[v] = true;
  comp[v] = sc;
  for (int to : rev_g[v]) {
    if (!used[to]) {
      dfs_rev(to);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  make_g();

  for (size_t i = 0; i < g.size(); i++) {
    if (!used[i]) {
      dfs(i);
    }
  }

  used.assign(2 * n + 1, false);
  reverse(top_sort.begin(), top_sort.end());
  for (int v : top_sort) {
    if (!used[v]) {
      dfs_rev(v);
      sc++;
    }
  }

  for (int i = 0; i < n; i++) {
    if (comp[i] == comp[i + 2 * (n - i)]) {
      cout << "NO";
      return 0;
    }
  }

  cout << "YES\n";
  for (int i = n - 1; i >= 0; i--) {
    cout << (comp[i] > comp[i + 2 * (n - i)] ? i - n : -(i - n)) << ' ';
  }

  return 0;
}
