#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> g;
map<pair<int, int>, int> used;
vector<int> ans;

pair<int, int> get_pair(int a, int b) {
  return {min(a, b), max(a, b)};
}

void path(int v) {
  while (!g[v].empty()) {
    if (used[get_pair(v, g[v].back())] != 0) {
      used[get_pair(v, g[v].back())]--;

      path(g[v].back());
    } else {
      g[v].pop_back();
    }
  }

  ans.push_back(v);
}

vector<int> odd;

void add_fake_edges() {
  for (int i = 0; i < n; i++) {
    if (g[i].size() % 2 == 1) {
      odd.push_back(i);
    }
  }

  for (size_t i = 0; i < odd.size(); i++) {
    used[get_pair(odd[i], n)]++;

    g[odd[i]].push_back(n);
    g[n].push_back(odd[i]);
  }
}

vector<int> cur_path;
void print_cur_path() {
  if (cur_path.size() > 1) {
    for (int cur : cur_path) {
      cout << cur + 1 << ' ';
    }
    cout << '\n';
  }

  cur_path.clear();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> m;
  g.resize(n + 1);

  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--; b--;

    used[get_pair(a, b)]++;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  add_fake_edges();
  path(odd.empty() ? 0 : odd[0]);

  cout << (odd.empty() ? 1 : odd.size() / 2) << '\n';

  for (size_t i = 0; i < ans.size(); i++) {
    cur_path.push_back(ans[i]);

    if (ans[(i + 1) % ans.size()] == n) {
      print_cur_path();
      i++;
    }
  }
  print_cur_path();

  return 0;
}
