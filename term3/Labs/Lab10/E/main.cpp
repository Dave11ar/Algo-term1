#include <bits/stdc++.h>

using namespace std;

// number of diag of every type --- m + n - 1
// type 1 --- влево и вниз
// type 2 -- вправо вниз
struct bruh {
  int i, j;
  char color;

  bruh(int i, int j, char color) :
    i(i), j(j), color(color) {}
};

int n, m;
vector<vector<pair<int, bruh>>> g[2], g_or[2];
vector<vector<bool>> board;
vector<int> used, matching, ans[2];

int get_diag(int i, int j, bool type) {
  // !type -- влево вниз
  // type -- вправо вниз
  while (true) {
    if (i == 0) {
      break;
    }

    if (type) {
      if (j == 0) {
        break;
      }
      i--;
      j--;
    } else {
      if (j == m - 1) {
        break;
      }
      i--;
      j++;
    }
  }

  int num;
  if (type) {
    if (i != 0) {
      num = n - 1 - i;
    } else {
      num = n - 1 + j;
    }
    num += m + n - 1;
  } else {
    if (i != 0) {
      num = n - 1 - i;
    } else {
      num = n - 1 + m - 1 - j;
    }
  }

  return num;
}

void input() {
  cin >> n >> m;

  g[0].resize(2 * (m + n - 1));
  g[1].resize(2 * (m + n - 1));
  g_or[0].resize(2 * (m + n - 1));
  g_or[1].resize(2 * (m + n - 1));
  ans[0].clear();
  ans[1].clear();
  used.resize(2 * (m + n - 1));
  matching.resize(2 * (m + n - 1));
  board.resize(n, vector<bool>(m));

  bool even = false;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char tmp;
      cin >> tmp;
      board[i][j] = tmp == 'W';

      int type1 = get_diag(i, j, false);
      int type2 = get_diag(i, j, true);

      if (even != board[i][j]) {
        g[1][type1].push_back({type2, {i + 1, j + 1, tmp == 'W' ? 'B' : 'W'}});
        g[1][type2].push_back({type1, {i + 1, j + 1, tmp == 'W' ? 'B' : 'W'}});
      } else {
        g[0][type1].push_back({type2, {i + 1, j + 1, tmp == 'W' ? 'B' : 'W'}});
        g[0][type2].push_back({type1, {i + 1, j + 1, tmp == 'W' ? 'B' : 'W'}});
      }

      if (j != m - 1) {
        even = !even;
      }
    }
    if (m % 2 != 0) {
      even = !even;
    }
  }
}

// парсоч + покрытие
void dfs(int v, int cur_g) {
  used[v] = 1;

  for (size_t i = 0; i < g_or[cur_g][v].size(); i++) {
    int to = g_or[cur_g][v][i].first;
    if (used[to] != 1) {
      dfs(to, cur_g);
    }
  }
}

vector<int> free_vert;
int timer;

bool dfs_par(int v, int cur_g) {
  if (used[v] == timer) {
    return false;
  }
  used[v] = timer;

  for (size_t i = 0; i < g[cur_g][v].size(); i++) {
    int to = g[cur_g][v][i].first;
    if (matching[to] == -1 || dfs_par(matching[to], cur_g)) {
      matching[to] = v;
      return true;
    }
  }
  return false;
}

void find_par() {
  for (int varia = 0; varia < 2; varia++) {
    free_vert.clear();

    timer = 1;
    used.assign(2 * (m + n - 1), 0);
    matching.assign(2 * (m + n - 1), -1);

    for (int i = 0; i < m + n - 1; i++) {
      dfs_par(i, varia);
      timer++;
    }

    vector<bool> not_free(m + n - 1);

    for (int i = m + n - 1; i < 2 * (m + n - 1); i++) {
      if (matching[i] != -1) {
        not_free[matching[i]] = true;

        for (size_t j = 0; j < g[varia][i].size(); j++) {
          int to = g[varia][i][j].first;
          if (to == matching[i]) {
            g_or[varia][i].push_back({to, g[varia][i][j].second});
          } else {
            g_or[varia][to].push_back({i, g[varia][i][j].second});
          }
        }
      }
    }
    for (int i = 0; i < m + n - 1; i++) {
      if (!not_free[i]) {
        free_vert.push_back(i);
      }
    }

    // найти покрытие
    used.assign(2 * (m + n - 1), 0);
    for (int vertex : free_vert) {
      dfs(vertex, varia);
    }

    for (int i = 0; i < m + n - 1; i++) {
      if (used[i] == 0) {
        ans[varia].push_back(i);
      }
    }

    for (int i = m + n - 1; i < 2 * (m + n - 1); i++) {
      if (used[i] != 0) {
        ans[varia].push_back(i);
      }
    }
  }

  int good = ans[0].size() < ans[1].size() ? 0 : 1;

  cout << ans[good].size() << '\n';
  for (int vertex : ans[good]) {
    cout << (vertex >= m + n - 1 ? 2 : 1) << ' ';
    cout << g[good][vertex].back().second.i << ' ' << g[good][vertex].back().second.j << ' ';
    cout << g[good][vertex].back().second.color <<'\n';
  }
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  find_par();
  return 0;
}
