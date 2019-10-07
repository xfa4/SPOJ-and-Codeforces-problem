#include<bits/stdc++.h>
using namespace std;
const int N=1e5+2;
typedef pair<int,int> ii;
#define x first
#define y second
#define log asf
struct rd{
	int par,ma,mi;
	rd(){};
	rd(int par, int ma, int mi):par(par),ma(ma),mi(mi){};
}p[N][30];
int n,m,par[N],h[N],log=0,Min,Max;
vector<ii> a[N];
void dfs(int u, int pre){
	for(ii t:a[u])
		if (t.y!=pre){
			h[t.y]=h[u]+1;
			par[t.y]=u;
			p[t.y][0]=rd(u,t.x,t.x);
			dfs(t.y,u);
		}
}
void process(){
	while ((1<<log)<n) log++;log--;
	dfs(1,0);
	for(int j=1;j<=log;++j)
		for(int i=1;i<=n;++i){
			p[i][j].par=p[p[i][j-1].par][j-1].par;
			p[i][j].ma=max(p[i][j-1].ma,p[p[i][j-1].par][j-1].ma);
			p[i][j].mi=min(p[i][j-1].mi,p[p[i][j-1].par][j-1].mi);
		}
}
int LCA(int u, int v){
	if (h[u]<h[v]) swap(u,v);
	for(int i=log;i>=0;--i)
		if (h[u]-(1<<i)>=h[v]) u=p[u][i].par;
	if (u==v) return u;
	for(int i=log;i>=0;--i)
		if (p[u][i].par>0 && p[u][i].par!=p[v][i].par){
			u=p[u][i].par;
			v=p[v][i].par;
		}
	return par[u];
}
void getv(int u, int v){
	for(int i=log;i>=0;--i)
		if (h[u]-(1<<i)>=h[v]){
			Min=min(p[u][i].mi,Min);
			Max=max(p[u][i].ma,Max);
			u=p[u][i].par;
		}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	//freopen("nhap.inp","r",stdin);
	//freopen("nhap.out","w",stdout);
	cin>>n;
	for(int i=1;i<n;++i){
		int u,v,w;
		cin>>u>>v>>w;
		a[u].push_back(ii(w,v));
		a[v].push_back(ii(w,u));
	}
	process();
	int T,u,v;
	cin>>T;
	while(T--){
		cin>>u>>v;
		int x=LCA(u,v);
		Min=1e9;Max=0;
		getv(u,x);getv(v,x);
		cout<<Min<<" "<<Max<<'\n';
	}
} 