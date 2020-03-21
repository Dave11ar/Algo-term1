#include<bits/stdc++.h>

using namespace std;

struct node {
  int x;
  int y;

  node* l;
  node* r;
  node* p;
  node(int x, int y, node* l, node* r, node* p):
      x(x), y(y), l(l), r(r), p(p) {}
};

node* merge(node* a, node* b) {
  if (!a) return b;
  if (!b) return a;

  if (a->y < b->y) {
    a->r = merge(a->r, b);
    a->r->p = a;
    return a;
  } else {
    b->l = merge(a, b->l);
    b->l->p = b;
    return b;
  }
}

vector<node*> ans;
vector<int> pos;
void dfs(node* t) {
  if (!t) return;
  ans[pos[t->x]] = t;

  dfs(t->l);
  dfs(t->r);
}

int main() {
  int n;
  cin >> n;

  ans.resize(3000000);
  pos.resize(3000000);
  vector<pair<int, int>> buff(n);
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    x += 1000010;
    pos[x] = i;
    buff[i] = {x, y};
  }
  sort(buff.begin(), buff.end());
  queue<node*> nodes;

  for (auto & i : buff) {
    nodes.push(new node(i.first, i.second, nullptr, nullptr, nullptr));
  }

  while (nodes.size() > 1) {
    node* z1 = nodes.front();
    nodes.pop();
    node* z2 = nodes.front();
    nodes.pop();

    if (nodes.empty()) {
      if (z1->x > z2->x) {
        nodes.push(merge(z2, z1));
      } else {
        nodes.push(merge(z1, z2));
      }
      continue;
    }


    if (z1->x > z2->x) {
      nodes.push(z1);
      z1 = nodes.front();
      nodes.pop();
      nodes.push(merge(z2, z1));
    } else {
      nodes.push(merge(z1, z2));
    }
  }

  dfs(nodes.front());

  cout << "YES" << '\n';
  for (int i = 0; i < n; i++) {
    if (ans[i]->p) {
      cout << pos[ans[i]->p->x] + 1;
    } else {
      cout << 0;
    }
    cout << ' ';

    if (ans[i]->l) {
      cout << pos[ans[i]->l->x] + 1;
    } else {
      cout << 0;
    }
    cout << ' ';

    if (ans[i]->r) {
      cout << pos[ans[i]->r->x] + 1;
    } else {
      cout << 0;
    }
    cout << '\n';
  }

  return 0;
}
