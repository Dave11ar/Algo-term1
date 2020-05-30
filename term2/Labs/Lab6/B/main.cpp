#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<string, string>>> vec(1000000);
vector<int> st(20);

int hash_code(string a) {
  int cur_hash = 0;

  for (int i = 0; i < (int)a.length(); i++) {
    cur_hash += st[i] * a[i];
  }
  return abs(cur_hash) % 1000000;
}

void map_insert(pair<string, string> a) {
  int cur_hash = hash_code(a.first);

  for (int i = 0; i < (int)vec[cur_hash].size(); i++) {
    if (vec[cur_hash][i].first == a.first) {
      vec[cur_hash][i].second = a.second;
      return;
    }
  }
  vec[cur_hash].push_back(a);
}

void map_delete(string a) {
  int cur_hash = hash_code(a);

  for (int i = 0; i < (int)vec[cur_hash].size(); i++) {
    if (vec[cur_hash][i].first == a) {
      vec[cur_hash].erase(vec[cur_hash].begin() + i);
      return;
    }
  }
}

string map_get(string a) {
  int cur_hash = hash_code(a);

  for (int i = 0; i < (int)vec[cur_hash].size(); i++) {
    if (vec[cur_hash][i].first == a) {
      return vec[cur_hash][i].second;
    }
  }
  return "*";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("map.in", "r", stdin);
  freopen("map.out", "w", stdout);

  st[0] = 63;
  for (int i = 1; i < 20; i++) {
    st[i] = st[i - 1] * 63;
  }

  string s;

  while (cin >> s) {
    string a;
    cin >> a;

    if (s == "put") {
      string tmp;
      cin >> tmp;
      map_insert({a, tmp});
    } else if (s == "delete") {
      map_delete(a);
    } else if (s == "get") {
      string tmp = map_get(a);
      if (map_get(a) != "*") {
        cout << map_get(a);
      } else {
        cout << "none";
      }
      cout << '\n';
    }
  }






  return 0;
}
