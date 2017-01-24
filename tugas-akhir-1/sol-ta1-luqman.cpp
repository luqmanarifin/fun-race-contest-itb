#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int mod = 1e9 + 7;

string str[] = {"DOTA", "GTA", "TA"};
string s;

int main() {
  cin >> s;
  int n = s.size();
  long long ans = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 3; j++) {
      if (i + str[j].size() <= n && s.substr(i, str[j].size()) == str[j]) {
        ans = ans * str[j].size() % mod;
        i += str[j].size() - 1;
        break;
      }
    }
  }
  cout << ans << endl;
  return 0;
}
