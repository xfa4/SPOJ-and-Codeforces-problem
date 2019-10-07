#include<bits/stdc++.h>
using namespace std;
 
int u, v, u1, v1, res;
 
void cass() {
     ios::sync_with_stdio(0);
     cin.tie(0);
     //freopen("nhap.inp", "r", stdin);
     //freopen("nhap.out", "w", stdout);
}
 
void read() {
     int T; cin >> T;
     while (T--) {
          cin >> u >> v;
          int res = -1;
          u1 = u; v1 = v;
          if (u > 16) {
               while (u1 > 16) u1 -= 16;
               v1 = u1 + (v - u);
          }
          if (u1 <= 8 && v1 >= 9) res = max(res, 2);
          if (u1 <= 16 && v1 >= 17) res = max(res, 2);
          if (v-u+1 >= 32) res = max(res, ((v-u+1) / 16)*16);
          cout << res << '\n';
     }
}
 
int main() {
     cass(); read();
     return 0;
}