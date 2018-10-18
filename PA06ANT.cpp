#include<cstdio>
#define MAX 33
typedef long long ll;
const ll a[24][2]={{1,2},{1,4},{1,5},{2,1},{2,3},{2,6},{3,2},{3,4},{3,7},{4,1},{4,3},{4,8},
                    {5,1},{5,6},{5,8},{6,2},{6,5},{6,7},{7,3},{7,6},{7,8},{8,4},{8,5},{8,7}};
int k;
ll p;
char f,l;
struct matrix {
    int m,n;
    ll d[MAX][MAX];
};
matrix fst,mul;
matrix multi(const matrix &a,const matrix &b) {
    matrix c;
    int x=a.m;
    int y=a.n;
    int z=b.n;
    int i,j,k;
    c.m=x;c.n=z;
    for (i=0;i<x;i=i+1)
        for (j=0;j<z;j=j+1) {
            c.d[i][j]=0;
            for (k=0;k<y;k=k+1) c.d[i][j]=(c.d[i][j]+a.d[i][k]*b.d[k][j])%p;
        }
    return (c);
}
matrix multiply(const matrix &a,const int &k) {
    if (k==1) return (a);
    matrix c=multiply(a,k/2);
    c=multi(c,c);
    if (k%2==1) c=multi(c,a);
    return (c);
}
void construct(void) {
    int i,j;
    mul.m=24;
    mul.n=24;
    for (i=0;i<24;i=i+1)
        for (j=0;j<24;j=j+1) {
            if ((a[j][0]==a[i][1]) && (a[j][1]!=a[i][0])) mul.d[i][j]=1;
            else mul.d[i][j]=0;
        }
}
void process(void) {
    scanf("%c",&f);
    scanf("%c",&l);
    scanf("%c",&l);
    f=f-'A'+1;
    l=l-'A'+1;
    scanf("%d",&k);
    scanf("%lld",&p);
    construct();
    int i;
    fst.m=1;
    fst.n=24;
    for (i=0;i<24;i=i+1) fst.d[0][i]=(a[i][0]==f);
    if (k>1) fst=multi(fst,multiply(mul,k-1));
    ll res=0;
    for (i=0;i<24;i=i+1)
        if (a[i][1]==l) res=(res+fst.d[0][i])%p;
    printf("%lld",res);
}
int main(void) {
    //freopen("ant.inp","r",stdin);
    //freopen("ant.ans","w",stdout);
    process();
    return 0;
} 