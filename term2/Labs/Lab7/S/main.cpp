#include <bits/stdc++.h>

using namespace std;

int k;
vector<pair<int, int>> rmq;
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
  ln = (int)(log(k) / log(2)) + 1;

  num_to_node.resize(k);
  for (int i = 0; i < k; i++) {
    num_to_node[i] = new node(i);
  }

  num_to_rmq.resize(k);

  for (int i = 1; i < k; i++) {
    int a, b;
    cin >> a >> b;
    a--; b--;

    num_to_node[a]->edges.push_back(num_to_node[b]);
    num_to_node[b]->edges.push_back(num_to_node[a]);
  }
}

void dfs(node* v, int d, int par) {
  num_to_rmq[v->id] = (int)rmq.size();
  rmq.emplace_back(d, v->id);

  for (int i = 0; i < (int)v->edges.size(); i++) {
    if (v->edges[i]->id != par) {
      dfs(v->edges[i], d + 1, v->id);
      rmq.emplace_back(d, v->id);
    }
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

pair<int, int> take_sparse(int l, int r) {
  l = num_to_rmq[l];
  r = num_to_rmq[r];
  if (r < l) swap(l, r);

  int cur_log = fl(r - l + 1);

  if (l == r) {
    return sparse[l][0];
  }

  pair<int, int> a = sparse[l][cur_log];
  pair<int, int> b = sparse[r - (1 << cur_log) + 1][cur_log];

  return (a.first < b.first ? a : b);
}
int root = 0;

void output() {
  int p;
  cin >> p;

  for (int i = 0; i < p; i++) {
    char type;
    cin >> type;

    if (type == '?') {
      int a, b;
      cin >> a >> b;
      a--; b--;

      vector<pair<int, int>> bruh {take_sparse(a, b),
                                   take_sparse(root, a),
                                   take_sparse(root, b)};
      sort(bruh.begin(), bruh.end());
      cout << bruh[2].second + 1 << '\n';
    } else {
      int a;
      cin >> a;
      a--;

      root = a;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  while (cin >> k) {
    if (k == 0) {
      return 0;
    }

    root = 0;
    rmq.resize(0);
    num_to_node.resize(0);
    num_to_rmq.resize(0);
    sparse.resize(0);

    input();
    dfs(num_to_node[0], 0, 0);
    make_sparse();
    output();
  }
  return 0;
}
