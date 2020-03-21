#include<bits/stdc++.h>

using namespace std;

struct node{
  long long x;
  long long cnt;

  node* l;
  node* r;
  node* p;

  node(long long x, long long cnt, node* l, node* r, node* p):
      x(x), cnt(cnt), l(l), r(r), p(p) {}
};

long long get(node* t) {
  return t ? t->cnt : 0;
}

node* zig(node*t) {
  if (t->x < t->p->x) {
    t->p->l = t->r;
    if (t->r) t->r->p = t->p;

    t->r = t->p;
    t->r->cnt = t->r->x + get(t->r->l) + get(t->r->r);
  } else {
    t->p->r = t->l;
    if (t->l) t->l->p = t->p;

    t->l = t->p;
    t->l->cnt = t->l->x + get(t->l->l) + get(t->l->r);
  }

  node* tmp = t->p->p;
  t->p->p = t;
  t->p = tmp;
  t->cnt = t->x + get(t->l) + get(t->r);

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

node* find(node* t, long long x) {
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

pair<node*, node*> split(node* t, long long x) {
  if (!t) return {t, t};
  t = find(t, x);

  if (t->x <= x) {
    node* r = t->r;
    t->r = nullptr;
    t->cnt = t->x + get(t->l) + get(t->r);

    if (r) r->p = nullptr;

    return {t, r};
  } else {
    node* l = t->l;
    t->l = nullptr;
    t->cnt = t->x + get(t->l) + get(t->r);

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
  a->cnt = a->x + get(a->l) + get(a->r);

  return a;
}

node* add(node* t, long long x) {
  if (!t) return new node(x, x, t, t, t);
  pair<node*, node*> z = split(t, x);

  if (z.first && z.first->x == x) {
    return merge(z.first, z.second);
  }

  node* new_node = new node(x, x + get(z.first) + get(z.second), z.first, z.second, nullptr);
  if (new_node->l) new_node->l->p = new_node;
  if (new_node->r) new_node->r->p = new_node;

  return new_node;
}

node* down(node* t, bool left) {
  if (left) {
    if (t->l) {
      return down(t->l, left);
    }
  } else {
    if (t->r) {
      return down(t->r, left);
    }
  }
  t = splay(t);
  return t;
}

node* next(node* t, long long x) {
  if (!t) return nullptr;
  t = find(t, x);

  if (t->x > x) return t;
  if (!t->r) return nullptr;
  return down(t->r, true);
}

node* prev(node* t, long long x) {
  if (!t) return nullptr;
  t = find(t, x);

  if (t->x < x) return t;
  if (!t->l) return nullptr;
  return down(t->l, false);
}

int main() {
  node* t = nullptr;
  int n;
  bool f = false;
  long long y = 0;
  cin >> n;

  for (int i = 0; i < n; i++) {
    char s;
    cin >> s;

    if (s == '+') {
      long long x;
      cin >> x;

      if (!f) {
        t = add(t, x);
      } else {
        t = add(t, (x + y) % 1000000000);
      }
      f = false;
    } else {
      f = true;
      y = 0;
      int l, r;
      long long sum = 0;
      cin >> l >> r;
      if (!t) {
        cout << 0 << '\n';
        continue;
      }
      t = find(t, l);
      if (t->x < l) {
        node* next_l = next(t, t->x);
        if (!next_l) {
          t = splay(t);
          cout << 0 << '\n';
          continue;
        }
        t = next_l;
      }
      sum += get(t->l);


      t = find(t, r);
      if (t->x > r) {
        node* prev_r = prev(t, t->x);
        if (!prev_r) {
          t = splay(t);
          cout << 0 << '\n';
          continue;
        }
        t = prev_r;
      }
      sum += get(t->r);
      y = t->cnt - sum;
      cout << y << '\n';
    }
  }

  return 0;
}
