#include<bits/stdc++.h>

using namespace std;

const int N=1500010,INF=1e9;

int n,m;
int a[N];
int idx;

struct Tree{
    int s[2],p,v,id;
    int si;
    void ini(int p1,int v1,int id1){
        p=p1,v=v1;
        si=1;
        id=id1;
    }
}tr[N];

int root2[N];

void init(){
    memset(root2,0,sizeof root2);
}

void pushup(int u){
    tr[u].si=tr[tr[u].s[0]].si+tr[tr[u].s[1]].si+1;
}

void rot(int x){
    int y=tr[x].p;
    int z=tr[y].p;
    int isleft=(tr[y].s[1]==x);
    tr[z].s[(tr[z].s[1]==y)]=x;
    tr[x].p=z;
    tr[y].s[isleft]=tr[x].s[isleft^1];
    tr[tr[x].s[isleft^1]].p=y;
    tr[x].s[isleft^1]=y;
    tr[y].p=x;
    pushup(y),pushup(x);
}

void splay(int id,int x,int k){
    while(tr[x].p!=k){
        int y=tr[x].p;
        int z=tr[y].p;
        if(z!=k){
            if((tr[y].s[1]==x)^(tr[z].s[1]==y)){
                rot(x);
            }
            else rot(y);
        }
        rot(x);
    }
    if(!k){
        root2[id]=x;
        
    }
}

void ins(int id,int x,int node_id){
    int p=root2[id];
    int fa=0;
    while(p){
        fa=p;
        //printf("%d\n",tr[p].v);
        p=tr[p].s[(x>tr[p].v)];
    }
    p=++idx;
    if(fa){
        tr[fa].s[(x>tr[fa].v)]=p;
    }
    tr[p].ini(fa,x,node_id);
    splay(id,p,0);
}

// int getknum(int id,int k){
//     int p=root2[id];
//     while(p){
//         if(tr[tr[p].s[0]].si>=k){
// 			p=tr[p].s[0];
//         }
//         else if(tr[tr[p].s[0]].si+1==k){
//             return tr[p].v;
//         }
//         else {
//             k-=tr[tr[p].s[0]].si+1;
//             p=tr[p].s[1];
//         }
//     }
//     return -1;
// }

int getknum(int id, int v)
{
    int p=root2[id];
    int ans=0;
    while (p)
    {
        if (tr[p].v < v){
            ans += tr[tr[p].s[0]].si + 1;
            p = tr[p].s[1];
        }
        else p = tr[p].s[0];
    }
    return ans;
}

void rem(int id,int x,int y){
    int &p=root2[id];
    while(p){
        if(tr[p].v==x)break;
        if(tr[p].v<x)p=tr[p].s[1];
        else p=tr[p].s[0];
    }
    splay(p,x,0);
    int l=tr[p].s[0],r=tr[p].s[1];
    while(tr[l].s[1])l=tr[l].s[1];
    while(tr[r].s[0])r=tr[r].s[0];
    splay(id,l,0);
    splay(id,r,l);
    tr[r].s[0]=0;
    pushup(r),pushup(l);
    ins(id,y,++idx);
}

// int getpre(int id,int v){
//     int p=root2[id];
//     int res=INF;
//     while(p){
//         if(tr[p].v<v){
//             res=max(res,tr[p].v);
//             p=tr[p].s[1];
//         }
//         else p=tr[p].s[0];
//     }
//     return res;
// }

// int getsuc(int id,int v){
//     int p=root2[id];
//     int res=INF;
//     while(p){
//         if(tr[p].v>v){
//             res=min(res,tr[p].v);
//             p=tr[p].s[0];
//         }
//         else p=tr[p].s[1];
//     }
//     return res;
// }

void search(int id,int x){
    if(!root2[id])return;
    int p=root2[id];
    while(tr[p].s[(x>tr[p].v)]&&tr[p].v!=x){
        p=tr[p].s[(x>tr[p].v)];
    }
    splay(id,p,0);
}

