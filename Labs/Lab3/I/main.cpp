#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, m;
  cin >> n >> m;

  if (m <= 16) {
    for (int i = 0; i < m; i++) {
      cout << "0 1 1" << '\n';
    }

    return 0;
  }

  int cnt = 0;
  int k = (int)sqrt(m);

  for (int i = 1; i <= k; i++) {
    cout << "1 " << k + 1 << " " << i  << '\n';
    cnt++;
  }

  cout << "1 " << k + 2 << " " << k + 1  << '\n';
  cnt++;

  for (int i = k + 1; i <= 2 * k; i++) {
    for (int j = 1; j < k; j += 2) {
      cout << "0 " << j << " " << j + 1 << '\n';
      cnt++;
      if (cnt == m) {
        return 0;
      }
    }

    cout << "1 " << i + 2 << " " << i + 1  << '\n';
    cnt++;
    if (cnt == m) {
      return 0;
    }
  }

  for ( ; cnt < m; cnt++) {
    cout << "0 1 1" << '\n';
  }

  return 0;
}
