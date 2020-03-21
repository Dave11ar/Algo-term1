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
  mimx[a] = { min(mimx[a].first, mimx[b].first) , max(mimx[a].second, mimx[b].second) };
  p[b] = a;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;

  p.resize(n);
  siz.resize(n);
  mimx.resize(n);

  for (int i = 0; i < n; i++) {
    p[i] = i;
    siz[i] = 1;
    mimx[i] = { i + 1 , i + 1};
  }

  string type;

  while (cin >> type) {
    if (type == "union") {
      int a, b;
      cin >> a >> b;

      union_set(a - 1, b - 1);
    } else {
      int a;
      cin >> a;
      a = find_set(a - 1);

      cout << mimx[a].first << ' ' << mimx[a].second << ' ' << siz[a] << '\n';
    }
  }
  return 0;
}
