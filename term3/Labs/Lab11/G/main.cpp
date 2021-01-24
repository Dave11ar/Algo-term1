#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> u, v, matching, prev_column;
vector<vector<int>> matrix;

void input() {
  cin >> n;
  u.resize(n + 1);
  v.resize(n + 1);
  matching.resize(n + 1);
  prev_column.resize(n + 1);

  matrix.resize(n + 1, vector<int>(n + 1));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> matrix[i][j];
    }
  }
}

void hungarian() {
  input();

  for (int i = 1; i <= n; i++) {
    matching[0] = i;
    int column_free = 0;
    int column_min;
    vector<int> min_potential_diff(n + 1, INT_MAX);
    vector<bool> used(n + 1);

    while (true) {
      used[column_free] = true;
      int line = matching[column_free];
      int delta = INT_MAX;

      for (int j = 1; j <= n; j++) {
        if (!used[j]) {
          int diff = matrix[line][j] - u[line] - v[j];

          if (diff < min_potential_diff[j]) {
            min_potential_diff[j] = diff;
            prev_column[j] = column_free;
          }

          if (min_potential_diff[j] < delta) {
            delta = min_potential_diff[j];
            column_min = j;
          }
        }
      }

      for (int j = 0; j <= n; j++) {
        if (used[j]) {
          u[matching[j]] += delta;
          v[j] -= delta;
        } else {
          min_potential_diff[j] -= delta;
        }
      }

      if (matching[column_free = column_min] == 0) {
        break;
      }
    }

    while (true) {
      matching[column_free] = matching[column_min = prev_column[column_free]];

      if ((column_free = column_min) == 0) {
        break;
      }
    }
  }

  int sum = 0;
  vector<int> ans(n + 1);
  for (int j = 1; j <= n; j++) {
    sum += matrix[matching[j]][j];
    ans[matching[j]] = j;
  }

  cout << sum << '\n';
  for (int i = 1; i <= n; i++) {
    cout << i << ' ' << ans[i] << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  hungarian();

  return 0;
}
