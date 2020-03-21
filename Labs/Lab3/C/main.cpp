#include<bits/stdc++.h>

using namespace std;

struct tree {
  int key;
  int dist;
  int push;

  tree* l;
  tree* r;
  tree* parent;

  tree(int key, int dist, int push, tree* l, tree* r, tree* parent):
    key(key), dist(dist), push(push), l(l), r(r), parent(parent) {}
};

vector<tree*> push;

tree* merge(tree* x, tree* y) {
  if (x == NULL) return y;
  if (y == NULL) return x;

  if (y->key < x->key) {
    swap(x, y);
  }

  x->r = merge(x->r, y);
  x->r->parent = x;

  if ((x->r ? x->r->dist : 0) > (x->l ? x->l->dist : 0)) {
    swap(x->l, x->r);
  }
  x->dist = (x->r ? x->r->dist : 0) + 1;
  return x;
}

void toTop(tree* t) {
  if (t->parent == NULL) {
    return;
  }

  if (t->key < t->parent->key) {
    swap(t->key, t->parent->key);
    swap(t->push, t->parent->push);
    swap(push[t->push], push[t->parent->push]);
    toTop(t->parent);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  tree* t = NULL;
  string type;
  int sc = 0;

  while (cin >> type) {
    if (type == "push") {
      int key;
      cin >> key;
      push.push_back(new tree(key, 1, sc, NULL, NULL, NULL));
      t = merge(t , push[int(push.size()) - 1]);
    } else if (type == "extract-min") {
      if (t == NULL) {
        cout << "*";
      } else {
        cout << t->key << ' ' << t->push + 1;
        if (t->l) t->l->parent = NULL;
        if (t->r) t->r->parent = NULL;
        t = merge(t->l, t->r);
      }
      cout << '\n';
      push.push_back(NULL);
    } else {
      int p, k;
      cin >> p >> k;
      push[p - 1]->key = k;
      toTop(push[p - 1]);
      push.push_back(NULL);
    }

    sc++;
  }

  return 0;
}
