#include<bits/stdc++.h>
using namespace std;
const int N=252;
vector<int> a[N];
struct ii{
	int x,y,ty;
	ii(){};
	ii(int x, int y, int ty): x(x),y(y),ty(ty){};
};
int n,m,s,t,f[N][N][2];
queue<ii> q;
void bfs(){
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) f[i][j][0]=f[i][j][1]=2e9;
	f[s][t][0]=0;
	q.push(ii(s,t,0));
	while(!q.empty()){
		ii tmp=q.front();q.pop();
		int u=tmp.x,v=tmp.y,z=tmp.ty;
		if (z==0){
			for(int i=0;i<a[u].size();++i){
				int tp=a[u][i];
				if (f[u][v][z]+1<f[tp][v][1]){
					f[tp][v][1]=f[u][v][z]+1;
					q.push(ii(tp,v,1));
				}
			}
		}
		else{
			for(int i=0;i<a[v].size();++i){
				int tp=a[v][i];
				if (f[u][v][z]+1<f[u][tp][0]){
					f[u][tp][0]=f[u][v][z]+1;
					q.push(ii(u,tp,0));
				}
			}
		}
	}	
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	//freopen("nhap.inp","r",stdin);
	//freopen("nhap.out","w",stdout);
	cin>>n>>m>>s>>t; int u,v;
	for(int i=1;i<=m;++i){
		cin>>u>>v;
		a[u].push_back(v);
	}
	bfs();int res=2e9;
	for(int i=1;i<=n;++i) res=min(res,f[i][i][0]);
	if (res==2e9) cout<<-1; else cout<<res/2;
} 