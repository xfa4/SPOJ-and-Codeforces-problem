#include<bits/stdc++.h>
using namespace std;
const int N=102;
const double EPS=1e-9;
int w,h,d;
double a[N][N],x[N],ans[12][12];
vector<int> vt[N];
void solve(){
	for(int i=1;i<=w*h;++i){
		int row = -1;
        for (int j = i; j <= w*h; ++j) {
            if (fabs(a[j][i]) > max(EPS, row == -1 ? 0 : fabs(a[row][i])))
                row = j;
        }
        if (row == -1) continue;
        if (row != i) for(int j=1;j<=w*h+1;++j) swap(a[i][j],a[row][j]);
		for(int j=i+1;j<=w*h;++j){
			double ratio=a[j][i]/a[i][i];
			for(int k=i;k<=w*h+1;++k){
				a[j][k]-=ratio*a[i][k];
			}
		}
	}
	for (int i=w*h;i>=1;--i) {
        for (int j=i+1;j<w*h+1;++j)
            a[i][w*h+1] -= a[j][w*h+1] * a[i][j];
        int v=i%w;if (v==0) v=w;int u=(i-v)/w;u++;
        ans[u][v] = a[i][w*h+1] /= a[i][i];
    }
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	//freopen("nhap.inp","r",stdin);
	//freopen("nhap.out","w",stdout);
	while(cin>>w>>h>>d && w*h!=0){
		memset(a,0,sizeof(a));
		for(int i=1;i<=h;++i)
			for(int j=1;j<=w;++j)
				cin>>x[(i-1)*w+j];
		for(int i=1;i<=h;++i)
			for(int j=1;j<=w;++j)
				for(int u=-d;u<=d;++u)
				for(int v=-d;v<=d;++v)
				if (abs(u)+abs(v)<=d && i+u>0 && i+u<=h && j+v>0 && j+v<=w){
					int U=i+u,V=j+v;
					vt[(i-1)*w+j].push_back((U-1)*w+V);
				}
		for(int i=1;i<=w*h;++i){
			x[i]=x[i]*vt[i].size();
			a[i][w*h+1]=x[i];
			for(int j=0;j<vt[i].size();++j)
				a[i][vt[i][j]]=(double)1;
			vt[i].clear();
		}
		solve();
		for(int i=1;i<=h;++i){
			for(int j=1;j<=w;++j){
				cout<<setw(8)<<setprecision(2)<<fixed<<ans[i][j]<<" ";
			}
			cout<<'\n';
		}
		cout<<'\n';
	}
}