#include <bits/stdc++.h>

using namespace std;

int n;
pair<int, int> mx = {-1, -1};
vector<vector<int>> vec;
vector<long long> d_hash(1e5);

void dfs(int v, int p, int depth) {
  if (depth > mx.second) {
    mx = {v, depth};
  }

  for (int i = 0; i < (int)vec[v].size(); i++) {
    if (vec[v][i] != p) {
      dfs(vec[v][i], v, depth + 1);
    }
  }
}

long long shiza_hash(int v, int p, long long depth) {
  long long hash = depth;

  for (int i = 0; i < (int)vec[v].size(); i++) {
    if (vec[v][i] != p) {
      hash += depth * shiza_hash(vec[v][i], v, depth + 1);
    }
  }
  return hash;
}
bool opa = false;
int dep;
int res;
void middle(int v, int p) {
  if (v == mx.first) {
    opa = true;
    dep--;
    return;
  }
  for (int i = 0; i < (int)vec[v].size(); i++) {
    if (vec[v][i] != p) {
      middle(vec[v][i], v);
    }
    if (opa) break;
  }

  if (dep == mx.second / 2 + 1) {
    res = v;
    dep = -1;
    return;
  }
  if (opa) {
    dep--;
    return;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  d_hash[0] = 67;
  for (int i = 1; i < 1e5; i++) {
    d_hash[i] = 67 * d_hash[i - 1];
  }

  cin >> n;
  vec.resize(n);

  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;

    vec[u].push_back(v);
    vec[v].push_back(u);
  }

  dfs(0, 0, 1);
  int tmp = mx.first;
  mx.second = -1;
  dfs(mx.first, mx.first, 1);

  dep = mx.second;

  if (mx.second % 2 == 0) {
    cout << "NO";
    return 0;
  }
  middle(tmp, tmp);
  if ((int)vec[res].size() != 2) {
    cout << "NO";
    return 0;
  }
  if (shiza_hash(vec[res][0], res, 2) ==
      shiza_hash(vec[res][1], res, 2)) {
    cout << "YES";
    return 0;
  }
  cout << "NO"г

  return 0;
}
