#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

int par[N], c[N];
vector<int> edge[N];

void dfs(int now, int bef) {
  par[now] = bef;
  for (auto it : edge[now]) {
    if (it == bef) continue;
    dfs(it, now);
  }
}

int find(int now, int col) {
  int ret = (c[now] == col)
  for (auto it : edge[now]) {
    if (it == par[now]) continue;
    ret += find(it, col);
  }
  return ret'
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
    int x, col;
    scanf("%d %d", &x, &col);
    printf("%d\n", find(x, par[x], col));
  }
  return 0;
}