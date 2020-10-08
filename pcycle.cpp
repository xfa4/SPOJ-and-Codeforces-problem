#include <bits/stdc++.h>
using namespace std;
 
const int N = 205;
const int M = N * N;
int n, m, a[N][N], d[N][N], deg[N], f[M];
vector <int> lst;
 
int main() {
//    freopen ("pcycle.in", "r", stdin);
//    freopen ("pcycle.out", "w", stdout);
 
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        a[u][v] = a[v][u] = c;
        d[u][v] = d[v][u] = 1;
        deg[u]++; deg[v]++;
    }
 
    for (int i = 1; i <= n; i++) if (deg[i] % 2 == 1) {
        cout << -1 << '\n'; return 0;
    }
 
    stack <int> st; st.push (1);
    while (st.size()) {
        int u = st.top();
        if (deg[u] == 0) {
            lst.push_back (u);
            st.pop();
        }
        else {
            for (int v = 1; v <= n; v++) if (d[u][v]) {
                d[u][v] = d[v][u] = 0;
                deg[u]--; deg[v]--;
                st.push (v); break;
            }
        }
    }
 
    int start = -1, Min = INT_MAX;
    for (int i = 1; i < lst.size(); i++) {
        f[i] = f[i-1] + a[lst[i-1]][lst[i]];
        if (f[i] < Min) { Min = f[i], start = i; }
    }
 
    int sum = 0;
    for (int i = start + 1; i < lst.size(); i++) {
        sum += a[lst[i-1]][lst[i]];
        if (sum < 0) { cout << -1 << '\n'; return 0; }
    }
 
    for (int i = 1; i < start; i++) {
        sum += a[lst[i-1]][lst[i]];
        if (sum < 0) { cout << -1 << '\n'; return 0; }
    }
 
    for (int i = start; i < lst.size(); i++)
        cout << lst[i] << ' ';
 
    for (int i = 1; i <= start; i++)
        cout << lst[i] << ' ';
 
    return 0;
}
 
