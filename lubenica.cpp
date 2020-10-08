// Author : dungdq //
#include <bits/stdc++.h>
using namespace std;
 
typedef pair <int, int> ii;
#define fi first
#define se second
 
const int inf = 1e9;
const int N = 1e5 + 5;
 
int n, q;
int dad[N], dep[N];
vector <ii> adj[N];
int par[N][30], Min[N][30], Max[N][30];
 
void dfs(int u, int pu = 0) {
    dad[u] = pu;
    for (auto it : adj[u]) {
        int v = it.fi;
        if (v == pu) continue;
        dep[v] = dep[u] + 1;
        dfs (v, u);
    }
    return;
}
 
void buildLCA() {
    for (int i = 1; i <= n; i++)
        for (int j = 0; (1 << j) <= n; j++) {
            Min[i][j] = inf;
            Max[i][j] = -inf;
        }
 
    for (int i = 1; i <= n; i++) {
        par[i][0] = dad[i];
        for (auto it : adj[i]) {
            int v = it.fi, w = it.se;
            if (v == dad[i]) 
                Min[i][0] = Max[i][0] = w;
        }
    }
 
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i <= n; i++)
            if (par[i][j-1] != 0) {
                par[i][j] = par[par[i][j-1]][j-1];
                Min[i][j] = min (Min[i][j-1], Min[par[i][j-1]][j-1]);
                Max[i][j] = max (Max[i][j-1], Max[par[i][j-1]][j-1]);
            }
 
    return;
}
 
ii getLCA(int u, int v) {
    if (dep[u] < dep[v]) swap (u, v);
    int LOG = (int) log2(dep[u]);
    int minDist = inf, maxDist = -inf;
 
    for (int i = LOG; i >= 0; i--) if (dep[u] - (1 << i) >= dep[v]) {
        minDist = min (minDist, Min[u][i]);
        maxDist = max (maxDist, Max[u][i]);
        u = par[u][i];
    }
 
    if (u == v) return ii (minDist, maxDist);
 
    for (int i = LOG; i >= 0; i--) if (par[u][i] != 0 && par[u][i] != par[v][i]) {
        minDist = min ({minDist, Min[u][i], Min[v][i]});
        maxDist = max ({maxDist, Max[u][i], Max[v][i]});
        u = par[u][i], v = par[v][i];
    }
 
    minDist = min ({minDist, Min[u][0], Min[v][0]});
    maxDist = max ({maxDist, Max[u][0], Max[v][0]});
 
    return ii (minDist, maxDist);
}
 
 
int main() {
    ios :: sync_with_stdio(0);
    cin.tie (0); cout.tie (0);
 
    if (fopen ("main.in", "r"))
        freopen ("main.in", "r", stdin);
 
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back ({v, w});
        adj[v].push_back ({u, w});
    }
 
    dfs (1);
    buildLCA();
 
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int u, v; cin >> u >> v;
        ii res = getLCA(u, v);
        cout << res.fi << ' ' << res.se << '\n';
    }
 
    return 0;
} 
