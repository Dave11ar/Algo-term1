#include<bits/stdc++.h>

using namespace std;

vector<pair<int, int>> vertex;
vector<int> siz;

pair<int, int> find_dsu(int a) {
  if (a == vertex[a].first) {
    return vertex[a];
  }

  int tmp = vertex[a].second;
  vertex[a] = find_dsu(vertex[a].first);
  vertex[a].second ^= tmp;
  return vertex[a];
}

void unite_dsu(int a, int b) {
  pair<int, int> vertA = find_dsu(a);
  pair<int, int> vertB = find_dsu(b);

  if (siz[vertA.first] < siz[vertB.first]) {
    swap(vertA, vertB);
  }

  siz[vertA.first] += siz[vertB.first];
  vertex[vertB.first] = { vertA.first , vertA.second ^ vertB.second ^ 1 };
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m;
  cin >> n >> m;

  vertex.resize(n);
  siz.resize(n);

  for (int i = 0; i < n; i++) {
    vertex[i] = { i , 0 };
    siz[i] = 1;
  }

  int shift = 0;
  for (int i = 0; i < m; i++) {
    int type, a, b;
    cin >> type >> a >> b;
    a = (a + shift) % n;
    b = (b + shift) % n;

    if (type == 0) {
      unite_dsu(a, b);
    } else {
      if (find_dsu(a).second == find_dsu(b).second) {
        cout << "YES";
        shift = (shift + 1) % n;
      } else {
        cout << "NO";
      }
      cout << '\n';
    }
  }

  return 0;
}
