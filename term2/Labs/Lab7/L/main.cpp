#include <bits/stdc++.h>

#define uint unsigned int

using namespace std;

uint a, b;
uint cur = 0;
uint nextRand17() {
  cur = cur * a + b;
  return cur >> 15;
}

uint nextRand24() {
  cur = cur * a + b;
  return cur >> 8;
}

uint q;
uint f[1 << 17];

vector<vector<int>> tree(1 << 19);

void merge_vec(vector<int> &res, vector<int> const& vec1, vector<int> const& vec2) {
  size_t i = 0;
  size_t j = 0;

  while (i != vec1.size() || j != vec2.size()) {
    if (i == vec1.size()) {
      res.push_back(vec2[j++]);
      continue;
    }
    if (j == vec2.size()) {
      res.push_back(vec1[i++]);
      continue;
    }

    res.push_back(vec1[i] < vec2[j] ? vec1[i++] : vec2[j++]);
  }
}

void build_tree(uint v, uint l, uint r) {
  if (l == r) {
    tree[v].push_back(f[l]);
    return;
  }
  uint mid = (l + r) / 2;

  build_tree(v * 2, l, mid);
  build_tree(v * 2 + 1, mid + 1, r);
  merge_vec(tree[v], tree[v * 2], tree[v * 2 + 1]);
}

uint bin(uint v, uint x, uint y) {
  uint l = (lower_bound(tree[v].begin(), tree[v].end(), x) - tree[v].begin());
  uint r = (upper_bound(tree[v].begin(), tree[v].end(), y) - tree[v].begin());

  return r - l;
}

uint res_tree(uint v, uint l, uint r, uint dl, uint dr, uint x, uint y) {
  if (dr < dl) return 0;
  if (l == dl && r == dr) {
    return bin(v, x, y);
  }
  uint mid = (l + r) / 2;

  return res_tree(v * 2, l, mid, dl, min(dr, mid), x, y) +
      res_tree(v * 2 + 1, mid + 1, r, max(dl, mid + 1), dr, x, y);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> q >> a >> b;

  for (uint & i : f) {
    i = nextRand24();
  }

  build_tree(1, 0, (1 << 17) - 1);
  uint ans = 0;

  for (uint i = 0; i < q; i++) {
    uint l = nextRand17();
    uint r = nextRand17();
    if (l > r) swap(l, r);
    uint x = nextRand24();
    uint y = nextRand24();
    if (x > y) swap(x, y);

    uint c = res_tree(1, 0, (1 << 17) - 1, l, r, x, y);

    ans += c;
    b += c;
  }

  cout << ans;

  return 0;
}
