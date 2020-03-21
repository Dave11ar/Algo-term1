#include<bits/stdc++.h>

using namespace std;

vector<int> p;

int find_dsu(int a) {
  if (a == p[a]) {
    return a;
  }
  return p[a] = find_dsu(p[a]);
}

void union_dsu(int a, int b) {
  a = find_dsu(a);
  b = find_dsu(b);
  if (a == b) {
    return;
  }

  p[a] = b;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  p.resize(n);

  for (int i = 0; i < n; i++) {
    p[i] = i;
  }

  for (int i = 0; i < n; i++) {
    int cur;
    cin >> cur;
    cur--;

    cur = find_dsu(cur);
    cout << cur + 1 << ' ';
    union_dsu(cur, cur + 1 < n ? cur + 1: 0);
  }

  return 0;
}