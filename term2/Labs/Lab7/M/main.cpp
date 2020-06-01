#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<pair<int, int>>  rmq;
vector<int> num_to_rmq;
vector<vector<pair<int, int>>> sparse;
int ln;

struct node {
  int id;
  vector<node*> edges;

  explicit node(int id) : id(id) {}
};
vector<node*> num_to_node;

void dfs(node* v, int d) {
  num_to_rmq[v->id] = (int)rmq.size();
  rmq.emplace_back(d, v->id);

  for (int i = 0; i < (int) v->edges.size(); i++) {
    dfs(v->edges[i], d + 1);
    rmq.emplace_back(d, v->id);
  }
}

void make_sparse() {
  sparse.resize(rmq.size(), vector<pair<int, int>>(ln + 1));

  for (int i = (int)rmq.size() - 1; i >= 0; i--) {
    sparse[i][0] = rmq[i];
    for (int j = 1; j <= ln; j++) {
      if (i + (1 << (j - 1)) >= (int)rmq.size()) {
        sparse[i][j] = sparse[i][j - 1];
        continue;
      }

      pair<int, int> a = sparse[i][j - 1];
      pair<int, int> b = sparse[i + (1 << (j - 1))][j - 1];

      sparse[i][j] = (a.first < b.first ? a : b);
    }
  }
}

int fl(int v) {
  if (v == 1) {
    return  0;
  } else {
    return fl(v / 2) + 1;
  }
}

vector<int> precalc_ln;

int take_sparse(int l, int r) {
  l = num_to_rmq[l];
  r = num_to_rmq[r];
  if (r < l) swap(l, r);

  int cur_log = precalc_ln[r - l + 1];

  if (l == r) {
    return sparse[l][0].second;
  }

  pair<int, int> a = sparse[l][cur_log];
  pair<int, int> b = sparse[r - (1 << cur_log) + 1][cur_log];

  return (a.first < b.first ? a.second : b.second);
}

void precalc() {
  precalc_ln.resize(sparse.size());
  precalc_ln[0] = 0;
  for (size_t i = 1; i < sparse.size(); i++) {
    precalc_ln[i] = fl(i);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> m;
  num_to_node.resize(n);

  for (int i = 0; i < n; i++) {
    num_to_node[i] = new node(i);
  }

  num_to_rmq.resize(n);

  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;

    num_to_node[p]->edges.push_back(num_to_node[i]);
  }

  dfs(num_to_node[0], 0);

  ln = (int)(log((int)rmq.size()) / log(2)) + 1;
  make_sparse();
  precalc();

  long long a1, a2, x, y, z;
  cin >> a1 >> a2 >> x >> y >> z;

  long long ans = take_sparse((int)a1, (int)a2);

  long long res = ans;

  for (int i = 1; i < m; i++) {
    long long a3 = (x * a1 + y * a2 + z) % n;
    long long a4 = (x * a2 + y * a3 + z) % n;
    a1 = a3;
    a2 = a4;

    ans = take_sparse((int)((a1 + ans) % n), (int)a2);
    res += ans;
  }

  cout << res;

  return 0;
}
