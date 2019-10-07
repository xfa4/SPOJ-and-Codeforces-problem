#include<bits/stdc++.h>
using namespace std;
const int N=102;
struct node{
	int v,d,t;
	node(){};
	node(int v, int d, int t):v(v),d(d),t(t){};
	bool operator > (const node &a) const{
		return t>a.t;
	}
};
vector<node> a[N];
priority_queue<node, vector<node>, greater<node> > pq;
int dis[N],n,m,k;
void dijkstra(){
	pq.push(node(1,0,0));
	while(!pq.empty()){
		node x=pq.top();
		pq.pop();
		if (dis[x.v]<=x.d) continue;
		dis[x.v]=x.d;
		for(node y:a[x.v])
			if (x.t+y.t<=k)
				pq.push(node(y.v,x.d+y.d,x.t+y.t));
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	//freopen("nhap.inp","r",stdin);
	//freopen("nhap.out","w",stdout);
	int T;cin>>T;
	while(T--){
		cin>>k>>n>>m;
		for(int i=1;i<=n;++i){
			dis[i]=1e9;
			a[i].clear();
		}
		while(m--){
			int u,v,d,t;
			cin>>u>>v>>d>>t;
			a[u].push_back(node(v,d,t));
		}
		dijkstra();
		if (dis[n]==1e9) cout<<-1;
		else cout<<dis[n];
		cout<<'\n';
	}
}  