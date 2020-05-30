#include<bits/stdc++.h>

using namespace std;

struct node{
  int x;
  int cnt;

  node* l;
  node* r;
  node* p;

  node(int x, int cnt, node* l, node* r, node* p):
      x(x), cnt(cnt), l(l), r(r), p(p) {}
};

int get(node* t) {
  return t ? t->cnt : 0;
}

node* zig(node*t) {
  if (t->x < t->p->x) {
    t->p->l = t->r;
    if (t->r) t->r->p = t->p;

    t->r = t->p;
    t->r->cnt = 1 + get(t->r->l) + get(t->r->r);
  } else {
    t->p->r = t->l;
    if (t->l) t->l->p = t->p;

    t->l = t->p;
    t->l->cnt = 1 + get(t->l->l) + get(t->l->r);
  }

  node* tmp = t->p->p;
  t->p->p = t;
  t->p = tmp;
  t->cnt = 1 + get(t->l) + get(t->r);

  return t;
}

node* splay(node* t) {
  if (!t || !t->p) return t;
  if (!t->p->p) return zig(t);

  if ((t->x < t->p->x && t->p->x < t->p->p->x) ||
      (t->x > t->p->x && t->p->x > t->p->p->x)) {
    t->p = zig(t->p);
    t = zig(t);
  } else {
    t = zig(t);
    t = zig(t);
  }

  return splay(t);
}

node* find(node* t, int x) {
  if (!t) return t;

  if (t->x == x) return splay(t);

  if (t->x > x) {
    if (!t->l) return splay(t);
    return find(t->l, x);
  } else {
    if (!t->r) return splay(t);
    return find(t->r, x);
  }
}

pair<node*, node*> split(node* t, int x) {
  if (!t) return {t, t};
  t = find(t, x);

  if (t->x <= x) {
    node* r = t->r;
    t->r = nullptr;
    t->cnt = 1 + get(t->l) + get(t->r);

    if (r) r->p = nullptr;

    return {t, r};
  } else {
    node* l = t->l;
    t->l = nullptr;
    t->cnt = 1 + get(t->l) + get(t->r);

    if (l) l->p = nullptr;

    return {l, t};
  }
}

node* merge(node* a, node* b) {
  if (!a) return b;
  if (!b) return a;

  a = find(a, INT_MAX);
  a->r = b;
  b->p = a;
  a->cnt = 1 + get(a->l) + get(a->r);

  return a;
}

node* add(node* t, int x) {
  if (!t) return new node(x, 1, t, t, t);
  pair<node*, node*> z = split(t, x);

  if (z.first && z.first->x == x) {
    return merge(z.first, z.second);
  }

  node* new_node = new node(x, 1 + get(z.first) + get(z.second), z.first, z.second, nullptr);
  if (new_node->l) new_node->l->p = new_node;
  if (new_node->r) new_node->r->p = new_node;

  return new_node;
}

node* remove(node* t, int x) {
  if (!t) return t;
  t = find(t, x);
  if (t->x != x) return t;

  if (t->l) t->l->p = nullptr;
  if (t->r) t->r->p = nullptr;

  return merge(t->l, t->r);
}

node* k_max(node* t, int x) {
  int cur = 1 + get(t->l);
  if (cur == x) {
    return splay(t);
  }

  if (cur < x) {
    return k_max(t->r, x - cur);
  } else {
    return k_max(t->l, x);
  }
}

int main() {
  int num = 0;
  string s;
  int x;
  node* t = nullptr;

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> s >> x;

    if (s == "+1" || s == "1") {
      t = add(t, x);
      num++;
    } else if (s == "-1") {
      t = remove(t, x);
      num--;
    } else {
      t = k_max(t, num - x + 1);

      cout << t->x << '\n';
    }
  }

  return 0;
}
