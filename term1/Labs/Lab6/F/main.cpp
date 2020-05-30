#include <bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  string s;
  for (int i = 0; i < 1000; i++) {
    s.push_back('b');
  }
  int k;
  cin >> k;

  cout << s << '\n';
  for (int i = 1; i < k; i++) {
    s[i] = char(int(s[i]) - 31);
    s[i - 1] = char(int(s[i - 1]) + 1);
    cout << s << '\n';
    s[i - 1] = 'b'; s[i] = 'b';
  }

  return 0;
}
