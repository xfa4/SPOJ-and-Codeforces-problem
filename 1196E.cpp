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
const int inf = 1e9;
const int base = 1e6;
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
 
int w, b;
bool complete;
vector <ii> List;
map <ii, int> vis;
queue <ii> q;
 
void bfs(int u, int v) {
	vis[{u,v}] = true;
	while (q.size()) {
		int u = q.front().fi, v = q.front().se; q.pop();
		List.push_back ({u, v});
		for (int dir = 0; dir < 4; dir++) {
			int x = u + dx[dir];
			int y = v + dy[dir];
			if (x < 1 || x > inf || y < 1 || y > inf) continue;
			if (vis[{x, y}]) continue;
			bool white = ((y + x) % 2 == 0);
			if (white) {
				if (w) {
					vis[{x, y}] = true;
					w--, q.push ({x, y});
				}
			}
			else {
				if (b) {
					vis[{x, y}] = true;
					b--, q.push ({x, y});
				}
			}
		}		
	}
	complete = (w == 0) && (b == 0);
}
 
void start(int u, int v, int &xx, int &yy) {
	int c = u, ac = v;
	while (q.size()) q.pop();
	List.clear(); vis.clear();
	for (int i = 1; i <= xx; i++) {
		vis[{u, v}] = true;
		vis[{u, v+1}] = true;
		q.push ({u, v+1});
		q.push ({u, v}); 
		v += 2; 
	}
	yy -= xx; xx = 0; bfs (c, ac);
}
 
void solve() {
	cin >> b >> w;
	complete = true;
	if (b < w) start (base, base+1, b, w);
	else start (base, base, w, b);
	if (!complete)
		cout << "NO\n";
	else {
		cout << "YES\n";
		for (auto it : List)
			cout << it.se << ' ' << it.fi << '\n';
	}
}
 
#undef int
int main() {
#define int long long
 
	ios :: sync_with_stdio (0);
	cin.tie (0); cout.tie (0);
 
	if (fopen ("main.in", "r"))
		freopen ("main.in", "r", stdin);
 
	int nTest; cin >> nTest;
	while (nTest--) solve();
 
	return 0;
}