#include<bits/stdc++.h>
using namespace std;
const int N = 2005;
int m, n, k, ct = 0, res = 0, tmp;
int dp[N * N], suma[N], sumb[N];
pair <int, int> vt[N * N];
int main()
{
	if (fopen("input.txt", "r"))
		freopen("input.txt", "r", stdin);
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; ++i) scanf("%d", &tmp), suma[i] = suma[i - 1] + tmp;
	for (int i = 1; i <= n; ++i) scanf("%d", &tmp), sumb[i] = sumb[i - 1] + tmp;
	scanf("%d", &k);
	for (int i = 1; i <= m; ++i)
		for (int j = i; j <= m; ++j)
			vt[++ct] = {suma[j] - suma[i - 1], j - i + 1};
	sort(vt + 1, vt + ct + 1);
	for (int i = 1; i <= ct; ++i)
		dp[i] = max(dp[i - 1], vt[i].second);
	for (int i = 1; i <= n; ++i)
		for (int j = i; j <= n; ++j)
		{
			int x = sumb[j] - sumb[i - 1];
			int l = 1, r = ct, ans = 0;
			while (l <= r)
			{
				int mid = l + r >> 1;
				if (vt[mid].first <= k / x)
				{
					ans = mid;
					l = mid + 1;
				}
				else r = mid - 1;
			}
			res = max(res, (j - i + 1) * dp[ans]);
		}
	printf("%d\n", res);
}