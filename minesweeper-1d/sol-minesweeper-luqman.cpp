#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;
const int mod = 1e9 + 7;

long long dp[N][5];
char s[N];

void clear(int i) {
  if (s[i] == '0') {
    dp[i][1] = dp[i][2] = dp[i][3] = dp[i][4] = 0;
  } else if (s[i] == '1') {
    dp[i][0] = dp[i][3] = dp[i][4] = 0;
  } else if (s[i] == '2') {
    dp[i][0] = dp[i][1] = dp[i][2] = dp[i][4] = 0;
  } else if (s[i] == '*') {
    dp[i][0] = dp[i][1] = dp[i][2] = dp[i][3] = 0;
  }
}

int main() {
  scanf("%s", s);
  int n = strlen(s);
  dp[0][0] = dp[0][2] = dp[0][4] = 1;
  clear(0);
  for (int i = 1; i < n; i++) {
    dp[i][0] += dp[i-1][0];
    dp[i][0] += dp[i-1][1];
    dp[i][1] += dp[i-1][4];
    dp[i][2] += dp[i-1][0];
    dp[i][2] += dp[i-1][1];
    dp[i][3] += dp[i-1][4];
    dp[i][4] += dp[i-1][2];
    dp[i][4] += dp[i-1][3];
    dp[i][4] += dp[i-1][4];
    for (int j = 0; j < 5; j++) dp[i][j] %= mod;
    clear(i);
  }
  long long ans = (dp[n-1][0] + dp[n-1][1] + dp[n-1][4]) % mod;
  cout << ans << endl;
  return 0;
}
