#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 999999937;

vector<vector<ll>> matrix = {
    {1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1},
    {1, 1, 0, 1, 0},
    {1, 1, 0, 1, 0}
};

vector<vector<ll>> multiplyMatrix(5, vector<ll>(5));

void multiply(vector<vector<ll>> firstMatrix, vector<vector<ll>> secondMatrix) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      multiplyMatrix[i][j] = 0;

      for (int r = 0; r < 5; r++) {
        multiplyMatrix[i][j] = (multiplyMatrix[i][j] + firstMatrix[i][r]
            * secondMatrix[r][j]) % MOD;
      }
    }
  }
}

vector<vector<ll>> binpow(ll n, vector<vector<ll>> curMatrix) {
  if (n == 1) {
    return matrix;
  } else if (n % 2 == 1) {
    vector<vector<ll>> binMatrix = binpow(n - 1, curMatrix);
    multiply(binMatrix, matrix);
  } else {
    vector<vector<ll>> binMatrix = binpow(n / 2, curMatrix);
    multiply(binMatrix, binMatrix);
  }

  return multiplyMatrix;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("sequences.in", "r", stdin);
  freopen("sequences.out", "w", stdout);

  ll n;
  cin >> n;

  while (n != 0) {
    if (n == 1) {
      cout << 5 << '\n';
    } else if (n == 2) {
      cout << 21 << '\n';
    } else {
      vector<vector<ll>> res = binpow(n - 1, matrix);

      ll ans = 0;
      for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
          ans += res[i][j];
          ans %= MOD;
        }
      }

      cout << ans << '\n';
    }
    cin >> n;
  }

  return 0;
}
