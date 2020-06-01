#include <bits/stdc++.h>

using namespace std;

int sq;
int n, m;
struct req_node {
  int l, r;
  int id;

  req_node(int l, int r, int id) :
      l(l), r(r), id(id) {}
};
vector<req_node> req;
vector<int> vec;
vector<long long> ans_req;
int seg[1000010];

void input() {
  cin >> n >> m;
  sq = (int)(sqrt((double)n));
  vec.resize(n);
  ans_req.resize(m);

  for (int i = 0; i < n; i++) {
    cin >> vec[i];
    seg[vec[i]] = 0;
  }
  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    req.emplace_back(l - 1, r, i);
  }
}

long long ans;

void add(int j) {
  ans += vec[j] * (2ll * seg[vec[j]] + 1);
}

void sub(int j) {
  ans -= vec[j] * (2ll * seg[vec[j]] - 1);
}
void solution() {
  sort(req.begin(), req.end(), [](req_node const &a, req_node const &b) {
    if (a.l / sq != b.l /sq) {
      return a.l < b.l;
    }
    return a.r < b.r;
  });

  int l = 0;
  int r = 1;
  seg[vec[0]]++;
  ans = vec[0];

  for (int i = 0; i < m; i++) {
    while (r > req[i].r) {
      sub(--r);
      seg[vec[r]]--;
    }
    while (r < req[i].r) {
      add(r);
      seg[vec[r++]]++;
    }
    while (l < req[i].l) {
      sub(l);
      seg[vec[l++]]--;
    }
    while (l > req[i].l) {
      add(--l);
      seg[vec[l]]++;
    }

    ans_req[req[i].id] = ans;
  }
}

void output() {
  for (int i = 0; i < m; i++) {
    cout << ans_req[i] << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  solution();
  output();

  return 0;
}
