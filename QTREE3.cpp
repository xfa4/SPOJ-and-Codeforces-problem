// Do you know how much I hate you?
#include <bits/stdc++.h>
#define sqr(x) (1LL*(x)*(x))
#define all(x) x.begin(), x.end()
#define size(a) (int) ((a).size())
#define last(x) x[size(x) - 1]
#define watch(x) cerr << " !" << (#x) << " = " << x << '\n';
#define TASK "something"
using namespace std;
 
typedef pair <int, int> ii;
#define fi first
#define se second
 
namespace FastIO {
    template <typename T> inline bool read(T &num) {
        num = 0; char c; bool neg = false;
        do { c = getchar(); } while (!isdigit (c) && c != '-' && c != EOF);
        if (c == EOF) return 0;
        if (c == '-') neg = true, c = getchar();
        while (isdigit (c)) num = num * 10 + c - '0', c = getchar();
        if (neg) num = -num;
        return 1;
    }
    template <typename T> inline void write(T num) {
        if (num < 0) putchar ('-'), write (-num);
        else {
            if (num  > 9) write (num / 10);
            putchar (num % 10 + '0');
        }
    }
}
using namespace FastIO;
 
const int N = 1e5 + 5;
int n, q;
vector <int> adj[N];
int dad[N], dep[N], par[N][30];
int numChild[N], head[N], pos[N], arr[N], chain[N];
 
void dfs(int u, int pu = 0, int d = 0) {
    numChild[u]++; dad[u] = pu; dep[u] = d;
    for (int v : adj[u]) {
        if (v == pu) continue;
        dfs(v, u, d + 1);
        numChild[u] += numChild[v];
    }
}
 
int idChain = 1, Time = 0;
void hld(int u) {
    pos[u] = ++Time; 
    arr[Time] = u;
    chain[u] = idChain;
    int best = 0, pos = -1;
    for (int v : adj[u]) {
        if (v == dad[u]) continue;
        if (best < numChild[v]) {
            pos = v;
            best = numChild[v];
        }
    }
    if (pos != -1) hld(pos);
    for (int v : adj[u]) {
        if (v == dad[u] || v == pos) continue;
        head[++idChain] = v; hld(v);
    }
}
 
void buildLCA() {
    for (int i = 1; i <= n; i++)
        par[i][0] = dad[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i <= n; i++)
            if (par[i][j-1] != 0)
                par[i][j] = par[par[i][j-1]][j-1];
}
 
int getLCA(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int LOG = (int) log2(dep[u]);
    for (int i = LOG; i >= 0; i--)
        if (dep[u] - (1 << LOG) >= dep[v])
            u = par[u][i];
    if (u == v) return u;
    for (int i = LOG; i >= 0; i--)
        if (par[u][i] != 0 && par[u][i] != par[v][i])
            u = par[u][i], v = par[v][i];
    return dad[u];
}
 
void prep() {
    dfs(1);
    head[1] =1;
    hld(1);
    buildLCA();
}
 
int best(int a, int b) {
    if (a == -1) return b;
    if (b == -1) return a;
    return min (a, b);
}
 
struct IntervalTree {
    int node[4*N];
 
    IntervalTree() { memset (node, -1, sizeof node); }
 
    void update(int u, int id = 1, int low = 1, int high = n) {
        if (low > u || high < u) return;
        if (low == high) {
            if (node[id] == -1)
                node[id] = u;
            else node[id] = -1;
            return;
        }
        int mid = (low + high) >> 1;
        update(u, id+id, low, mid);
        update(u, id+id+1, mid+1, high);
        node[id] = best(node[id+id], node[id+id+1]);
    }
 
    int get(int l, int r, int id = 1, int low = 1, int high = n) {
        if (low > r || high < l) return -1;
        if (l <= low && high <= r) return node[id];
        int mid = (low + high) >> 1;
        int x = get(l, r, id + id, low, mid);
        int y = get(l, r, id + id + 1, mid + 1, high);
        return best(x, y);
    }
} IT;
 
int get(int l, int r) {
    int u = r, a = l, res = -1;
    int idChainU = chain[u], idChainA = chain[a];
    while (true) {
        if (idChainU == idChainA) {
            res = best(res, IT.get(pos[a], pos[u]));
            break;
        }
        res = best(res, IT.get(pos[head[idChainU]], pos[u]));
        u = dad[head[idChainU]]; idChainU = chain[u];
    }
    if (res == -1) return -1;
    return arr[res];
}
 
int main() {
    ios :: sync_with_stdio (0);
    cin.tie (0); cout.tie (0);
 
    if (fopen ("main.in", "r"))
        freopen ("main.in", "r", stdin);
    else if (fopen (TASK".inp", "r"))
        freopen (TASK".inp", "r", stdin),
        freopen (TASK".out", "w", stdout);
 
    read(n), read(q);
    for (int i = 1; i < n; i++) {
        int u, v; 
        read (u), read (v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    prep();
 
    for (int i = 1; i <= q; i++) {
        int type, u;
        read (type), read (u);
        if (type == 0) IT.update(pos[u]);
        else write(get(1, u)), puts("");        
    }
 
    return 0;
} 
