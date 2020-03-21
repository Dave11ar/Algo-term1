#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  vector<int> a(n + 1);

  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  for (int i = n; i > 1; i--) {
    if (a[i] < a[i / 2]) {
      cout << "NO";
      return 0;
    }
  }

  cout << "YES";
  return 0;
}
