#include <bits/stdc++.h>

using namespace std;

int t, n, m;

vector<set<int>> g;
vector<bool> color;
vector<int> used;

void paint(int v, bool clr) {
  used[v] = 1;
  color[v] = clr;

  for (int to : g[v]) {
    if (used[to] == 0) {
      paint(to, !clr);
    }
  }
}

void make_bi(int v) {
  used[v] = 1;

  vector<int> del;
  for (int to : g[v]) {
    if (used[to] == 0) {
      make_bi(to);
    } else {
      if (color[v] == color[to]) {
        del.push_back(to);
      }
    }
  }

  for (int to : del) {
    g[v].erase(to);
  }
}
int cyc = -1;
vector<int> ans;

void cycle(int v, int p) {
  used[v] = 1;

  for (int to : g[v]) {
    if (cyc == -2) return;
    if (used[to] == 0) {
      cycle(to, v);

      if (cyc != -1) {
        ans.push_back(v);
        if (cyc == v) {
          cyc = -2;
        }
        return;
      }
    } else if (used[to] == 1 && to != p) {
      cyc = to;
      ans.push_back(v);
      return;
    }
  }
  used[v] = 2;
}

void input() {
  cyc = -1;
  ans.clear();
  g.clear();
  color.clear();
  used.clear();
  cin >> n >> m;
  g.resize(n);
  color.resize(n);
  used.resize(n);

  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    l--;
    r--;

    g[l].insert(r);
    g[r].insert(l);
  }

  paint(0, true);

  used.assign(n, 0);
  make_bi(0);

  used.assign(n, 0);
  cycle(0, 0);

  if (!ans.empty()) {
    cout << ans.size() << '\n';
    for (int cur : ans) {
      cout << cur + 1 << ' ';
    }
  } else {
    if (ans.empty()) {
      used.assign(n, false);
      paint(0, false);

      used.assign(n, 0);
      make_bi(0);

      used.assign(n, 0);
      cycle(0, 0);

      if (!ans.empty()) {
        cout << ans.size() << '\n';
        for (int cur : ans) {
          cout << cur + 1 << ' ';
        }
      } else {
        cout << -1;
      }
    }
  }
  cout << '\n';
}



int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> t;
  for (int i = 0; i < t; i++) {
    input();
  }

  return 0;
}
