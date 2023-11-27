#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int>pii;

const int N=100001,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;

int n,m,p;
int ar[N];

struct Node {
    int l,r;
    ll sum;
    ll lazy1,lazy2;
}tr[N*4];

void pushup(int u){
    tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
}

void pushdown(int u){
    ll lazy1=tr[u].lazy1,lazy2=tr[u].lazy2;
    Node &le=tr[u<<1],&ri=tr[u<<1|1];

    le.sum=(le.sum*lazy2)+(le.r-le.l+1)*lazy1;
    le.lazy1=(le.lazy1*lazy2)+lazy1;
    le.lazy2*=lazy2;

    ri.sum=(ri.sum*lazy2)+(ri.r-ri.l+1)*lazy1;
    ri.lazy1=(ri.lazy1*lazy2)+lazy1;
    ri.lazy2*=lazy2;
    
    tr[u].lazy1=0;
    tr[u].lazy2=1;
}

void build(int u,int l,int r){
    if(l==r) {
        tr[u]={l,r,ar[l],0,1};
    }
    else{
        tr[u]={l,r,0,0,1};
        int mid=l+r>>1;
        build(u<<1,l,mid),build(u<<1|1,mid+1,r);
        pushup(u);
    }
}

ll querysum(int u,int l,int r) {
    if(tr[u].l>=l&&tr[u].r<=r)return tr[u].sum;
    else{
        pushdown(u);
        int mid=tr[u].l+tr[u].r>>1;
        ll sum=0;
        if(l<=mid){
            sum+=querysum(u<<1,l,r);
        }
        if(r>mid){
            sum+=querysum(u<<1|1,l,r);
        }
        return sum;
    }
}

void add(int u,int l,int r,int v){
    if(tr[u].l>=l&&tr[u].r<=r){
        tr[u].sum+=(tr[u].r-tr[u].l+1)*v;
        tr[u].lazy1+=v;
    }
    else{
        pushdown(u);
        int mid=tr[u].l+tr[u].r>>1;
        if(mid>=l){
            add(u<<1,l,r,v);
        }
        if(mid<r){
            add(u<<1|1,l,r,v);
        }
        pushup(u);
    }
}

void mul(int u,int l,int r,int v){
    if(tr[u].l>=l&&tr[u].r<=r){
        tr[u].sum*=v;
        tr[u].lazy1*=v;
        tr[u].lazy2*=v;
    }
    else{
        pushdown(u);
        int mid=tr[u].l+tr[u].r>>1;
        if(mid>=l){
            mul(u<<1,l,r,v);
        }
        if(mid<r){
            mul(u<<1|1,l,r,v);
        }
        pushup(u);
    }
}

int main(){
    scanf("%d%d",&n,&p);
    for(int i=1;i<=n;i++){
        scanf("%d",&ar[i]);
    }
    build(1,1,n);
    scanf("%d",&m);
    while(m--){
        int op,l,r,v;
        scanf("%d%d%d",&op,&l,&r);
        if(op==1){
            scanf("%d",&v);
            mul(1,l,r,v);
        }
        else if(op==2){
            scanf("%d",&v);
            add(1,l,r,v);
        }
        else printf("%lld\n",querysum(1,l,r));
    }
}
