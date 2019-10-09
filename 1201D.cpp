/******************************
**    Author : dungdq2002    **
*******************************/
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define int long long
#define sqr(x) (1LL*x*x)
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define BIT(x, k) (x >> k & 1)
#define cntBit(x) __builtin_popcountll(x)
#define REP(i,a,b) for (int i = (int) a; i < (int) b; i++)
#define FOR(i,a,b) for (int i = (int) a; i <= (int) b; i++)
#define FORD(i,a,b) for (int i = (int) a; i >= (int) b; i--)
 
typedef pair <int, int> ii;
 
const int N = 2e5 + 5;
const int inf = 1e18 + 5;
 
int dp[N][4];
int n, m, k, q;
vector <int> row[N];
vector <int> spec[N];
vector <int> specCol;
 
int findLef (int x) {
	int k = upper_bound (all (specCol), x) - specCol.begin() - 1;
	if (k == -1) k = 0; assert (k >= 0 && k < q);
	return specCol[k];
}
 
int findRig (int x) {
	int k = lower_bound (all (specCol), x) - specCol.begin();
	if (k == specCol.size()) k--; assert (k >= 0 && k < q);
	return specCol[k];
}
 
int dist (int a, int b) { return abs (a - b); }
 
void minimize(int &a, int b) { a = min (a, b); }
 
#undef int
int main() {
#define int long long
 
	ios :: sync_with_stdio (0);
	cin.tie (0); cout.tie (0);
 
	if (fopen ("main.in", "r"))
		freopen ("main.in", "r", stdin);
 
	cin >> m >> n >> k >> q;
	row[1].push_back (1);
	for (int i = 1; i <= k; i++) {
		int x, y; cin >> x >> y;
		row[x].push_back (y);
	}
 
	for (int i = 1; i <= q; i++) {
		int x; cin >> x;
		specCol.push_back (x);
	}
	sort (all (specCol));
 
	for (int i = 1; i <= m; i++) {
		sort (all (row[i]));
		if (row[i].empty()) {
			spec[i] = spec[i-1];
			continue;
		}
		int lef = row[i][0], rig = row[i].back();
		spec[i].push_back (findLef (lef));
		spec[i].push_back (findRig (lef));
		spec[i].push_back (findLef (rig));
		spec[i].push_back (findRig (rig));
	}
 
 
	FOR (i, 0, m) FOR (j, 0, 3)
		dp[i][j] = inf;
		
	for (int i = 0; i < 4; i++) {
		dp[1][i] = dist (1, row[1].back());
		dp[1][i] += dist (row[1].back(), spec[1][i]);
	}
 
	int last = m;
	for (int i = m; i >= 1; i--)
		if (row[i].size()) break;
		else last = i - 1;
 
	if (last == 1) {
		cout << row[1].back() - 1 << '\n';
		exit (0);
	}
 
	for (int i = 2; i <= last; i++)
		for (int prv = 0; prv < 4; prv++)
			for (int cur = 0; cur < 4; cur++) {
				int cost = 1 + dp[i-1][prv];
				if (row[i].size()) {
					int lef = row[i][0], rig = row[i].back();
					int case1 = 0, case2 = 0;
 
					case1 += dist (spec[i-1][prv], lef);
					case1 += dist (lef, rig);
					if (i != last) case1 += dist (rig, spec[i][cur]);
 
					case2 += dist (spec[i-1][prv], rig);
					case2 += dist (rig, lef);
					if (i != last) case2 += dist (lef, spec[i][cur]);
 
					cost += min (case1, case2);
				} else cost += dist (spec[i-1][prv], spec[i][cur]);
 
				minimize (dp[i][cur], cost);
			}
 
	int res = inf;
	for (int i = 0; i < 4; i++)
		minimize (res, dp[last][i]);
 
	cout << res << '\n';
	
	return 0;
}