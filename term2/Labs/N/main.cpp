#include <bits/stdc++.h>
#define ll long long

using namespace std;

int nx, ny, nz;

vector<vector<vector<ll>>> c, d;

void suf_modify(int x, int y, int z, ll k) {
  for (int ix = x; ix < nx; ix = ix | (ix + 1)) {
    for (int iy = y; iy < ny; iy = iy | (iy + 1)) {
      for (int iz = z; iz < nz; iz = iz | (iz + 1)) {
        c[ix][iy][iz] += k;
        d[ix][iy][iz] += k * x * y * z;
      }
    }
  }
}

/*
private void update(int left, int right, int by) {
    internalUpdate(left, by, -by * (left - 1));
    internalUpdate(right, -by, by * right);
}

private void internalUpdate(int at, int mul, int add) {
    while (at < dataMul.length) {
        dataMul[at] += mul;
        dataAdd[at] += add;
        at |= (at + 1);
    }
}

private int query(int at) {
    int mul = 0;
    int add = 0;
    int start = at;
    while (at >= 0) {
        mul += dataMul[at];
        add += dataAdd[at];
        at = (at & (at + 1)) - 1;
    }
    return mul * start + add;
}
*/

void modify(int x1, int y1, int z1, int x2, int y2, int z2, ll k) {
  x2++, y2++, z2++;

  suf_modify(x1, y1, z1, k);

  suf_modify(x1, y1, z2, -k);
  suf_modify(x1, y2, z1, -k);
  suf_modify(x2, y1, z1, -k);

  suf_modify(x1, y2, z2, k);
  suf_modify(x2, y2, z1, k);
  suf_modify(x2, y1, z2, k);

  suf_modify(x2, y2, z2, -k);
}

ll pref_res(int x, int y, int z) {
  ll sum = 0;

  for (int ix = x; ix >= 0; ix = (ix & (ix + 1)) - 1) {
    for (int iy = y; iy >= 0; iy = (iy & (iy + 1)) - 1) {
      for (int iz = z; iz >= 0; iz = (iz & (iz + 1)) - 1) {
        sum += c[ix][iy][iz] * x * y * z + d[ix][iy][iz];
      }
    }
  }
  return sum;
}

ll sum(int x1, int y1, int z1, int x2, int y2, int z2) {
  x1--; y1--; z1--;
  return pref_res(x2, y2, z2)
  - (pref_res(x1, y2, z2) + pref_res(x2, y1, z2) + pref_res(x2, y2, z1))
  + (pref_res(x2, y1, z1) + pref_res(x1, y2, z1) + pref_res(x1, y1, z1))
  - pref_res(x1, y1, z1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int q;
  cin >> nx >> ny >> nz >> q;
  nx += 5;
  ny += 5;
  nz += 5;

  c.resize(nx, vector<vector<ll>>(ny, vector<ll>(nz)));
  d.resize(nx, vector<vector<ll>>(ny, vector<ll>(nz)));

  for (int i = 0; i < q; i++) {
    char type;
    int x1, y1, z1, x2, y2, z2;
    cin >> type >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
    x2--; y2--; z2--;

    if (type == 's') {
      cout << sum(x1, y1, z1, x2, y2, z2) << '\n';
    } else {
      ll value;
      cin >> value;

      modify(x1, y1, z1, x2, y2, z2, value);
    }
  }

  return 0;
}
