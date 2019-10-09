// Do you know how much I hate you?
#include <bits/stdc++.h>
#define sqr(x) (1LL*(x)*(x))
#define all(x) x.begin(), x.end()
#define size(a) (int) ((a).size())
#define last(x) x[size(x) - 1]
#define watch(x) cerr << " !" << (#x) << " = " << x << '\n';
#define TASK "101964K"
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
 
struct dataQuery { int type, x, y, u, v; };
 
const int N = 8e5 + 5;
int q, n, m;
vector <dataQuery> ques;
 
vector <int> TRect[N], orderRect[N];
vector <int> TPoint[N], orderPoint[N];
 
void update_Rect(int x, int y, int w) {
    for (; x <= n; x += x & -x) {
        int bd = lower_bound(all(orderRect[x]), y) - orderRect[x].begin();
        for (; bd < size(orderRect[x]); bd += bd & -bd)
            TRect[x][bd] += w;
    }
}
 
void update_Point(int x, int y, int w) {
    for (; x <= n; x += x & -x) {
        int bd = lower_bound(all(orderPoint[x]), y) - orderPoint[x].begin();
        for (; bd < size(orderPoint[x]); bd += bd & -bd)
            TPoint[x][bd] += w;
    }
}
 
int get_Rect(int x, int y) {
    int res = 0;
    for (; x > 0; x -= x & -x) {
        int bd = lower_bound(all(orderRect[x]), y) - orderRect[x].begin();
        for (; bd > 0; bd -= bd & -bd)
            res += TRect[x][bd];
    }
    return res;
}
 
int get_Point(int x, int y) {
    int res = 0;
    for (; x > 0; x -= x & -x) {
        int bd = lower_bound(all(orderPoint[x]), y) - orderPoint[x].begin();
        for (; bd > 0; bd -= bd & -bd)
            res += TPoint[x][bd];
    }
    return res;
}
 
int get_Matrix(int x, int y, int u, int v) {
    return get_Rect(u, v) - get_Rect(x-1, v) - get_Rect(u, y-1) + get_Rect(x-1, y-1);   
}
 
void compress() {
    vector <int> valX, valY;
    for (auto it : ques) {
        int type = it.type, x = it.x, y = it.y, u = it.u, v = it.v;
        if (type == 1) valX.push_back (x), valY.push_back (y);
        else {
            valX.push_back (x), valX.push_back (x-1);
            valX.push_back (u), valX.push_back (u+1);
            valY.push_back (y), valY.push_back (y-1);
            valY.push_back (v), valY.push_back (v+1);
        }
    }
 
    sort (all(valX)), sort (all(valY));
    valX.erase(unique(all(valX)), valX.end());
    valY.erase(unique(all(valY)), valY.end());
 
    for (auto &it : ques) {
        int type = it.type, &x = it.x, &y = it.y, &u = it.u, &v = it.v;
        x = lower_bound(all(valX), x) - valX.begin() + 1;
        y = lower_bound(all(valY), y) - valY.begin() + 1;
        if (type == 2) {
            u = lower_bound(all(valX), u) - valX.begin() + 1;
            v = lower_bound(all(valY), v) - valY.begin() + 1;
        }
    }
 
    n = size(valX); m = size(valY);
}
 
void makeMemoryRect(int x, int y) {
    for (int i = x; i <= n; i += i & -i)
        orderRect[i].push_back (y);
    for (int i = x; i > 0; i -= i & -i)
        orderRect[i].push_back (y);
}
 
void makeMemoryPoint(int x, int y) {
    for (int i = x; i <= n; i += i & -i)
        orderPoint[i].push_back (y);
    for (int i = x; i > 0; i -= i & -i)
        orderPoint[i].push_back (y);
}
 
void prep() {
    for (int i = 1; i <= n; i++) {
        orderRect[i].push_back(0);
        orderPoint[i].push_back(0);
    }
    for (auto it : ques) {
        int type = it.type, x = it.x, y = it.y, u = it.u, v = it.v;
        if (type == 1) {
            makeMemoryPoint(x, y);
            makeMemoryRect (x, y);
        }
        else {
            makeMemoryRect(u, v);
            makeMemoryRect(x-1, v);
            makeMemoryRect(u, y-1);
            makeMemoryRect(x-1, y-1);
            makeMemoryPoint(x, y);
            makeMemoryPoint(x, v+1);
            makeMemoryPoint(u+1, y);
            makeMemoryPoint(u+1, v+1);
        }
    }
    for (int i = 1; i <= n; i++) {
        sort (all(orderPoint[i]));
        orderPoint[i].erase(unique(all(orderPoint[i])), orderPoint[i].end());
        TPoint[i].resize(size(orderPoint[i]));
 
        sort (all(orderRect[i]));
        orderRect[i].erase(unique(all(orderRect[i])), orderRect[i].end());
        TRect[i].resize(size(orderRect[i]));
    }
}
 
int main() {
    ios :: sync_with_stdio (0);
    cin.tie (0); cout.tie (0);
 
    if (fopen ("main.in", "r"))
        freopen ("main.in", "r", stdin);
    else if (fopen (TASK".inp", "r"))
        freopen (TASK".inp", "r", stdin),
        freopen (TASK".out", "w", stdout);
 
    read (q);
    for (int i = 1; i <= q; i++) {
        int type, u, v, x, y;
        read (type), read (u), read (v);
        if (type == 2) read (x), read (y);
        ques.push_back ({type, u, v, x, y});
    }
 
    compress();
    prep();
 
    long long res = 0;
    for (int i = 0; i < q; i++) {
        dataQuery it = ques[i];
        int type = it.type, x = it.x, y = it.y, u = it.u, v = it.v;
        if (type == 1) {
            res += get_Point(x, y);
            update_Rect(x, y, 1);
        }
        else {
            res += get_Matrix(x, y, u, v);
            update_Point (x, y, 1);
            update_Point (x, v+1, -1);
            update_Point (u+1, y, -1);
            update_Point (u+1, v+1, 1);
        }
        write (res), puts ("");
    }
 
 
    return 0;
}