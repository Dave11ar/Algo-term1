#include <bits/stdc++.h>

using namespace std;

int n;
vector<pair<int, int>> wind_y;
vector<pair<int, int>> wind_open, wind_close;
vector<int> y;
void input() {
  cin >> n;

  for (int i = 0; i < n; i++) {
    int x1, x2, y1, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    wind_y.emplace_back(y1, y2);
    wind_open.emplace_back(x1, i);
    wind_close.emplace_back(x2, i);
    y.push_back(y1);
    y.push_back(y2);
  }
}
vector<pair<int, int>> tree;
vector<int> modif;

void push(int v, int l, int r) {
  tree[v].first += modif[v];

  if (l < r) {
    modif[v * 2] += modif[v];
    modif[v * 2 + 1] += modif[v];
  }
  modif[v] = 0;
}

void tree_modify(int v, int l, int r, int dl, int dr, int x) {
  push(v, l, r);
  if (dl > dr) return;

  int mid = (l + r) / 2;

  if (l == dl && r == dr) {
    modif[v] += x;
    push(v, l, r);
    if (l != r) {
      push(v * 2, l, mid);
      push(v * 2 + 1, mid + 1, r);
      int left1 = tree[v * 2].first;
      int right1 = tree[v * 2 + 1].first;

      tree[v].second = (left1 > right1 ? tree[v * 2].second : tree[v * 2 + 1].second);
      tree[v].first = max(left1, right1);
    }
    return;
  }


  tree_modify(v * 2, l, mid, dl, min(dr, mid), x);
  tree_modify(v * 2 + 1, mid + 1, r, max(dl, mid + 1), dr, x);

  int left = tree[v * 2].first;
  int right = tree[v * 2 + 1].first;

  tree[v].second = (left > right ? tree[v * 2].second : tree[v * 2 + 1].second);
  tree[v].first = max(left, right);
}

void bruh_init(int v, int l, int r) {
  if (l == r) {
    tree[v].second = l;
    return;
  }

  int mid = (l + r) / 2;
  bruh_init(v * 2, l, mid);
  bruh_init(v * 2 + 1, mid + 1, r);
  tree[v].second = tree[v * 2].second;
}

int tree_n = 0;
map<int, int> sq_tree;
vector<int> sq_coord;
void sq() {
  sort(y.begin(), y.end());

  for (int cur : y) {
    if (!sq_tree.count(cur)) {
      sq_tree[cur] = tree_n++;
      sq_coord.push_back(cur);
    }
  }
}

int mx = 0;
pair<int, int> ans = {0, 0};

void scanline() {
  sq();
  tree.resize(4 * tree_n);
  modif.resize(4 * tree_n);
  bruh_init(1, 0 , tree_n - 1);

  sort(wind_open.begin(), wind_open.end());
  sort(wind_close.begin(), wind_close.end());

  int i = 0, j = 0;

  while (i < n || j < n) {
    while (i < n && (wind_open[i].first <= wind_close[j].first || j == n)) {
      pair<int, int> borders = wind_y[wind_open[i].second];
      tree_modify(1, 0, tree_n - 1, sq_tree[borders.first], sq_tree[borders.second], 1);
      push(1, 0, tree_n - 1);
      if (tree[1].first > mx) {
        mx = tree[1].first;
        ans = {wind_open[i].first, sq_coord[tree[1].second]};
      }
      i++;
    }

    while (j < n && (wind_close[j].first < wind_open[i].first || i == n)) {
      pair<int, int> borders = wind_y[wind_close[j].second];
      tree_modify(1, 0, tree_n - 1, sq_tree[borders.first], sq_tree[borders.second], -1);
      j++;
    }
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  scanline();

  cout << mx << '\n' << ans.first << ' ' << ans.second;
  return 0;
}
