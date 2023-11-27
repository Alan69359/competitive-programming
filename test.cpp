#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int>pii;

const int N=2000010,M=1e5+10,INF=0x3f3f3f3f,MOD=1e9+7;

int n,m;
int ar[N];
int root,ind;
int pa[N];

struct Node{
	int ch[2],p,v;
	int size;
    int sum;
    int isrotate,isreverse;
	void ini(int p1,int v1){
		p=p1,v=v1;
		size=1;
        sum=0;
        isrotate=isreverse=0;
	}
}tr2[N];

struct Node1 {
    int l,r;
    int root2;
    ll sum;
    ll lazy1,lazy2;
}tr1[N*4];

void ter(){
    printf("program is terminated");
    exit(0);
}

void deb2(int u){
    printf("%d %d %d\n",u,tr1[u].root2,tr2[tr1[u].root2].size);
}

void pushup2(int x){
    auto &u=tr2[x],&l=tr2[u.ch[0]],&r=tr2[u.ch[1]];
    u.size=l.size+r.size+1;
    u.sum=l.sum+r.sum+u.v;
}

void rot(int x){
	int y=tr2[x].p;
    int z=tr2[y].p;
	int isleft=(tr2[y].ch[1]==x);
	tr2[z].ch[(tr2[z].ch[1]==y)]=x;
    tr2[x].p=z;
	tr2[y].ch[isleft]=tr2[x].ch[isleft^1];
    tr2[tr2[x].ch[isleft^1]].p=y;
	tr2[x].ch[isleft^1]=y;
    tr2[y].p=x;
	pushup2(y),pushup2(x);
}

void splay(int &u,int x,int k){
	while(tr2[x].p!=k){
		int y=tr2[x].p;
        int z=tr2[y].p;
		if(z!=k){
			if((tr2[y].ch[1]==x)^(tr2[z].ch[1]==y)){
				rot(x);
			}
		    else rot(y);
		}
		rot(x);
	}
    if(!k){
//      root=x;
        u=x;
    }
}

void ins(int &u,int x){
//	int p=root;
    int p=u;
    int pa=0;
	while(p){
		pa=p;
		p=tr2[p].ch[(x>tr2[p].v)];
	}
	p=++ind;
	if(pa){
		tr2[pa].ch[(x>tr2[pa].v)]=p;
	}
	tr2[p].ini(pa,x);
	splay(u,p,0);
}

void pushup1(int u){
    tr1[u].sum=tr1[u<<1].sum+tr1[u<<1|1].sum;
}

void pushdown1(int u){
    ll lazy1=tr1[u].lazy1,lazy2=tr1[u].lazy2;
    Node1 &le=tr1[u<<1],&ri=tr1[u<<1|1];

    le.sum=(le.sum*lazy2)+(le.r-le.l+1)*lazy1;
    le.lazy1=(le.lazy1*lazy2)+lazy1;
    le.lazy2*=lazy2;

    ri.sum=(ri.sum*lazy2)+(ri.r-ri.l+1)*lazy1;
    ri.lazy1=(ri.lazy1*lazy2)+lazy1;
    ri.lazy2*=lazy2;
    
    tr1[u].lazy1=0;
    tr1[u].lazy2=1;
}

void build1(int u,int l,int r){
    tr1[u]={l,r,0,ar[u]};
    ins(tr1[u].root2,-INF),ins(tr1[u].root2,INF);
    for(int i=l;i<=r;i++){
        ins(tr1[u].root2,ar[i]);
    }
    if(l==r)return;
    int mid=l+r>>1;
    build1(u<<1,l,mid),build1(u<<1|1,mid+1,r);
    //pushup1(u);
}

void pushdown2(int x){
    auto &u=tr2[x],&l=tr2[u.ch[0]],&r=tr2[u.ch[1]];
    if(u.isrotate){
        swap(l,r);
        l.isrotate^=1;
        r.isrotate^=1;
        u.isrotate=0;
    }
}

int search(int &u,int x){
    if(tr2[u].v==x)return u; 
    int p=u;
    while(p){
        if(tr2[p].v==x)break;
        if(tr2[p].v<x){
            p=tr2[p].ch[1];
        }
        else p=tr2[p].ch[0];
    }
    splay(u,p,0);
    return p;
}

int getpreviousnode(int &u,int x){
    int p=search(u,x);
    int pr = tr2[p].ch[0];
    while (tr2[pr].ch[1]) pr = tr2[pr].ch[1];
    return pr;
}

