#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=1e6+10,M=1e6,INF=0x3f3f3f3f,MOD=1e9+7;

int n,m;
int root,idx;
int pa[N];
int root2[N];

struct Node{
	int s[2],p,v,id;
	int size;
    int sum;
    int isrotate,isreverse;
	void ini(int v1,int p1,int id1){
		p=p1,v=v1,id=id1;
		size=1;
        sum=0;
        isrotate=isreverse=0;
	}
}tr[N];

void pushup(int x){
    auto &u=tr[x],&l=tr[u.s[0]],&r=tr[u.s[1]];
    u.size=l.size+r.size+1;
    u.sum=l.sum+r.sum+u.v;
}

void pushdown(int x){
    auto &u=tr[x],&l=tr[u.s[0]],&r=tr[u.s[1]];
	if(u.isrotate){
        swap(l,r);
		l.isrotate^=1;
		r.isrotate^=1;
		u.isrotate=0;
	}
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
//      root=x;
        root2[id]=x;
    }
}

void build(int l,int r,int fa){
    int mid=l+r>>1;
}

void ins(int id,int x,int node_id){
//	int p=root;
    int p=root2[id];
    int fa=0;
	while(p){
		fa=p;
		p=tr[p].s[(x>tr[p].v)];
	}
	p=++idx;
	if(fa){
		tr[fa].s[(x>tr[fa].v)]=p;
	}
	tr[p].ini(x,fa,node_id);
	splay(id,p,0);
}

void search(int id,int x){
//  if(!root)return;
//  int p=root;
    if(!root2[id])return;
    int p=root2[id];
    while(tr[p].s[(x>tr[p].v)]&&tr[p].v!=x){
        p=tr[p].s[(x>tr[p].v)];
    }
    splay(id,p,0);
}

int getpreviousnode(int id,int x){
    int isleft=0;
    search(id,x);
//  int p=root;
    int p=root2[id];
    if(tr[p].v<x&&!isleft)return p;
    p=tr[p].s[isleft];
    while(tr[p].s[isleft^1]){
        p=tr[p].s[isleft^1];
    }
    return p;
}

int getnextnode(int id,int x){
    int isleft=1;
    search(id,x);
//  int p=root;
    int p=root2[id];
    if(tr[p].v>x&&isleft)return p;
    p=tr[p].s[isleft];
    while(tr[p].s[isleft^1]){
        p=tr[p].s[isleft^1];
    }
    return p;
}

void rem(int id,int x){
    int pr=getpreviousnode(id,x);
    int ne=getnextnode(id,x);
    splay(id,pr,0);
    splay(id,ne,pr);
    int le=tr[ne].s[0];
    if(tr[le].size>1){
        tr[le].size--;
        splay(id,le,0);
    }
    else{
        tr[ne].s[0]=0;
    }
}

int find(int x){
    if(pa[x]==x)return x;
    else return pa[x]=find(pa[x]);
}

void dfs(int u,int id){
    if(tr[u].s[0]){
        dfs(tr[u].s[0],id);
    }
    if(tr[u].s[1]){
        dfs(tr[u].s[1],id);
    }
    ins(id,tr[u].v,tr[u].id);
}

void mer(int id1,int id2){
    int a=find(id1),b=find(id2);
    if(a!=b){
        if(tr[root2[a]].size>tr[root2[b]].size){
            swap(a,b);
        }
        dfs(root2[a],b);
        pa[a]=b;
    }
}

int getknum(int id,int k){
//	int p=root;
    int p=root2[id];
	while(p){
		if(tr[tr[p].s[0]].size>=k){
			p=tr[p].s[0];
		}
		else if(tr[tr[p].s[0]].size+1==k){
//			return tr[p].v;
            return tr[p].id;
		}
		else {
			k-=tr[tr[p].s[0]].size+1;
			p=tr[p].s[1];
		}
	}
	return -1;
}

void print(int u){
	pushdown(u);
	if(tr[u].s[0])print(tr[u].s[0]);
	if(tr[u].v>=1&&tr[u].v<=n)printf("%d ",tr[u].v);
	if(tr[u].s[1])print(tr[u].s[1]);
}

int main(){
	return 0;
}
