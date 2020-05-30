#include <bits/stdc++.h>

using namespace std;

struct quad {
  int h_min, h_max;
  int w_min, w_max;

  quad() = default;
  quad(int h_min, int h_max, int w_min, int w_max) :
      h_min(h_min), h_max(h_max), w_min(w_min), w_max(w_max) {}
};

int n, m;
quad sparse[128][128][10][10];
quad table[128][128];

quad get_sparse(quad a, quad b) {
  quad c{max(a.h_min, b.h_min),
         min(a.h_max, b.h_max),
         max(a.w_min, b.w_min),
         min(a.w_max, b.w_max)};
  return c;
}

void build_sparse() {
  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      sparse[i][j][0][0] = table[i][j];
      for (int k2 = 1; j + (1 << (k2 - 1)) < m; k2++) {
        sparse[i][j][0][k2] = get_sparse(sparse[i][j][0][k2 - 1],
            sparse[i][j + (1 << (k2 - 1))][0][k2 - 1]);
      }
    }
  }

  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      for (int k1 = 1; i + (1 << (k1 - 1)) < n; k1++) {
        for (int k2 = 0; j + (1 << (k2 - 1)) < m; k2++) {
          sparse[i][j][k1][k2] = get_sparse(sparse[i][j][k1 - 1][k2],
              sparse[i + (1 << (k1 - 1))][j][k1 - 1][k2]);
        }
      }
    }
  }
}

int lg(int x) {
  if (x <= 1) return 0;
  return 1 + lg(x / 2);
}

long long get_res(int x1, int y1, int x2, int y2) {
  int k1 = lg(x2 - x1 + 1);
  int k2 = lg(y2 - y1 + 1);
  quad ans1 = sparse[x1][y1][k1][k2];
  quad ans2 = sparse[x2 - (1 << k1) + 1][y1][k1][k2];
  quad ans3 = sparse[x1][y2 - (1 << k2) + 1][k1][k2];
  quad ans4 = sparse[x2 - (1 << k1) + 1][y2 - (1 << k2) + 1][k1][k2];

  int h_min = max(max(ans1.h_min, ans2.h_min), max(ans3.h_min, ans4.h_min));
  int h_max = min(min(ans1.h_max, ans2.h_max), min(ans3.h_max, ans4.h_max));
  int w_min = max(max(ans1.w_min, ans2.w_min), max(ans3.w_min, ans4.w_min));
  int w_max = min(min(ans1.w_max, ans2.w_max), min(ans3.w_max, ans4.w_max));

  if (h_max < h_min || w_max < w_min) return 0;
  return 1ll * (h_max - h_min) * (w_max - w_min);
}

int MOD = 1e9 + 7;
void input() {
  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int h_min, h_max;
      int w_min, w_max;
      cin >> h_min >> w_min >> h_max >> w_max;

      table[i][j] = quad{min(h_min, h_max), max(h_min, h_max),
                         min(w_min, w_max), max(w_min, w_max)};
    }
  }
  build_sparse();

  int q;
  long long A, B;
  int v0, v1, v2, v3;
  cin >> q >> A >> B >> v0;

  v0 = (int)((A * v0 + B) % MOD);
  long long ans = 0;
  for (int i = 0; i < q; i++) {
    v1 = (int)((A * v0 + B) % MOD);
    v2 = (int)((A * v1 + B) % MOD);
    v3 = (int)((A * v2 + B) % MOD);
    ans += get_res(min(v0 % n, v2 % n), min(v1 % m, v3 % m),
        max(v0 % n, v2 % n), max(v1 % m, v3 % m));
    ans %= MOD;

    v0 = (int)((A * v3 + B) % MOD);
  }

  cout << ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  input();

  return 0;
}