int getnextnode(int &u,int x){
    int p=search(u,x);
    int ne = tr2[p].ch[1];
    while (tr2[ne].ch[0]) ne = tr2[ne].ch[0];
    return ne;
}

void rem(int &u,int x){
    int l = getpreviousnode(u,x);
    int r=getnextnode(u,x);
    // while (tr2[l].ch[1]) l = tr2[l].ch[1];
    // while (tr2[r].ch[0]) r = tr2[r].ch[0];
    splay(u, l, 0), splay(u, r, l);
    tr2[r].ch[0] = 0;
    pushup2(r), pushup2(l);
}

int getrank(int u,int x){
    int p=u;
    int ans=0;
    while(p){
        if(tr2[p].v<x){
            ans+=tr2[tr2[p].ch[0]].size+1;
            p=tr2[p].ch[1];
        }
        else p=tr2[p].ch[0];
    }
    return ans;
}

int getknum(int u,int k){
    //	int p=root;
    int p=u;
    while(p){
        if(tr2[tr2[p].ch[0]].size>=k){
            p=tr2[p].ch[0];
        }
        else if(tr2[tr2[p].ch[0]].size+1==k){
            return tr2[p].v;
        }
        else {
            k-=tr2[tr2[p].ch[0]].size+1;
            p=tr2[p].ch[1];
        }
    }
    return -1;
}

int que1(int u,int l,int r,int x){
    if(tr1[u].l>=l&&tr1[u].r<=r){
        return getrank(tr1[u].root2,x)-1;
    }
    int mid=tr1[u].l+tr1[u].r>>1;
    int ans=0;
    if(l<=mid)ans+=que1(u<<1,l,r,x);
    if(r>mid)ans+=que1(u<<1|1,l,r,x);
    return ans;
}

void mod1(int u,int l,int x){
    rem(tr1[u].root2,ar[l]);
    ins(tr1[u].root2,x);
    if(tr1[u].l==tr1[u].r)return;
    int mid=tr1[u].l+tr1[u].r>>1;
    if(l<=mid)mod1(u<<1,l,x);
    else mod1(u<<1|1,l,x);
}

int que2(int u,int l,int r,int x){
    if(tr1[u].l>=l&&tr1[u].r<=r){
        return tr2[getpreviousnode(tr1[u].root2,x)].v;
        //return getpreviousnode(tr1[u].root2,x);
    }
    int mid=tr1[u].l+tr1[u].r>>1;
    int ans=-INF;
    if(l<=mid){
        ans=max(ans,que2(u<<1,l,r,x));
    }
    if(r>mid){
        ans=max(ans,que2(u<<1|1,l,r,x));
    }
    return ans;
}

int que3(int u,int l,int r,int x){
    //pushup2(tr1[u].root2);
    if(tr1[u].l>=l&&tr1[u].r<=r){
        return tr2[getnextnode(tr1[u].root2,x)].v;
        //return getnextnode(tr1[u].root2,x);
    }
    int mid=tr1[u].l+tr1[u].r>>1;
    int ans=INF;
    if(l<=mid){
        ans=min(ans,que3(u<<1,l,r,x));
    }
    if(r>mid){
        ans=min(ans,que3(u<<1|1,l,r,x));
    }
    return ans;
}

void deb(){
    for(int i=1;i<=n;i++){
        printf("[%d, %d], %d, %d\n",tr1[i].l,tr1[i].r,tr1[i].root2,tr2[tr1[i].root2].size);
    }
    printf("\n");
}

void pri(int u){
    if(!u)return;
    pri(tr2[u].ch[0]);
    printf("%d ",tr2[u].v);
    pri(tr2[u].ch[1]);
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&ar[i]);
    }
    build1(1,1,n);
    while(m--){
        int op;
        int l,r,x;
        scanf("%d",&op);
        if(op==1){
            scanf("%d%d%d",&l,&r,&x);
            printf("%d\n",que1(1,l,r,x)+1);
        }
        else if(op==2){
            scanf("%d%d%d",&l,&r,&x);
            int le=0,ri=1e8;
            while(le<ri){
                int mid=le+ri+1>>1;
                if(que1(1,l,r,mid)+1<=x){
                    le=mid;
                }
                else ri=mid-1;
            }
            printf("%d\n",le);
        }
        else if(op==3){
            scanf("%d%d",&l,&x);
            mod1(1,l,x);
            ar[l]=x;
        }
        else if(op==4){
            scanf("%d%d%d",&l,&r,&x);
            printf("%d\n",que2(1,l,r,x));
        }
        else {
            scanf("%d%d%d",&l,&r,&x);
            printf("%d\n",que3(1,l,r,x));
        }
    }
}
