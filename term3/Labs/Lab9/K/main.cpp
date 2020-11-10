#include <bits/stdc++.h>

#include <utility>

using namespace std;

typedef long long ll;
mt19937 rnd(time(NULL));

ll ans = 0;
int timer = 1;

struct treap {
  pair<int, ll> x;
  ll y;
  pair<int, ll> mn;
  treap *l;
  treap *r;
  ll psh = 0;

  treap(pair<int, ll> x, ll y, pair<int, ll> mn, treap *l, treap *r) :
      x(std::move(x)), y(y), mn(std::move(mn)), l(l), r(r) {}
};

void push(treap *T) {
  T->x.second += T->psh;
  T->mn.second += T->psh;

  T->psh = 0;
}

pair<int, ll> get_min(treap *e1) {
  if (e1->l == nullptr && e1->r == nullptr) {

  } else if (e1->l == nullptr) {
    e1->mn = min(e1->x, e1->r->mn);
  } else if (e1->r == nullptr) {
    e1->mn = min(e1->x, e1->l->mn);
  } else {
    e1->mn = min(e1->x, min(e1->l->mn, e1->r->mn));
  }
}

pair<int, ll> min(pair<int, ll> e1, pair<int, ll> e2) {
  return e1.second > e2.second ? e2 : e1;
}

treap *merge(treap *L, treap *R) {
  if (L == nullptr || R == nullptr) {
    return (R == nullptr ? L : R);
  }

  if (L == R) {
    return L;
  }

  push(L);
  push(R);

  if (L->y > R->y) {
    return new treap(L->x, L->y, min(L->x, R->x),
                     L->l, merge(L->r, R));
  } else {
    return new treap(R->x, R->y, min(R->x, L->x),
                     merge(L, R->l), R->r);
  }
}

treap *delete_min(treap *T) {
  if (T == nullptr) {
    return T;
  }
  push(T);

  if (T->x == T->mn) {
    return merge(T->l, T->r);
  }

  if (T->r == nullptr || T->mn == T->l->mn) {
    T->l = delete_min(T->l);
  }
  if (T->l == nullptr || T->mn == T->r->mn) {
    T->r = delete_min(T->r);
  }

  get_min(T);
  return T;
}

pair<int, ll> extract_min(treap *T) {
  push(T);
  return T->mn;
}

int n, m;
vector<int> parent, siz, used;
vector<bool> got;
vector<vector<pair<int, ll>>> g_rev;
vector<treap*> t;
void init() {
  got[0] = true;

  for (int i = 0; i < n; i++) {
    parent[i] = i;
    siz[i] = 1;

    sort(g_rev[i].begin(), g_rev[i].end());

    t[i] = nullptr;
    for (size_t j = 0; j < g_rev[i].size(); j++) {
      t[i] = merge(t[i], new treap(g_rev[i][j], rnd(), g_rev[i][j], nullptr, nullptr));
    }
  }
}

int find_set(int v) {
  if (v == parent[v]) {
    return v;
  }

  return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
  a = find_set(a);
  b = find_set(b);

  if (siz[a] < siz[b]) {
    swap(a, b);
  }

  parent[b] = a;
  siz[a] += siz[b];
}

void input() {
  cin >> n >> m;
  t.resize(n);
  parent.resize(n);
  siz.resize(n);
  g_rev.resize(n);
  used.resize(n);
  got.resize(n);

  for (int i = 0; i < m; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    a--; b--;

    used[i] = 0;
    g_rev[b].emplace_back(a, w);
  }
}

void zero() {
  for (int i = 0; i < n; i++) {
    ll mn = INT64_MAX;
    for (pair<int, ll> &to : g_rev[i]) {
      if (i != to.first) {
        mn = min(mn, to.second);
      }
    }


    if (mn != INT64_MAX) {
      ans += mn;

      for (pair<int, ll> &to : g_rev[i]) {
        to.second -= mn;
      }
    }
  }
}

bool cycle_alert = false;
int cycle_root;


void dfs(int v) {
  used[v] = timer;

  if (t[find_set(v)] == nullptr) {
    cout << "NO";
    exit(0);
  }
  pair<int, ll> edge = extract_min(t[find_set(v)]);
  while (find_set(edge.first) == find_set(v)) {
    if (t[v] == nullptr) {
      cout << "NO";
      exit(0);
    }
    t[find_set(v)] = delete_min(t[find_set(v)]);
    edge = extract_min(t[find_set(v)]);
  }


  if (used[edge.first] != timer) {
    if (!got[edge.first]) {
      dfs(edge.first);
      if (got[edge.first]) {
        got[v] = true;
      }
    } else {
      got[v] = true;
    }
  } else {
    cycle_alert = true;
    cycle_root = edge.first;


    int le = find_set(edge.first);
    int re = find_set(v);
    union_sets(edge.first, v);
    t[find_set(v)] = merge(t[le], t[re]);
    return;
  }

  if (cycle_alert) {
    int le = find_set(edge.first);
    int re = find_set(v);
    union_sets(edge.first, v);
    t[find_set(v)] = merge(t[le], t[re]);

    if (cycle_root == v) {
      cycle_alert = false;

      pair<int, ll> cur = extract_min(t[find_set(edge.first)]);

      while (find_set(cur.first) == find_set(v)) {
        if (t[find_set(v)] == nullptr) {
          cout << "NO";
          exit(0);
        }

        t[find_set(v)] = delete_min(t[find_set(v)]);
        cur = extract_min(t[find_set(v)]);
      }

      ans += cur.second;
    }
  }
}

void solution() {
  for (int i = 0; i < n; i++) {
    if (!got[i]) {
      dfs(i);
      timer++;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();
  zero();
  init();
  solution();

  cout << "YES\n" << ans;

  return 0;
}
