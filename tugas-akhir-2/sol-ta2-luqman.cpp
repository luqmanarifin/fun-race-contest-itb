#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int dp[N][N];
int c[N];
vector<int> edge[N];

void dfs(int now, int bef) {
  for (auto it : edge[now]) {
    if (it == bef) continue;
    dfs(it, now);
    for (int i = 0; i < N; i++) {
      dp[now][i] += dp[it][i];
    }
  }
  dp[now][c[now]]++;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", c + i);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  dfs(1, 0);
  
  int q;
  scanf("%d", &q);
  while (q--) {
    int x, v;
    scanf("%d %d", &x, &v);
    printf("%d\n", dp[x][v]);
  }
  return 0;
}
