#include <bits/stdc++.h>

using namespace std;

vector<int> st(20);

struct my_set {
  vector<vector<string>> mas;

  static int hash_code(string a) {
    int cur_hash = 0;

    for (int i = 0; i < (int)a.length(); i++) {
      cur_hash += st[i] * a[i];
    }
    return abs(cur_hash) % 100;
  }

  void set_insert(string key) {
    int cur_hash = hash_code(key);

    for (int i = 0; i < (int) mas[cur_hash].size(); i++) {
      if (mas[cur_hash][i] == key) {
        return;
      }
    }
    mas[cur_hash].push_back(key);
  }

  void set_delete(string key) {
    int cur_hash = hash_code(key);

    for (int i = 0; i < (int) mas[cur_hash].size(); i++) {
      if (mas[cur_hash][i] == key) {
        mas[cur_hash].erase(mas[cur_hash].begin() + i);
        return;
      }
    }
  }

  void set_get() {
    vector<string> out;
    for (int i = 0; i < 100; i++) {
      for (int j = 0; j < (int) mas[i].size(); j++) {
        out.push_back(mas[i][j]);
      }
    }

    cout << out.size();
    for (int i = 0; i < (int)out.size(); i++) {
      cout << ' ' << out[i];
    }
    cout << '\n';
  }

  my_set() {
    mas.resize(100);
  }
};

struct node{
  string key;
  my_set bruh_set;

  node(string keyt) {
    key = keyt;
    bruh_set = my_set();
  }
};

vector<vector<node>> vec(100000);

int hash_code(string a) {
  int cur_hash = 0;

  for (int i = 0; i < (int)a.length(); i++) {
    cur_hash += st[i] * a[i];
  }
  return abs(cur_hash) % 100000;
}

void map_put(string key, string value) {
  int cur_hash = hash_code(key);

  for (int i = 0; i < (int)vec[cur_hash].size(); i++) {
    if (vec[cur_hash][i].key == key) {
      vec[cur_hash][i].bruh_set.set_insert(value);
      return;
    }
  }

  vec[cur_hash].push_back(node(key));
  vec[cur_hash][(int)vec[cur_hash].size() - 1].bruh_set.set_insert(value);
}

void map_delete(string key, string value) {
  int cur_hash = hash_code(key);

  for (int i = 0; i < (int)vec[cur_hash].size(); i++) {
    if (vec[cur_hash][i].key == key) {
      vec[cur_hash][i].bruh_set.set_delete(value);
    }
  }
}

void map_deleteall(string key) {
  int cur_hash = hash_code(key);

  for (int i = 0; i < (int)vec[cur_hash].size(); i++) {
    if (vec[cur_hash][i].key == key) {
      vec[cur_hash][i].bruh_set = my_set();
      return;
    }
  }
}

void map_get(string key) {
  int cur_hash = hash_code(key);

  for (int i = 0; i < (int)vec[cur_hash].size(); i++) {
    if (vec[cur_hash][i].key == key) {
      vec[cur_hash][i].bruh_set.set_get();
      return;
    }
  }
  cout << 0 << '\n';
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("multimap.in", "r", stdin);
  freopen("multimap.out", "w", stdout);

  st[0] = 63;
  for (int i = 1; i < 20; i++) {
    st[i] = st[i - 1] * 63;
  }

  string s;

  while (cin >> s) {
    string key;
    cin >> key;

    if (s == "put") {
      string value;
      cin >> value;
      map_put(key, value);
    } else if (s == "delete") {
      string value;
      cin >> value;
      map_delete(key, value);
    } else if (s == "deleteall") {
      map_deleteall(key);
    } else if (s == "get") {
      map_get(key);
    }
  }






  return 0;
}
