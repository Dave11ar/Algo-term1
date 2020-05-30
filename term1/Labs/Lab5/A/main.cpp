#include<bits/stdc++.h>

using namespace std;

struct node{
  int x;

  node* l;
  node* r;
  node* p;

  node(int x, node* l, node* r, node* p):
      x(x), l(l), r(r), p(p) {}
};

node* zig(node*t) {
  if (t->x < t->p->x) {
    t->p->l = t->r;
    if (t->r) t->r->p = t->p;

    t->r = t->p;
  } else {
    t->p->r = t->l;
    if (t->l) t->l->p = t->p;

    t->l = t->p;
  }

  node* tmp = t->p->p;
  t->p->p = t;
  t->p = tmp;

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

    if (r) r->p = nullptr;

    return {t, r};
  } else {
    node* l = t->l;
    t->l = nullptr;

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

  return a;
}

node* add(node* t, int x) {
  if (!t) return new node(x, t, t, t);
  pair<node*, node*> z = split(t, x);

  if (z.first && z.first->x == x) {
    return merge(z.first, z.second);
  }

  node* new_node = new node(x, z.first, z.second, nullptr);
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
//
int down(node* t, bool left) {
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
  return t->x;
}

int next(node* t, int x) {
  if (!t) return INT_MIN;
  t = find(t, x);

  if (t->x > x) return t->x;
  if (!t->r) return INT_MIN;
  return down(t->r, true);
}

int prev(node* t, int x) {
  if (!t) return INT_MIN;
  t = find(t, x);

  if (t->x < x) return t->x;
  if (!t->l) return INT_MIN;
  return down(t->l, false);
}


int main() {
  string s;
  node* t = nullptr;

  while (cin >> s) {
    int x;
    cin >> x;

    if (s == "insert") {
      t = add(t, x);
    } else if (s == "delete") {
      t = remove(t, x);
    } else if (s == "exists") {
      t = find(t, x);
      if (t && t->x == x) {
        cout << "true";
      } else {
        cout << "false";
      }
      cout << '\n';
    } else if (s == "next") {
      int ans = next(t, x);
      t = splay(t);
      if (ans != INT_MIN) {
        cout << ans;
      } else {
        cout << "none";
      }
      cout << '\n';
    } else if (s == "prev") {
      int ans = prev(t, x);
      t = splay(t);
      if (ans != INT_MIN) {
        cout << ans;
      } else {
        cout << "none";
      }
      cout << '\n';
    }
  }

  return 0;
}
