// A classic problem using centroid decomposition
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, inf = 0x3f3f3f3f;
int n, par[N], ans[N], q;
set <int> a[N];
struct LCA
{
	int h[N], p[N][20], Log = 0;
	void dfs(int u, int pre)
	{
		for (auto it = a[u].begin(); it != a[u].end(); ++it)
		{
			int v = *it;
			if (v == pre) continue;
			h[v] = h[u] + 1;
			p[v][0] = u;
			dfs(v, u);
		}
	}
	void process()
	{
		while ((1 << Log) <= n) Log++;
		Log--;
		dfs(1, 0);
		for (int j = 1; j <= Log; ++j)
			for (int i = 1; i <= n; ++i)
				p[i][j] = p[p[i][j - 1]][j - 1];
	}
	int get(int u, int v)
	{
		if (h[u] < h[v]) swap(u, v);
		for(int i = Log; i >= 0; --i)
        	if (h[u]- (1 << i) >= h[v]) u = p[u][i];
        if (u == v) return u;
        for (int i = Log; i >= 0; --i)
        	if (p[u][i] > 0 && p[u][i] != p[v][i])
        	{
        		u = p[u][i];
        		v = p[v][i];
        	}
        return p[u][0];
	}
	int dist(int u, int v) { return h[u] + h[v] - 2 * h[get(u, v)]; }
}lca;
struct DECOMPOSITION
{
	int nn, nc[N];
	void dfs(int u, int pre)
	{
		nc[u] = 1;
		nn++;
		for (auto it = a[u].begin(); it != a[u].end(); ++it)
		{
			int v = *it;
			if (v == pre) continue;
			dfs(v, u);
			nc[u] += nc[v];
		}
	}
	int Find(int u, int pre)
	{
		for (auto it = a[u].begin(); it != a[u].end(); ++it)
			if (*it != pre && nc[*it] > nn / 2)
				return Find(*it, u);
		return u;
	}
	void decompose(int root, int p)
	{
		nn = 0;
		dfs(root, 0);
		int centroid = Find(root, 0);
		if (p == -1) p = centroid;
		par[centroid] = p;
		for (auto it = a[centroid].begin(); it != a[centroid].end(); ++it)
		{
			a[*it].erase(centroid);
			decompose(*it, centroid);
		}
		a[centroid].clear();
	}
}decomposition;
void update(int u)
{
	int x = u;
	while(1)
	{
		ans[x] = min(ans[x], lca.dist(x, u));
		if(x == par[x]) break;
		x = par[x];
	}
}
int query(int u)
{
	int x = u, res = inf;
	while(1)
	{
		res = min(res, lca.dist(u,x) + ans[x]);
		if(x == par[x]) break;
		x = par[x];
	}
	return res;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	if (fopen("input.txt", "r"))
        freopen("input.txt", "r", stdin);
    cin >> n >> q;
    for (int i = 1; i < n; ++i)
    {
    	int u, v;
    	cin >> u >> v;
    	a[u].insert(v);
    	a[v].insert(u);
    }
    lca.process();
    decomposition.decompose(1, -1);
    memset(ans, 0x3f, sizeof(ans));
    update(1);
    while(q--)
	{
		int t, v;
		cin >> t >> v;
		if(t == 1) update(v);
		else cout << query(v) << '\n';
	}
}