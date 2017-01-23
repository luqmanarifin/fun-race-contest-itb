#include <bits/stdc++.h>

using namespace std;

const int N = 105;

int a[N];

int main() {
  int n, x;
  scanf("%d %d", &n, &x);
  for (int i = 0; i < n; i++) scanf("%d", a + i);
  sort(a, a + n);
  int sum = 0, ans = 0;
  for (int i = 0; i < n; i++) {
    if (sum + a[i] <= x) {
      sum += a[i];
      ans = i + 1;
    }
  }
  cout << ans << endl;
  return 0;
}
