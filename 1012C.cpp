#include<bits/stdc++.h>
using namespace std;
const int N=5e3+5;
int n,a[N],dp[N][N],ans[N],Min[N][N];
int cost(int i, int j){
    if (a[j]<a[i]) return 0;
    else return a[j]-a[i]+1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    //freopen("hills.inp","r",stdin);
    //freopen("hills.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i];
    memset(dp,0x3f,sizeof(dp));
    memset(ans,0x3f,sizeof(ans));
    memset(Min,0x3f,sizeof(Min));
    for(int i=0;i<=n;++i) dp[i][0]=0,Min[i][0]=0;
    dp[1][1]=cost(1,2);
    dp[n][1]=cost(n,n-1);
    a[n+1]=a[n]-1;a[0]=a[1]-1;
    ans[1]=min(dp[1][1],dp[n][1]);
    for(int i=2;i<n;++i) dp[i][1]=cost(i,i-1)+cost(i,i+1),ans[1]=min(ans[1],dp[i][1]);
    for(int i=1;i<=n;++i)
        Min[i][1]=min(Min[i-1][1],dp[i][1]);
    for(int i=3;i<=n;++i){
        for(int j=2;j<=(n+1)/2;++j){
            dp[i][j]=min(dp[i][j],Min[i-3][j-1]+cost(i,i-1)+cost(i,i+1));
            if (a[i]>=a[i-2]){
                dp[i][j]=min(dp[i][j],dp[i-2][j-1]+cost(i,i+1));
            }
            else{
                if (a[i-1]>=a[i]){
                    if (a[i-1]>=a[i-2]) dp[i][j]=min(dp[i][j],dp[i-2][j-1]+a[i-2]-a[i]+cost(i,i+1));
                    else dp[i][j]=min(dp[i][j],dp[i-2][j-1]+cost(i,i-1)+cost(i,i+1));
                }
                else dp[i][j]=min(dp[i][j],dp[i-2][j-1]+cost(i,i+1));
            }
            ans[j]=min(ans[j],dp[i][j]);
            Min[i][j]=min(Min[i-1][j],dp[i][j]);
        }
    }
    for(int i=1;i<=(n+1)/2;++i)
        cout<<ans[i]<<' ';
}