#include <bits/stdc++.h>
#define ll long long

using namespace std;

int n = 1 << 24;
int m, q;

uint32_t a, b;
uint32_t cur = 0;
uint32_t nextRand() {
  cur = cur * a + b;
  return cur >> 8;
}

vector<ll> pref(n + 1, 0);

void seg_add(int l, int r, ll x) {
  pref[l] += x;
  pref[r + 1] -= x;
}

void build_pref() {
  for (int i = 1; i < n; i++) {
    pref[i] += pref[i - 1];
  }
  for (int i = 1; i < n; i++) {
    pref[i] += pref[i - 1];
  }
}

uint32_t seg_sum(int l, int r) {
  if (l == 0) return (uint32_t)pref[r];
  return (uint32_t)(pref[r] - pref[l - 1]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> m >> q >> a >> b;

  for (int i = 0; i < m; i++) {
    uint32_t add = nextRand();
    uint32_t l = nextRand();
    uint32_t r = nextRand();
    if (l > r) swap(l, r);

    seg_add(l, r, add);
  }
  build_pref();
  uint32_t ans = 0;

  for (int i = 0; i < q; i++) {
    uint32_t l = nextRand();
    uint32_t r = nextRand();
    if (l > r) swap(l, r);

    ans += seg_sum(l, r);
  }

  cout << ans;

  return 0;
}
