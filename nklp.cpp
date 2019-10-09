/******************************
**    Author : dungdq2002    **
**    Created: 18.09.2019    **
*******************************/

#include <bits/stdc++.h>

using namespace std;

#define TASK "nklp_ver1"
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
const int N = 3e5 + 5;
int n, a[N], bord[N], lst[N], LOG[N], Min[N][30], Max[N][30];

int getMax(int l, int r) {
    int k = LOG[r-l+1];
    return max (Max[l][k], Max[r-(1<<k)+1][k]);
}

int getMin(int l, int r) {
    int k = LOG[r-l+1];
    return min (Min[l][k], Min[r-(1<<k)+1][k]);
}

int cal(int l, int r) {
    if (l >= r) return (a[l] == 1);
    int m = (l + r) >> 1, res = 0;
    for (int i = m + 1; i <= r; i++) {
        int maxVal = getMax (m + 1, i);
        int rig = i, lef = i - maxVal + 1;
        if (lef < bord[rig] || lef > m || lef < l) continue;
        if (getMin (lef, rig) == 1 && getMax (lef, rig) == maxVal)
            res = max (res, maxVal); 
    }
    for (int i = m; i >= l; i--) {
        int maxVal = getMax (i, m);
        int lef = i, rig = i + maxVal - 1;
        if (lef < bord[rig] || rig <= m || rig > r) continue;
        if (getMin (lef, rig) == 1 && getMax (lef, rig) == maxVal)
            res = max (res, maxVal);
    }
    int part1 = cal (l, m);
    int part2 = cal (m + 1, r);
    return max ({res, part1, part2});
}

#undef int
int main() {
#define int long long

    ios :: sync_with_stdio (0);
    cin.tie (0); cout.tie (0);

    if (fopen ("main.in", "r"))
        freopen ("main.in", "r", stdin);
    else if (fopen (TASK".inp", "r"))
        freopen (TASK".inp", "r", stdin),
        freopen (TASK".out", "w", stdout);

    cin >> n;
    
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 20; j++)
            Min[i][j] = inf, Max[i][j] = -inf;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        Max[i][0] = a[i];
        Min[i][0] = a[i];
    }
    
    for (int j = 1; j < 20; j++)
        for (int i = 1; i + (1 << j) <= n + 1; i++) {
            Max[i][j] = max (Max[i][j-1], Max[i+(1<<(j-1))][j-1]);
            Min[i][j] = min (Min[i][j-1], Min[i+(1<<(j-1))][j-1]);
        }

    for (int i = 1; i <= n; i++)
        LOG[i] = (int) log2(i);

    bord[1] = 1, lst[a[1]] = 1;
    for (int i = 2; i <= n; i++) {
        if (lst[a[i]] == 0) bord[i] = bord[i-1];
        else bord[i] = max (bord[i-1], lst[a[i]]+1);
        lst[a[i]] = i;
    }

    cout << cal (1, n) << '\n';

    return 0;
}