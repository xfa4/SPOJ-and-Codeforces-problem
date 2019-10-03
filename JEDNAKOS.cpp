#include<bits/stdc++.h>
using namespace std;
string s;
const int N=1002;
int a[N],f[N][5*N],val=0,n=0,mul[5];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	//freopen("nhap.inp","r",stdin);
	//freopen("nhap.out","w",stdout);
	cin>>s;bool ok=true;
	for(int i=0;i<s.size();++i){
		if (s[i]=='='){ok=false;continue;}
		if (ok) a[i+1]=(int)(s[i]-'0'),++n;
		else val=val*10+(int)(s[i]-'0');
	}
	for(int i=0;i<=n;++i) for(int j=0;j<=val;++j) f[i][j]=1e9;
    f[0][0] = 0; mul[0] = 1;
    for(int i=1;i<=4;++i) mul[i]=mul[i-1]*10;
    for(int i=1;i<=n;++i) 
		for(int j=1;j<=val;++j){
	        int valu=0;
	        for(int t=1;t<=4;++t){
	            if (i-t+1<=0) break;
	            valu+=mul[t-1]*a[i-t+1];
	            if (j<valu) break;
	            if (!valu && i < n) f[i][j]=min(f[i][j],f[i-t][j]);
	                else f[i][j]=min(f[i][j],f[i-t][j-valu]+1);
	        }
	    }
	cout<<f[n][val]-1;
} 