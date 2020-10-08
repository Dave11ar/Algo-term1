#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<string>> vec;
set<int> not_zero;

void input() {
  cin >> n;
  vector<string> cur_length;
  string last;
  bool smaller = false;
  for (int i = 0; i < n; i++) {
    string tmp;
    cin >> tmp;

    if (tmp.size() > 1) {
      not_zero.insert(tmp[0] - 'a');
    }

    if (tmp.length() < last.length()) {
      smaller = true;
    }

    if (!cur_length.empty() && tmp.length() != cur_length.back().length()) {
      vec.emplace_back(cur_length);
      cur_length.clear();
    }
    cur_length.emplace_back(tmp);
    last = tmp;
  }
  vec.emplace_back(cur_length);

  if (smaller) {
    cout << "No\n";
    exit(0);
  }
}

int find_first(string const& a, string const& b) {
  for (size_t i = 0; i < a.length(); i++) {
    if (a[i] != b[i]) {
      return i;
    }
  }
  return -1;
}

// edge u -> v if u < v
vector<vector<int>> g(26);

void make_g() {
  for (vector<string> const& cur : vec) {
    for (size_t i = 1; i < cur.size(); i++) {
      int fir_not_eq = find_first(cur[i], cur[i - 1]);
      if (fir_not_eq == -1) {
        cout << "No\n";
        exit(0);
      }

      g[cur[i - 1][fir_not_eq] - 'a'].push_back(cur[i][fir_not_eq] - 'a');
    }
  }
}

vector<int> top_sort, used(26, 0);
vector<int> in(26);
void dfs(int v) {
  used[v] = 1;

  for (int to : g[v]) {
    in[to]++;
    if (used[to] == 0) {
      dfs(to);
    } else if (used[to] == 1) {
      cout << "No\n";
      exit(0);
    }
  }
  used[v] = 2;
  top_sort.push_back(v);
}

vector<int> ans(26, -1);

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  make_g();

  for (int i = 0; i < 26; i++) {
    if (used[i] == 0) {
      dfs(i);
    }
  }
  reverse(top_sort.begin(), top_sort.end());

  used.assign(26, 0);
  int sc = 1;
  bool zero = false;
  for (int i : top_sort) {
    if (ans[i] != -1) {
      continue;
    }

    if (!not_zero.count(i) && !zero) {
      zero = true;
      ans[i] = 0;
    } else {
      ans[i] = sc++;
    }
  }

  if (!zero) {
    cout << "No\n";
    return 0;
  }

  cout << "Yes\n";
  for (int i = 0; i < 26; i++) {
    cout << ans[i] << ' ';
  }

  return 0;
}
