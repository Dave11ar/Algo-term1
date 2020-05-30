#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> vec(1000000);

int hash_code(int a) {
  return abs(a) % 1000000;
}

void set_insert(int a) {
  int cur_hash = hash_code(a);

  for (int i = 0; i < (int)vec[cur_hash].size(); i++) {
    if (vec[cur_hash][i] == a) {
      return;
    }
  }
  vec[cur_hash].push_back(a);
}

void set_delete(int a) {
  int cur_hash = hash_code(a);

  for (int i = 0; i < (int)vec[cur_hash].size(); i++) {
    if (vec[cur_hash][i] == a) {
      vec[cur_hash].erase(vec[cur_hash].begin() + i);
      return;
    }
  }
}

bool set_exists(int a) {
  int cur_hash = hash_code(a);

  for (int i = 0; i < (int)vec[cur_hash].size(); i++) {
    if (vec[cur_hash][i] == a) {
      return true;
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("set.in", "r", stdin);
  freopen("set.out", "w", stdout);

  string s;

  while (cin >> s) {
    int a;
    cin >> a;

    if (s == "insert") {
      set_insert(a);
    } else if (s == "delete") {
      set_delete(a);
    } else if (s == "exists") {
      if (set_exists(a)) {
        cout << "true";
      } else {
        cout << "false";
      }
      cout << '\n';
    }
  }


  return 0;
}
