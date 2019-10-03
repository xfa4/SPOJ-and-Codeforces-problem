#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 3;
int n, Q, a[N], S, L, R;
int cnt[1000006];
long long res, ans[N];
struct QUERY
{
	int l, r, id;
	bool operator < (const QUERY & a) const { return l/S != a.l/S ? l < a.l : r < a.r; }
}q[N];
void read(int &val)
{
    val = 0; char c; c = getchar();
    while (!isdigit(c)) c = getchar();
    do { val = val * 10 + c - '0'; c = getchar(); } while (isdigit(c));
}
void write(long long val)
{
    if (val < 10) putchar('0' + val);
    else{ write(val / 10); putchar('0' + val % 10); }
}
long long func(int x) { return 1LL * cnt[x] * cnt[x] * x; }
void update(int x, int val)
{
    res -= func(x);
    cnt[x] += val;
    res += func(x);
}
int main()
{
	if (fopen("input.txt", "r"))
        assert(freopen("input.txt", "r", stdin));
    read(n); read(Q);
    S = sqrt(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= Q; ++i) read(q[i].l), read(q[i].r), q[i].id = i;
    sort(q + 1, q + 1 + Q);
	for (int id = 1; id <= Q; ++id)
	{
		if (id == 1 || q[id].l / S != q[id - 1].l / S)
		{
			for (int i = L; i <= R; ++i) cnt[a[i]] = 0;
			res = 0;
			L = q[id].l, R = q[id].r;
			for (int i = L; i <= R; ++i) update(a[i], 1);
		}
		else
		{
			while (L < q[id].l) update(a[L], - 1), L++;
			while (L > q[id].l) --L, update(a[L], 1);
			while (R < q[id].r) ++R, update(a[R], 1);
		}
		ans[q[id].id] = res;
	}
	for (int i = 1; i <= Q; ++i) write(ans[i]), puts("");
}