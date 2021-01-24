#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<int>> g, g_or, ans;
vector<set<int>> way;
vector<int> pars, used, matching;
int timer = 1;
int cur_vertex_dfs;

void dfs(int v) {
  used[v] = timer;

  for (int to : g_or[v]) {
    if (used[to] != timer) {
      if (to >= n) {
        way[cur_vertex_dfs].insert(to);
      }
      dfs(to);
    }
  }
}

void input() {
  cin >> n;

  g.resize(n * 2);
  g_or.resize(n * 2);
  pars.resize(n * 2);
  used.resize(n * 2);
  matching.resize(n * 2, -1);
  ans.resize(n);
  way.resize(n);

  for (int i = 0; i < n; i++) {
    int num;
    cin >> num;

    for (int j = 0; j < num; j++) {
      int tmp;
      cin >> tmp;
      tmp = tmp - 1 + n;

      g[i].push_back(tmp);
      g[tmp].push_back(i);
    }
  }

  for (int i = 0; i < n; i++) {
    cin >> pars[i];
    pars[i]--;
    matching[i] = pars[i] + n;
    matching[pars[i] + n] = i;
  }

  for (int i = 0; i < n; i++) {
    for (int to : g[i]) {
      if (to == matching[i]) {
        g_or[to].push_back(i);
      } else {
        g_or[i].push_back(to);
      }
    }
  }
}

void solution() {
  for (cur_vertex_dfs = 0; cur_vertex_dfs < n; cur_vertex_dfs++) {
    dfs(cur_vertex_dfs);
    timer++;
  }

  for (int i = 0; i < n; i++) {
    for (int j : g[i]) {
      if (j == matching[i]) {
        ans[i].push_back(j);
        continue;
      }

      int fuckup1 = matching[j];
      int fuckup2 = matching[i];

      if (way[fuckup1].count(fuckup2) != 0) {
        ans[i].push_back(j);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    cout << ans[i].size();

    for (int to : ans[i]) {
      cout << ' ' << to - n + 1;
    }
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  solution();

  return 0;
}
