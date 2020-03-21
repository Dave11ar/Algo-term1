#include<bits/stdc++.h>

using namespace std;

vector<int> p, siz;

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
  p[b] = a;
}


struct inq {
  bool type;
  int a;
  int b;

  inq(bool type, int a, int b) :
      type(type), a(a), b(b) {}
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m, k;
  cin >> n >> m >> k;

  p.resize(n);
  siz.resize(n);
  vector<inq> vec;

  for (int i = 0; i < n; i++) {
    p[i] = i;
    siz[i] = 1;
  }

  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
  }

  for (int i = 0; i < k; i++) {
    string tmp;
    int a, b;
    cin >> tmp >> a >> b;
    a--; b--;

    if (tmp == "ask") {
      vec.push_back(inq(true, a, b));
    } else {
      vec.push_back(inq(false, a, b));
    }
  }

  vector<bool> ans;

  for (int i = k - 1; i >= 0; i--) {
    if (vec[i].type) {
      ans.push_back(find_set(vec[i].a) == find_set(vec[i].b));
    } else {
      union_set(vec[i].a, vec[i].b);
    }
  }

  for (int i = int(ans.size()) - 1; i >= 0; i--) {
    cout << (ans[i] ? "YES" : "NO") << '\n';
  }

  return 0;
}
