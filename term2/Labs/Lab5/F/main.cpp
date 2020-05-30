#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(time(NULL));

struct node {
  int x;
  int y;
  int cnt;

  node* l;
  node* r;

  node(int x, int y, int cnt, node* l, node* r):
      x(x), y(y), cnt(cnt), l(l), r(r) {}
};

int get(node* t) {
  return t ? t->cnt : 0;
}

int get_num(node* t) {
  return 1 + get(t->l);
}

int fix(node* t) {
  return 1 + get(t->l) + get(t->r);
}

pair<node*, node*> split(node* t, int cnt) {
  if (!t) return {t, t};

  pair<node*, node*> z;
  if (get_num(t) < cnt) {
    z = split(t->r, cnt - get_num(t));
    t->r = z.first;
    t->cnt = fix(t);

    return {t, z.second};
  } else {
    z = split(t->l, cnt);
    t->l = z.second;
    t->cnt = fix(t);

    return {z.first, t};
  }
}

node* merge(node* a, node* b) {
  if (!a) return b;
  if (!b) return a;

  if (a->y > b->y) {
    a->r = merge(a->r, b);
    a->cnt = fix(a);

    return a;
  } else {
    b->l = merge(a, b->l);
    b->cnt = fix(b);

    return b;
  }
}

node* insert(node* t, int x, int y, int cnt) {
  if (!t) return new node(x, y, 1, nullptr, nullptr);

  if (t->y < y) {
    pair<node*, node*> z = split(t, cnt);
    t = new node(x, y, 0, z.first, z.second);
    t->cnt = fix(t);

    return t;
  }

  if (get_num(t) < cnt) {
    t->r = insert(t->r, x, y, cnt - get_num(t));
  } else {
    t->l = insert(t->l, x, y, cnt);
  }
  t->cnt = fix(t);

  return t;
}

node* remove(node* t, int cnt) {
  if (get_num(t) == cnt) {
    return merge(t->l, t->r);
  }

  if (get_num(t) < cnt) {
    t->r = remove(t->r, cnt - get_num(t));
  } else {
    t->l = remove(t->l, cnt);
  }
  t->cnt = fix(t);

  return t;
}

int find(node* t, int cnt) {
  if (get_num(t) == cnt) {
    return t->x;
  }

  if (get_num(t) < cnt) {
    return find(t->r, cnt - get_num(t));
  } else {
    return find(t->l, cnt);
  }
}

node* modify(node* t, int x, int cnt) {
  if (get_num(t) == cnt) {
    t->x = x;
    return t;
  }

  if (get_num(t) < cnt) {
    t->r = modify(t->r, x, cnt - get_num(t));
  } else {
    t->l = modify(t->l, x, cnt);
  }

  return t;
}

vector<int> p, dsu_max, siz;

int find_dsu(int a) {
  if (p[a] == a) {
    return a;
  }
  return p[a] = find_dsu(p[a]);
}

void union_set(int a, int b) {
  a = find_dsu(a);
  b = find_dsu(b);

  if (a == b) return;
  if (siz[a] < siz[b]) swap(a, b);

  siz[a] += siz[b];
  dsu_max[a] = max(dsu_max[a], dsu_max[b]);
  p[b] = a;
}

int main() {
  node* t = nullptr;
  int n, m;
  cin >> n >> m;

  p.resize(n + m + 1);
  dsu_max.resize(n + m + 1);
  siz.resize(n + m + 1);
  for (int i = 1; i <= n + m; i++) {
    p[i] = i;
    siz[i] = 1;
    dsu_max[i] = i;

    t = insert(t, 0, rnd(), i);
  }

  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;

    if (find(t, x) == 0) {
      t = modify(t, i, x);
      if (x != 1 && find(t, x - 1) != 0) {
        union_set(x - 1, x);
      }
      if (x != n + m && find(t, x + 1) != 0) {
        union_set(x, x + 1);
      }
    } else {
      int next_free = dsu_max[find_dsu(x)] + 1;

      union_set(x, next_free);
      if (next_free != n + m && find(t, next_free + 1) != 0) {
        union_set(next_free, next_free + 1);
      }

      t = remove(t, next_free);
      t = insert(t, i, rnd(), x);
    }
  }
  int max_elem = 1;
  for (int i = 1; i <= n + m; i++) {
    int cur = find(t, i);
    if (cur != 0) {
      max_elem = i;
    }
  }

  cout << max_elem << '\n';
  for (int i = 1; i <= max_elem; i++) {
    cout << find(t, i) << ' ';
  }

  return 0;
}
