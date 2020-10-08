#include<bits/stdc++.h>
#define n 50000
#define INF -15008
using namespace std;
int a[n+1];
struct Tree
{
    long long int res;
    long long int lsum,rsum,tot;
}tree[6*n];
void build(int node,int start,int end)
{
    if(start==end)
        tree[node].res=tree[node].lsum=tree[node].rsum=tree[node].tot=a[start];
    else
    {
        int mid=(end+start)>>1;
        int lchild=node<<1;
        int rchild=lchild+1;
        build(lchild,start,mid);
        build(rchild,mid+1,end);
        tree[node].tot=tree[lchild].tot+tree[rchild].tot;
        tree[node].lsum=max(tree[lchild].tot+tree[rchild].lsum,tree[lchild].lsum);
        tree[node].rsum=max(tree[rchild].rsum,tree[lchild].rsum+tree[rchild].tot);
        tree[node].res=max(tree[lchild].rsum+tree[rchild].lsum,max(tree[lchild].res,tree[rchild].res));
    }
}
Tree query(int node,int start,int end,int qs,int qe)
{
    if(start>=qs && qe>=end)
        return tree[node];
    if(qs>end || qe<start || start>end)
        return tree[0];
    int mid=(end+start)>>1;
    Tree lchild=query(node<<1,start,mid,qs,qe);
    Tree rchild=query((node<<1)+1,mid+1,end,qs,qe);
    Tree temp;
        temp.lsum=max(lchild.tot+rchild.lsum,lchild.lsum);
        temp.rsum=max(rchild.rsum,lchild.rsum+rchild.tot);
        temp.res=max(lchild.rsum+rchild.lsum,max(lchild.res,rchild.res));
        temp.tot=lchild.tot+rchild.tot;
        return temp;
}
int main()
{
    int m,q,qs,qe;
    scanf("%d",&m);
    tree[0].res=tree[0].lsum=tree[0].rsum=tree[0].tot=INF;
    for(int i=1;i<=m;i++)
        scanf("%d",&a[i]);
    scanf("%d",&q);
    build(1,1,m);
    while(q--)
    {
        scanf("%d%d",&qs,&qe);
        printf("%lld\n",query(1,1,m,qs,qe).res);
    }
}
