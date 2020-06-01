#include <bits/stdc++.h>

#define ll long long

using namespace std;

vector<ll> tree;
vector<ll> add;
vector<ll> nw;

void push(int v, int l, int r) {
  if (nw[v] != LONG_LONG_MAX) {
    tree[v] = nw[v];
  }
  tree[v] += add[v];

  if (l != r) {
    if (nw[v] != LONG_LONG_MAX) {
      nw[v * 2] = nw[v];
      nw[v * 2 + 1] = nw[v];
      add[v * 2] = add[v];
      add[v * 2 + 1] = add[v];
    } else {
      add[v * 2] += add[v];
      add[v * 2 + 1] += add[v];
    }
  }
  nw[v] = LONG_LONG_MAX;
  add[v] = 0;
}

ll func(int v, int l, int r, int dl, int dr) {
  push(v, l, r);

  if (dl > dr) return LONG_LONG_MAX;
  if (l == dl && r == dr) {
    return tree[v];
  }

  int mid = (l + r) / 2;

  ll ans = min(func(v * 2, l, mid, dl, min(mid, dr)),
             func(v * 2 + 1, mid + 1, r, max(dl, mid + 1), dr));
  push(v * 2, l, mid);
  push(v * 2 + 1, mid + 1, r);
  tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
  return ans;
}

void set_val(int v, int l, int r, int dl, int dr, ll x) {
  push(v, l, r);

  if (dl > dr) return;
  if (l == dl && r == dr) {
    if (l == r) {
      tree[v] = x;
    } else {
      nw[v] = x;
    }
    return;
  }

  int mid = (l + r) / 2;

  set_val(v * 2, l, mid, dl, min(mid, dr), x);
  set_val(v * 2 + 1, mid + 1, r, max(dl, mid + 1), dr, x);

  push(v * 2, l, mid);
  push(v * 2 + 1, mid + 1, r);
  tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
}

void add_val(int v, int l, int r, int dl, int dr, ll x) {
  push(v, l, r);

  if (dl > dr) return;
  if (l == dl && r == dr) {
    if (l == r) {
      tree[v] += x;
    } else {
      add[v] += x;
    }
    return;
  }

  int mid = (l + r) / 2;

  add_val(v * 2, l, mid, dl, min(mid, dr), x);
  add_val(v * 2 + 1, mid + 1, r, max(dl, mid + 1), dr, x);

  push(v * 2, l, mid);
  push(v * 2 + 1, mid + 1, r);
  tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;

  tree.resize(4* n, 0);
  nw.resize(4* n, LONG_LONG_MAX);
  add.resize(4* n, 0);

  for (int i = 0; i < n; i++) {
    ll x;
    cin >> x;

    set_val(1, 0, n - 1, i, i, x);
  }

  while (cin) {
    string type;
    int l, r;
    cin >> type >> l >> r;
    if (type == "set") {
      ll x;
      cin >> x;

      set_val(1, 0, n - 1, l - 1, r - 1, x);
    } else if (type == "add") {
      ll x;
      cin >> x;

      add_val(1, 0, n - 1, l - 1, r - 1, x);
    } else {
      cout << func(1, 0, n - 1, l - 1, r - 1) << '\n';
    }
  }

  return 0;
}
