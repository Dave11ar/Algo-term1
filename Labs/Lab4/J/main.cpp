#include<bits/stdc++.h>

using namespace std;

string s, t, ans;
vector<vector<int>> dpPref, dpSuff;
int n, m;

void lcsPref(int s1, int s2, int t1, int t2) {
  dpPref[1][t1 - 1] = 0;
  //
  for (int j = 0; j < (int)dpPref[0].size(); j++) {
    dpPref[0][j] = 0;
  }
  //
  for (int i = s1; i <= s2; i++) {
    for (int j = t1; j <= t2; j++) {
      if (s[i] == t[j]) {
        dpPref[1][j] = dpPref[0][j - 1] + 1;
      } else {
        dpPref[1][j] = max(dpPref[0][j], dpPref[1][j - 1]);
      }
    }
    dpPref[0] = dpPref[1];
  }
}

void lcsSuff(int s1, int s2, int t1, int t2) {
  dpSuff[1][t2 + 1] = 0;
  //
  for (int j = 0; j < (int)dpSuff[0].size(); j++) {
    dpSuff[0][j] = 0;
  }
  //
  for (int i = s2; i >= s1; i--) {
    for (int j = t2; j >= t1; j--) {
      if (s[i] == t[j]) {
        dpSuff[1][j] = dpSuff[0][j + 1] + 1;
      } else {
        dpSuff[1][j] = max(dpSuff[0][j],
            dpSuff[1][j + 1]);
      }
    }
    dpSuff[0] = dpSuff[1];
  }
}

bool contains(int t1, int t2, char x) {
  for (int i = t1; i <= t2; i++) {
    if (t[i] == x) {
      return true;
    }
  }
  return false;
}

void hirschberg(int s1, int s2, int t1, int t2) {
  if (s1 == s2 || t1 > t2) {
    if (contains(t1, t2, s[s1])) {
      ans.push_back(s[s1]);
    }
    return;
  }

  int mid = (s1 + s2) / 2;

  lcsPref(s1, mid, t1, t2);
  lcsSuff(mid + 1, s2, t1, t2);

  pair<int, int> bestPart = {-1, -1};

  for (int j = t1 - 1; j <= t2; j++) {
    int cur = dpPref[1][j]
        + dpSuff[1][j + 1];

    if (cur > bestPart.first) {
      bestPart = { cur, j };
    }
  }


  hirschberg(s1, mid, t1, bestPart.second);
  hirschberg(mid + 1, s2, bestPart.second + 1, t2);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> s >> t;

  n = (int)s.length(); m = (int)t.length();
  s = "d" + s; t = "p" + t;

  dpPref.resize(2, vector<int>(m + 2));
  dpSuff.resize(2, vector<int>(m + 2));

  hirschberg(1, n, 1, m);

  for (int i = 0; i < (int)ans.length(); i++) {
    cout << ans[i];
  }

  return 0;
}
