#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N = 3e5;
pii ar[N + 5];
bool CF(const pii &a, const pii &b){
	if(a.fi != b.fi) return a.fi > b.fi;
	return a.se < b.se;
}
int n, q;

int share[N + 5];
inline void generate(){
	for(int i = 0;i < n;){
		int j = i;
		while(j < n && ar[i] == ar[j]){
			++j;
		}
		for(int k = i; k < j; ++k){
			share[k] = j - i;
		}
		i = j;
	}	
}

int main(){
	scanf("%d%d", &n, &q);
	for(int i = 0;i < n; ++i){
		scanf("%d%d", &ar[i].fi, &ar[i].se);
	}
	sort(ar, ar+n, CF);
	generate();
	for(int i = 0;i < q; ++i){
		int k;
		scanf("%d", &k);
		printf("%d\n", share[k-1]);
	}

	return 0;
}