#include<bits/stdc++.h>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("lis.in", "r", stdin);
  freopen("lis.out", "w", stdout);

  int n;
  cin >> n;
  vector<int> vec(n), dp(n + 1, 1e9 + 1), last(n + 1), pos(n + 1);
  dp[0] = -(1e9 + 1);
  pos[0] = -1;

  for (int i = 0; i < n; i++) {
    cin >> vec[i];
  }

  for (int i = 0; i < n; i++) {
    int l = lower_bound(dp.begin(), dp.end(), vec[i]) - dp.begin();

    dp[l] = vec[i];
    pos[l] = i;
    last[i] = pos[l - 1];
  }

  int lst = -1;
  for (int i = n; i >= 0; i--) {
    if (dp[i] != 1e9 + 1) {
      lst = i;
      break;
    }
  }

  cout << lst << '\n';
  int p = pos[lst];
  vector<int> ans;

  while (p != -1) {
    ans.push_back(vec[p]);
    p = last[p];
  }

  reverse(ans.begin(), ans.end());

  for (int i = 0; i < (int)ans.size(); i++) {
    cout << ans[i] << ' ';
  }

  return 0;
}
