#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> used;
vector<int> ans;
int N, M;

void input() {
  cin >> N >> M;
  g.resize(N);
  used.resize(N);

  for (int i = 0; i < M; i++) {
    int l, r;
    cin >> l >> r;
    l--; r--;

    g[l].push_back(r);
  }
}

int dfs(int v) {
  used[v] = 1;

  for (int i = 0; i < (int)g[v].size(); i++) {
    if (used[g[v][i]] == 2) {
      continue;
    } else {
      if (used[g[v][i]] == 1) {
        ans.push_back(v);
        return g[v][i];
      } else {
        int t = dfs(g[v][i]);
        if (t != -1) {
          ans.push_back(v);

          if (t == v) {
             cout << "YES\n";
            if ((int)ans.size() != 0) {
              reverse(ans.begin(), ans.end());
              for (int j = 0; j < (int)ans.size(); j++) {
                cout << ans[j] + 1 << ' ';
              }
            }
            exit(0);
          }

          return t;
        }
      }
    }
  }
  used[v] = 2;
  return -1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  for (int i = 0; i < N; i++) {
    if (used[i] != 2) {
      dfs(i);
    }
  }

  cout << "NO";

  return 0;
}
