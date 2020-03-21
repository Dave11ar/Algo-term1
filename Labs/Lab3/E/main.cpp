#include<bits/stdc++.h>

using namespace std;

vector<int> p, siz;
vector<pair<int, int>> mimx;

int find_set(int a) {
  if (a == p[a]) {
    return a;
  }

  return p[a] = find_set(p[a]);
}

void union_set(int a, int b) {
  a = find_set(a);
  b = find_set(b);

  if (a == b) return;
  if (siz[a] < siz[b]) swap(a, b);

  siz[a] += siz[b];
  mimx[a] = { min(mimx[a].first, mimx[b].first) ,
              max(mimx[a].second, mimx[b].second) };
  p[b] = a;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, q;
  cin >> n >> q;
  p.resize(2 * n);
  siz.resize(2 * n);
  mimx.resize(2 * n);

  for (int i = 0; i < 2 * n; i++) {
    p[i] = i;
    mimx[i] = { i , i };
  }

  for (int i = 0; i < q; i++) {
    int type, a, b;
    cin >> type >> a >> b;
    a--; b--;

    if (type == 1) {
      union_set(a, b);
    } else if (type == 2) {
      int l = mimx[find_set(a + n)].second - n;
      int r = mimx[find_set(b + n)].first - n;

      for (int j = l; j <= r; j++) {
        union_set(a, j);
        union_set(a + n, j + n);
      }
    } else {
      if (find_set(a) == find_set(b)) {
        cout << "YES";
      } else {
        cout << "NO";
      }
      cout << '\n';
    }
  }

  return 0;
}
