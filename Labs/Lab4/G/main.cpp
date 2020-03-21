#include <bits/stdc++.h>

using namespace std;

struct p {
  int a, b, c;
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  freopen("meetings.in", "r", stdin);
  freopen("meetings.out", "w", stdout);

  int n, k;
  cin >> n >> k;
  vector<p> vec(n);
  vector<int> mood(1 << n, k);
  vector<bool> dp(1 << n);
  dp[0] = true;

  for (int i = 0; i < n; i++) {
    cin >> vec[i].a >> vec[i].b >> vec[i].c;
  }

  for (int i = 0; i < (1 << n); i++) {
    int num = 0, tmp = i;

    while (tmp != 0) {
      mood[i] += vec[num].c * (tmp % 2);
      num++;
      tmp /= 2;
    }
  }

  for (int i = 0; i < n; i++) {
    if (vec[i].a <= k && k <= vec[i].b) {
      dp[1 << i] = true;
    }
  }

  for (int mask = 1; mask < (1 << n); mask++) {
    for (int j = 0; j < n; j++) {
      if ((mask & (1 << j)) > 0) {
        continue;
      }

      if (dp[mask] && vec[j].a <= mood[mask] && mood[mask] <= vec[j].b) {
        dp[mask ^ (1 << j)] = true;
      }
    }
  }

  int mx = -1;
  int num = -1;
  for (int i = 0; i < (1 << n); i++) {
    if (dp[i] != true) {
      continue;
    }

    int tmp = i;
    int p = 0;

    while (tmp > 0) {
      if (tmp % 2 == 1) {
        p++;
      }
      tmp /= 2;
    }

    if (p > mx) {
      mx = p;
      num = i;
    }
  }

  vector<int> ans;
  mx = num;
  while (mx != 0) {
    for (int i = 0; i < n; i++) {
      if ((mx & (1 << i)) > 0 && dp[mx ^ (1 << i)]
          && vec[i].a <= mood[mx ^ (1 << i)]
          && mood[mx ^ (1 << i)] <= vec[i].b) {
        ans.push_back(i + 1);
        mx ^= (1 << i);
        break;
      }
    }
  }

  cout << (int) ans.size() << '\n';
  reverse(ans.begin(), ans.end());
  for (int i = 0; i < (int) ans.size(); i++) {
    cout << ans[i] << ' ';
  }

  return 0;
}
