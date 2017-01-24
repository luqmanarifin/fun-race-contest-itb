#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

int bit[N];

void update(int i, int v) {
  for (; i < N; i |= i + 1) bit[i] = max(bit[i], v);
}

int find(int i) {
  int ret = 0;
  for (; i >= 0; i = (i & (i + 1)) - 1) ret = max(ret, bit[i]);
  return ret;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int v;
    scanf("%d", &v);
    update(i, v);
  }
  int q;
  scanf("%d", &q);
  while (q--) {
    int t, x, v;
    scanf("%d", &t);
    if (t == 1) {
      scanf("%d %d", &x, &v);
      update(x, v);
    } else {
      scanf("%d", &x);
      printf("%d\n", find(x));
    }
  }
  return 0;
}
