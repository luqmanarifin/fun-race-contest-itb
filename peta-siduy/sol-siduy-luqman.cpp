#include <bits/stdc++.h>

using namespace std;

const int N = 3005;
const int inf = 1e9;

char s[N][N];
int n, m, dp[N][N];

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool valid(int i, int j) {
  return 0 <= i && i < n && 0 <= j && j < m;
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++) scanf("%s", s[i]);
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) dp[i][j] = inf;
  queue<pair<int, int>> q;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (s[i][j] == 'S') {
        q.emplace(i, j);
        dp[i][j] = 0;
      }
    }
  }
  while (!q.empty()) {
    int x, y;
    tie(x, y) = q.front();
    q.pop();
    if (s[x][y] == 'F') {
      cout << dp[x][y] << endl;
      return 0;
    }
    for (int i = 0; i < 4; i++) {
      int tx = x + dx[i];
      int ty = y + dy[i];
      if (!valid(tx, ty)) continue;
      if (s[tx][ty] == '*') continue;
      if (dp[x][y] + 1 < dp[tx][ty]) {
        dp[tx][ty] = dp[x][y] + 1;
        q.emplace(tx, ty);
      }
    }
  }
  puts("-1");
  return 0;
}
