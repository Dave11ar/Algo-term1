#include <bits/stdc++.h>

using namespace std;

struct node{
  string value;
  node* prev;
  node* next;

  node(string value, node* prev, node* next) :
      value(value), prev(prev), next(next){}
};

struct key_node{
  string key;
  node* pos;

  key_node(string key, node* pos) :
      key(key), pos(pos){}
};

vector<vector<key_node>> vec(1000000);
vector<int> st(20);
node* last;

int hash_code(string a) {
  int cur_hash = 0;

  for (int i = 0; i < (int)a.length(); i++) {
    cur_hash += st[i] * a[i];
  }
  return abs(cur_hash) % 1000000;
}

void map_insert(string key, string value) {
  int cur_hash = hash_code(key);

  for (int i = 0; i < (int)vec[cur_hash].size(); i++) {
    if (vec[cur_hash][i].key == key) {
      vec[cur_hash][i].pos->value = value;
      return;
    }
  }

  if (last == nullptr) {
    last = new node(value, nullptr, nullptr);
  } else {
    last->next = new node(value, last, nullptr);
    last = last->next;
  }
  vec[cur_hash].push_back(key_node(key, last));
}

void map_delete(string key) {
  int cur_hash = hash_code(key);

  for (int i = 0; i < (int)vec[cur_hash].size(); i++) {
    if (vec[cur_hash][i].key == key) {
      if (vec[cur_hash][i].pos->prev != nullptr) {
        vec[cur_hash][i].pos->prev->next = vec[cur_hash][i].pos->next;
      }
      if (vec[cur_hash][i].pos->next != nullptr) {
        vec[cur_hash][i].pos->next->prev = vec[cur_hash][i].pos->prev;
      } else {
        last = vec[cur_hash][i].pos->prev;
      }

      vec[cur_hash].erase(vec[cur_hash].begin() + i);
      return;
    }
  }
}

string map_get(string key) {
  int cur_hash = hash_code(key);

  for (int i = 0; i < (int)vec[cur_hash].size(); i++) {
    if (vec[cur_hash][i].key == key) {
      return vec[cur_hash][i].pos->value;
    }
  }
  return "none";
}

string map_prev(string key) {
  int cur_hash = hash_code(key);

  for (int i = 0; i < (int)vec[cur_hash].size(); i++) {
    if (vec[cur_hash][i].key == key) {
      if (vec[cur_hash][i].pos->prev != nullptr) {
        return vec[cur_hash][i].pos->prev->value;
      }
    }
  }
  return "none";
}

string map_next(string key) {
  int cur_hash = hash_code(key);

  for (int i = 0; i < (int)vec[cur_hash].size(); i++) {
    if (vec[cur_hash][i].key == key) {
      if (vec[cur_hash][i].pos->next != nullptr) {
        return vec[cur_hash][i].pos->next->value;
      }
    }
  }
  return "none";
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  freopen("linkedmap.in", "r", stdin);
  freopen("linkedmap.out", "w", stdout);

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
      map_insert(a, tmp);
    } else if (s == "delete") {
      map_delete(a);
    } else if (s == "get") {
      cout << map_get(a) << '\n';
    } else if (s == "prev") {
      cout << map_prev(a) << '\n';
    } else {
      cout << map_next(a) << '\n';
    }
  }






  return 0;
}
