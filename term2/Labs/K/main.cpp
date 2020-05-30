#include <bits/stdc++.h>

using namespace std;

int k;
vector<pair<int, int>> get_lca, rmq;
vector<int> num_to_rmq;
vector<vector<pair<int, int>>> sparse;
int ln;

struct node {
  int id;
  vector<node*> edges;

  explicit node(int id) : id(id) {}
};
vector<node*> num_to_node;

void input() {
  cin >> k;
  ln = (int)(log(k) / log(2)) + 1;
  num_to_node.resize(k);
  num_to_node[0] = new node(0);
  num_to_rmq.resize(k);
  int a, b;

  for (int i = 0; i < k; i++) {
    string s;
    cin >> s >> a >> b;
    a--; b--;

    if (s == "ADD") {
      num_to_node[b] = new node(b);
      num_to_node[a]->edges.push_back(num_to_node[b]);
    } else {
      get_lca.emplace_back(a, b);
    }
  }
}

void dfs(node* v, int d) {
  num_to_rmq[v->id] = (int)rmq.size();
  rmq.emplace_back(d, v->id);

  for (int i = 0; i < (int)v->edges.size(); i++) {
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

int take_sparse(int l, int r) {
  l = num_to_rmq[l];
  r = num_to_rmq[r];
  if (r < l) swap(l, r);

  int cur_log = fl(r - l + 1);

  if (l == r) {
    return sparse[l][0].second;
  }

  pair<int, int> a = sparse[l][cur_log];
  pair<int, int> b = sparse[r - cur_log + 1][cur_log];

  return (a.first < b.first ? a.second : b.second);
}

void output() {
  for (pair<int, int> a : get_lca) {
    cout << take_sparse(a.first, a.second) + 1 << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  dfs(num_to_node[0], 0);
  make_sparse();
  output();

  return 0;
}
