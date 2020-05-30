#include <bits/stdc++.h>

using namespace std;

vector<long long> tree;

long long func(int v, int l, int r, int dl, int dr) {
  if (dl > dr) return LONG_LONG_MAX;
  if (l == dl && r == dr) {
    return tree[v];
  }

  int mid = (l + r) / 2;

  return min(func(v * 2, l, mid, dl, min(mid, dr)),
             func(v * 2 + 1, mid + 1, r, max(dl, mid + 1), dr));
}

void set_do(int v, int l, int r, int t, long long x) {
  if (l == r) {
    tree[v] = x;
    return;
  }

  int mid = (l + r) / 2;

  t <= mid ? set_do(v * 2, l, mid, t, x) : set_do(v * 2 + 1, mid + 1, r, t, x);


  tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;
  tree.resize(4 * n);

  for (int i = 0; i < n; i++) {
    long long x;
    cin >> x;
    set_do(1, 0, n - 1, i, x);
  }

  while (cin) {
    string type;
    cin >> type;

    if (type == "min") {
      int l, r;
      cin >> l >> r;

      cout << func(1, 0, n - 1, l - 1, r - 1) << '\n';
    } else {
      int t;
      long long x;
      cin >> t >> x;

      set_do(1, 0, n - 1, t - 1, x);
    }
  }

  return 0;
}
