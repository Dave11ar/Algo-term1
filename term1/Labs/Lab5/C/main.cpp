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
  if (get_num(t) <= cnt) {
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

  if (a->y <= b->y) {
    a->r = merge(a->r, b);
    a->cnt = fix(a);

    return a;
  } else {
    b->l = merge(a, b->l);
    b->cnt = fix(b);

    return b;
  }
}

int find(node* t, int cnt) {
  if (get_num(t) == cnt) return t->x;

  if (get_num(t) < cnt) {
    return find(t->r, cnt - get_num(t));
  } else {
    return find(t->l, cnt);
  }
}

node* insert(node* t, int x, int y) {
  if (!t) return new node(x, y, 1, nullptr, nullptr);

  if (t->y < y) {
    pair<node*, node*> z = split(t, x);
    t = new node(x, y, 0, z.first, z.second);
    t->cnt = fix(t);

    return t;
  }
  
  if (t->x < x) {
    t->r = insert(t->r, x, y);
  } else {
    t->l = insert(t->l, x, y);
  }
  t->cnt = fix(t);

  return t;
}

int main() {
  node* t = nullptr;
  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    t = insert(t, i, rnd());
  }

  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;

    pair<node*, node*> z1 = split(t, r);
    pair<node*, node*> z2 = split(z1.first, l - 1);

    t = merge(z2.second, z2.first);
    t = merge(t, z1.second);
  }

  for (int i = 1; i <= n; i++) {
    cout << find(t, i) << ' ';
  }

  return 0;
}