int getpre(int id,int x){
    int isleft=0;
    search(id,x);
    int p=root2[id];
    if(tr[p].v<x&&!isleft){
        return p;
    }
    p=tr[p].s[isleft];
    while(tr[p].s[isleft^1]){
        p=tr[p].s[isleft^1];
    }
    return p;
}

int getnex(int id,int x){
    int isleft=1;
    search(id,x);
    int p=root2[id];
    if(tr[p].v>x&&isleft)return p;
    p=tr[p].s[isleft];
    while(tr[p].s[isleft^1]){
        p=tr[p].s[isleft^1];
    }
    return p;
}

struct Node{
    int l,r;
}se[N];

void build(int u,int l,int r){
    ins(u,-INF,++idx),ins(u,INF,++idx);
    //exit(0);
    for(int i=l;i<=r;i++){
        ins(u,a[i],++idx);
    }
    if(l==r)se[u]={l,r};
    else{
        se[u]={l,r};
        int mid=l+r>>1;
        build(u<<1,l,mid),build(u<<1|1,mid+1,r);
    }
}

int que(int u,int l,int r,int x){
    if(se[u].l>=l&&se[u].r<=r){
        return getknum(u,x)-1;
    }
    else{
        int mid=se[u].l+se[u].r>>1;
        int ans=0;
        if(l<=mid)ans+=que(u<<1,l,r,x);
        if(r>mid)ans+=que(u<<1|1,l,r,x);
        return ans;
    }
}

void modifySplay(int id,int x,int y){
    search(id,x);
    printf("id of x: %d\n",root2[id]);
    int l=tr[id].s[0],r=tr[id].s[1];
    while(tr[l].s[1]){
        l=tr[l].s[1];
    }
    while(tr[r].s[0]){
        r=tr[r].s[0];
    }
    splay(id,l,0),splay(id,r,l);
    tr[r].s[0]=0;
    pushup(r),pushup(l);
    ins(id,y,idx++);
}

void modifySegment(int u,int p,int y){
    modifySplay(u,a[p],y);
    if(se[u].l==se[u].r)return;
    else{
        int mid=se[u].l+se[u].r>>1;
        if(p<=mid){
            modifySegment(u<<1,p,y);
        }
        else modifySegment(u<<1|1,p,y);
    }
}

int que2(int u,int l,int r,int x){
    if(se[u].l>=l&&se[u].r<=r)return getpre(u,x);
    else{
        int mid=se[u].l+se[u].r>>1;
        int ans=-INF;
        if(l<=mid)ans=max(ans,que2(u<<1,l,r,x));
        if(r>mid)ans=max(ans,que2(u<<1|1,l,r,x));
        return ans;
    }
}

int que3(int u,int l,int r,int x){
    if(se[u].l>=l&&se[u].r<=r)return getnex(u,x);
    else{
        int mid=se[u].l+se[u].r>>1;
        int ans=INF;
        if(l<=mid)ans=min(ans,que3(u<<1,l,r,x));
        if(r>mid)ans=min(ans,que3(u<<1|1,l,r,x));
        return ans;
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    init();
    build(1,1,n);
    while(m--){
        int op,l,r,x;
        scanf("%d",&op);
        if(op==1){
            scanf("%d%d%d",&l,&r,&x);
            printf("%d\n",que(1,l,r,x)+1);
        }
        else if(op==2){
            scanf("%d%d%d",&l,&r,&x);
            /*printf("%lld\n",que(1,3,8,2));*/
            /*exit(0);*/
            int l2=0,r2=1e8;
            while(l2<r2){
                int mid=l2+r2+1>>1;
                if(que(1,l,r,mid)+1<=x)l2=mid;
                else r2=mid-1;
            }
            printf("%d\n",r2);
        }
        else if(op==3){
            scanf("%d%d",&l,&x);
            modifySegment(1,l,x);
            a[l]=x;
        }
        else if(op==4){
            scanf("%d%d%d",&l,&r,&x);
            printf("%d\n",que2(1,l,r,x));
        }
        else{
            scanf("%d%d%d",&l,&r,&x);
            printf("%d\n",que3(1,l,r,x));
        }
    }
}
