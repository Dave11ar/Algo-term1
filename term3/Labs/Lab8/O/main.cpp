#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> wires, sockets, comp, place;
vector<bool> used, was, l_wires;
vector<vector<int>> g, rev_g;

void input() {
  cin >> n;
  comp.resize(2 * n);
  g.resize(2 * n);
  rev_g.resize(2 * n);
  wires.resize(n);
  used.resize(2 * n);
  was.resize(n);
  l_wires.resize(2 * n);
  sockets.resize(2 * n);
  place.resize(2 * n);

  for (int &wire : wires) {
    cin >> wire;
  }
  for (int i = 0; i < 2 * n; i++) {
    cin >> sockets[i];
    sockets[i]--;

    if (!was[sockets[i]]) {
      place[sockets[i]] = i + 1;
    } else {
      place[sockets[i] + n] = i + 1;
    }

    l_wires[i] = !was[sockets[i]];
    was[sockets[i]] = true;
  }
}

int get(int i) {
  return l_wires[i] ? sockets[i] : sockets[i] + n;
}

int get_not(int i) {
  return !l_wires[i] ? sockets[i] : sockets[i] + n;
}

int mod(int i) {
  return (i + 2 * n) % (2 * n);
}

void make_sat() {
  for (int i = 0; i < 2 * n; i++) {
    int r = mod(i + 1);
    if (wires[sockets[i]] == wires[sockets[r]]) {
      g[get(i)].push_back(get_not(r));
      g[get(r)].push_back(get_not(i));

      rev_g[get_not(r)].push_back(get(i));
      rev_g[get_not(i)].push_back(get(r));
    }
  }
}

vector<int> top_sort;

void dfs(int v) {
  used[v] = true;

  for (int to : g[v]) {
    if (!used[to]) {
      dfs(to);
    }
  }
  top_sort.push_back(v);
}

int sc = 0;
void dfs_rev(int v) {
  used[v] = true;
  comp[v] = sc;
  for (int to : rev_g[v]) {
    if (!used[to]) {
      dfs_rev(to);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  make_sat();

  for (size_t i = 0; i < g.size(); i++) {
    if (!used[i]) {
      dfs(i);
    }
  }

  used.assign(2 * n, false);
  reverse(top_sort.begin(), top_sort.end());
  for (int v : top_sort) {
    if (!used[v]) {
      dfs_rev(v);
      sc++;
    }
  }

  for (int i = 0; i < n; i++) {
    if (comp[i] == comp[i + n]) {
      cout << "NO\n";
      return 0;
    }
  }

  cout << "YES\n";
  for (int i = 0; i < n; i++) {
    cout << (comp[i] > comp[i + n] ? place[i] : place[i + n]) << ' ';
  }

  return 0;
}
