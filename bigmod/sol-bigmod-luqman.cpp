#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

char s[N];

int main() {
  int mod;
  scanf("%s %d", s, &mod);
  int n = strlen(s);
  long long now = 0;
  for (int i = 0; i < n; i++) {
    now = (now * 10 + s[i] - '0') % mod;
  }
  cout << now << endl;
  return 0;
}
