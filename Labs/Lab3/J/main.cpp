#include<bits/stdc++.h>

using namespace std;

vector<int> parent, siz, message, mins;
int q;

int find_dsu(int a) {
  if (a == parent[a]) {
    return a;
  }

  return find_dsu(parent[a]);
}

int get(int a) {
  q += message[a];
  if (a == parent[a]) {
    return a;
  }

  return get(parent[a]);
}

void unite_dsu(int a, int b) {
  if (siz[a] < siz[b]) {
    swap(a, b);
  }

  siz[a] += siz[b];
  message[b] -= message[a];
  parent[b] = a;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  const int p = 1e6 + 3;
  int n, m;
  cin >> n >> m;

  parent.resize(n);
  siz.resize(n, 1);
  message.resize(n);
  mins.resize(n);

  for (int i = 0; i < n; i++) {
    parent[i] = i;
  }

  int zerg = 0;
  for (int i = 0; i < m; i++) {
    int t, a, b;
    cin >> t >> a;
    a = (a + zerg) % n;


    if (t == 1) {
      message[find_dsu(a)]++;
      zerg = (30 * zerg + 239) % p;
    } else if (t == 2) {
      cin >> b;
      b = (b + zerg) % n;
      a = find_dsu(a);
      b = find_dsu(b);

      if (a != b) {
        unite_dsu(a, b);
        zerg = (13 * zerg + 11) % p;
      }
    } else {
      q = mins[a];
      get(a);

      cout << q << '\n';
      zerg = (int)((100500 * 1ll * zerg + q) % (long long)p);
      mins[a] -= q;
    }
  }

  return 0;
}
