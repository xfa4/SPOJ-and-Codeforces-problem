#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int nc[N], n;
vector <int> a[N];
void dfs(int u, int pre)
{
	bool isLeaf = true;
	for (int v : a[u])
	{
		if (v == pre) continue;
		isLeaf = false;
		dfs(v, u);
		nc[u] += nc[v];
	}
	if (isLeaf) nc[u]++;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	if (fopen("input.txt", "r"))
		freopen("input.txt", "r", stdin);
	cin >> n;
	for (int i = 2; i <= n; ++i)
	{
		int x; cin >> x;
		a[x].push_back(i);
		a[i].push_back(x);
	}
	dfs(1, 0);
	sort(nc + 1, nc + 1 + n);
	for (int i = 1;i <= n; ++i)
		cout << nc[i] << ' ';
}