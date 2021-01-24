#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g, g_or;
vector<int> used;

void dfs(int v) {
  used[v] = 1;

  for (int to : g_or[v]) {
    if (used[to] != 1) {
      dfs(to);
    }
  }
}

vector<pair<vector<int>, vector<int>>> ans;
vector<int> free_vert, matching;
int timer;
int n, m;

bool dfs_par(int v) {
  if (used[v] == timer) {
    return false;
  }
  used[v] = timer;

  for (int to : g[v]) {
    if (matching[to] == -1 || dfs_par(matching[to])) {
      matching[to] = v;
      return true;
    }
  }
  return false;
}

void find_par() {
  free_vert.clear();

  timer = 1;
  used.assign(m + n, 0);

  for (int i = 0; i < m; i++) {
    dfs_par(i);
    timer++;
  }

  vector<bool> not_free(m);

  for (int i = m; i < m + n; i++) {
    if (matching[i] != -1) {
      not_free[matching[i]] = true;

      for (int to : g[i]) {
        if (to == matching[i]) {
          g_or[i].push_back(to);
        } else {
          g_or[to].push_back(i);
        }
      }
    }
  }
  for (int i = 0; i < m; i++) {
    if (!not_free[i]) {
      free_vert.push_back(i);
    }
  }
}

void solution(int num) {
  cin >> m >> n;

  g.assign(m + n, vector<int>());
  g_or.assign(m + n, vector<int>());
  used.assign(m + n, 0);
  matching.assign(m + n, -1);

  vector<set<int>> g_to(m + n);
  for (int i = 0; i < m; i++) {
    while (true) {
      int to;
      cin >> to;
      if (to == 0) {
        break;
      }

      to = to - 1 + m;

      g_to[i].insert(to);
      g_to[to].insert(i);
    }
  }

  for (int i = 0; i < m; i++) {
    for (int j = m; j < m + n; j++) {
      if (g_to[i].count(j) == 0) {
        g[i].push_back(j);
        g[j].push_back(i);
      }
    }
  }

  find_par();
  used.assign(m + n, 0);

  for (int vertex : free_vert) {
    dfs(vertex);
  }

  for (int i = 0; i < m; i++) {
    if (used[i] != 0) {
      ans[num].first.push_back(i + 1);
    }
  }

  for (int i = m; i < m + n; i++) {
    if (used[i] == 0) {
      ans[num].second.push_back(i - m + 1);
    }
  }
}

void print(int k) {
  for (int i = 0; i < k; i++) {
    cout << ans[i].first.size() + ans[i].second.size()  << '\n';

    cout << ans[i].first.size() << ' ' << ans[i].second.size() << '\n';
    for (int vertex : ans[i].first) {
      cout << vertex << ' ';
    }
    cout << '\n';
    for (int vertex : ans[i].second) {
      cout << vertex << ' ';
    }
    cout << "\n\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int k;
  cin >> k;
  ans.resize(k);

  for (int i = 0; i < k; i++) {
    solution(i);
  }

  print(k);

  return 0;
}
