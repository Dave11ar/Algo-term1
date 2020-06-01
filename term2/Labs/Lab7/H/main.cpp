#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> tree;

void modify(int v, int l, int r, int pos, int nw_val) {
  if (l == r) {
    tree[v] = nw_val;
    return;
  }
  int mid = (l + r) / 2;

  if (pos <= mid) {
    modify(v * 2, l, mid, pos, nw_val);
  } else {
    modify(v * 2 + 1, mid + 1, r, pos, nw_val);
  }

  tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
}

int free_place(int v, int l, int r, int dl, int dr) {
  if (dl > dr) return INT_MAX;
  if (l == dl && r == dr) {
    return tree[v];
  }

  int mid = (l + r) / 2;

  return min(free_place(v * 2, l, mid, dl, min(mid, dr)),
      free_place(v * 2 + 1, mid + 1, r, max(dl, mid + 1), dr));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> m;
  tree.resize(4 * n);

  for (int i = 0; i < n; i++) {
    modify(1, 0, n - 1, i, i);
  }


  for (int i = 0; i < m; i++) {
    string type;
    int x;
    cin >> type >> x;

    if (type == "enter") {
      int cur_pos = free_place(1, 0, n - 1, x - 1, n - 1);
      if (cur_pos == INT_MAX) {
        cur_pos = free_place(1, 0, n - 1, 0, x - 2);
      }

      cout << cur_pos + 1 << '\n';
      modify(1, 0, n - 1, cur_pos, INT_MAX);
    } else {
      modify(1, 0, n - 1, x - 1, x - 1);
    }
  }

  return 0;
}
