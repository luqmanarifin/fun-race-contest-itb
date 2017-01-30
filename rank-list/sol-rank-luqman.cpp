#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;

pair<int, int> p[N];
int ans[N];

int main() {
  int n, q;
  scanf("%d %d", &n, &q);
  for (int i = 0; i < n; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    p[i] = {a, -b};
  }
  sort(p, p + n);
  reverse(p, p + n);
  //for (int i = 0; i < n; i++) printf("%d %d\n", p[i].first, -p[i].second);
  for (int i = 0; i < n; i++) {
    int j = i;
    while (j + 1 < n && p[i] == p[j + 1]) j++;
    for (int k = i; k <= j; k++) ans[k] = j - i + 1;
    i = j;
  }
  while (q--) {
    int k;
    scanf("%d", &k);
    k--;
    printf("%d\n", ans[k]);
  }
  return 0;
}
