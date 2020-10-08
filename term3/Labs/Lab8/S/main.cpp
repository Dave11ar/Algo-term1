#include <bits/stdc++.h>

using namespace std;

int n, l;
vector<int> vec;
vector<vector<int>> pos;
void input() {
  cin >> n >> l;
  vec.resize(l);
  pos.resize(n);

  for (int i = 0; i < l; i++) {
    cin >> vec[i];
    vec[i]--;

    pos[vec[i]].push_back(i);
  }
}

set<pair<int, int>> ans;

void go(int left, int right, int mn, int v) {
  for (int i = left; i < right; i++) {
    if (vec[i] > mn) {
      ans.insert({v + 1, vec[i] + 1});
    }
  }
}

void solution() {
  for (int i = 0; i < n; i++) {
    if (pos[i].size() == 1) {
      continue;
    }

    for (size_t j = 1; j < pos[i].size(); j++) {
      ans.insert({i + 1, vec[pos[i][j - 1] + 1] + 1});

      go(pos[i][j - 1] + 1, pos[i][j], vec[pos[i][j - 1] + 1], i);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  solution();

  cout << ans.size() << '\n';

  for (pair<int, int> a : ans) {
    cout << a.first << ' ' << a.second << '\n';
  }

  return 0;
}
