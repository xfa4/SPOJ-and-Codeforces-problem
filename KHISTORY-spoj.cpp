#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, m, ct = 0, Time = 0;
int low[N], num[N], country[N];
vector <int> a[N], adj[N], coconut[N];
struct ii { int x, y; };
vector <ii> edge;
bool vis[N];
int res = 0, dp[N][3];
void dfs(int u, int pre)
{
	low[u] = num[u] = ++Time;
	for (int v : a[u])
	{
		if (v == pre) continue;
		if (num[v] != 0)
			low[u] = min(low[u], num[v]);
		else
		{
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] >= num[v]);
			else edge.push_back({u, v});
		}
	}
}
void dfs_c(int u, int pre)
{
	country[u] = ct;
	for (int v : adj[u])
	{
		if (v == pre) continue;
		dfs_c(v, u);
	}
}
 
void cal(int u, int pre)
{
	vis[u] = true;
	bool ok = false, isLeaf = true;
	for (int v : coconut[u])
	{
		if (v == pre) continue;
		cal(v, u);
		isLeaf = false;
		if (0LL + dp[u][0] + dp[v][1] > 2e9) dp[u][0] = 2e9; 
		else dp[u][0] += dp[v][1];
		if (dp[v][1] >= dp[v][2]) dp[u][1] += dp[v][2], ok = true;
		else dp[u][1] += dp[v][1];
		dp[u][2] += min({dp[v][0], dp[v][1], dp[v][2]});
	}
	dp[u][2]++;
	if (isLeaf)
	{
		dp[u][1] = 1e9;
		return;
	}
	if (!ok)
	{
		int bonus = 2e9;
		for (int v : coconut[u])
		{
			if (v == pre) continue;
			bonus = min(bonus, dp[v][2] - dp[v][1]);
		}
		dp[u][1] += bonus;
	}
}
 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	if (fopen("input.txt", "r"))
		assert(freopen("input.txt", "r", stdin));
	cin >> n >> m;
	while (m--)
	{
		int x, y;
		cin >> x >> y;
		a[x].push_back(y);
		a[y].push_back(x);
	}
	for (int i = 1; i <= n; ++i)
		if (!num[i]) dfs(i, 0);
	for (ii tmp : edge)
	{
		adj[tmp.x].push_back(tmp.y);
		adj[tmp.y].push_back(tmp.x);
	}
	for (int  i = 1; i <= n ;++i) if (!country[i])
	{
		ct++;
		dfs_c(i, 0);
	}
	for (int u = 1; u <= n; ++u)
		for (int v : a[u])
			if (country[v] != country[u]){
				coconut[country[v]].push_back(country[u]);
				coconut[country[u]].push_back(country[v]);
			}
	for (int  i = 1; i <= ct; ++i)
	{
		sort(coconut[i].begin(), coconut[i].end());
		coconut[i].resize(unique(coconut[i].begin(), coconut[i].end()) - coconut[i].begin());
	}
	for (int  i = 1; i <= ct; ++i) if (!vis[i])
	{
		cal(i, 0);
		res += min({dp[i][1], dp[i][2]});
	}
	cout << res;
} 