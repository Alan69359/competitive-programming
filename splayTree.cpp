#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=1e6+10,M=1e6,INF=0x3f3f3f3f,MOD=1e9+7;

int n,m;
int root,ind;
int pa[N];
int ro[N];

struct Node{
	int ch[2],p,v,id;
	int size;
    int sum;
    int isrotate,isreverse;
	void ini(int p1,int v1){
		p=p1,v=v1;
		size=1;
        sum=0;
        isrotate=isreverse=0;
	}
}tr[N];

void pushup(int x){
    auto &u=tr[x],&l=tr[u.ch[0]],&r=tr[u.ch[1]];
    u.size=l.size+r.size+1;
    u.sum=l.sum+r.sum+u.v;
}

void pushdown(int x){
    auto &u=tr[x],&l=tr[u.ch[0]],&r=tr[u.ch[1]];
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
	int isleft=(tr[y].ch[1]==x);
	tr[z].ch[(tr[z].ch[1]==y)]=x;
    tr[x].p=z;
	tr[y].ch[isleft]=tr[x].ch[isleft^1];
    tr[tr[x].ch[isleft^1]].p=y;
	tr[x].ch[isleft^1]=y;
    tr[y].p=x;
	pushup(y),pushup(x);
}

void splay(int u,int x,int k){
	while(tr[x].p!=k){
		int y=tr[x].p;
        int z=tr[y].p;
		if(z!=k){
			if((tr[y].ch[1]==x)^(tr[z].ch[1]==y)){
				rot(x);
			}
		    else rot(y);
		}
		rot(x);
	}
    if(!k){
//      root=x;
        ro[u]=x;
    }
}

void build(int l,int r,int fa){
    int mid=l+r>>1;
}

void ins(int &u,int x,int i){
    int p=u;
    int pa=0;
	while(p){
		pa=p;
		p=tr[p].ch[(x>tr[p].v)];
	}
	p=++ind;
	if(pa){
		tr[pa].ch[(x>tr[pa].v)]=p;
	}
	tr[p].ini(pa,x);
	splay(u,p,0);
}

int search(int &u,int x){
    int p=u;
    while(p){
        if(tr[p].v==x)break;
        if(tr[p].v<x){
            p=tr[p].ch[1];
        }
        else p=tr[p].ch[0];
    }
    splay(u,p,0);
    return p;
}

int getpreviousnode(int &u,int x){
    int isleft=0;
    int p=search(u,x);
//  int p=root;
    if(tr[p].v<x&&!isleft)return p;
    p=tr[p].ch[isleft];
    while(tr[p].ch[isleft^1]){
        p=tr[p].ch[isleft^1];
    }
    return p;
}

int getnextnode(int &u,int x){
    int isleft=1;
    int p=search(u,x);
//  int p=root;
    if(tr[p].v>x&&isleft)return p;
    p=tr[p].ch[isleft];
    while(tr[p].ch[isleft^1]){
        p=tr[p].ch[isleft^1];
    }
    return p;
}

void rem(int &u,int x){
    int pr=getpreviousnode(u,x);
    int ne=getnextnode(u,x);
    splay(u,pr,0);
    splay(u,ne,pr);
    int le=tr[ne].ch[0];
    if(tr[le].size>1){
        tr[le].size--;
        splay(u,le,0);
    }
    else{
        tr[ne].ch[0]=0;
    }
}

int find(int x){
    if(pa[x]==x)return x;
    else return pa[x]=find(pa[x]);
}

void dfs(int u,int id){
    if(tr[u].ch[0]){
        dfs(tr[u].ch[0],id);
    }
    if(tr[u].ch[1]){
        dfs(tr[u].ch[1],id);
    }
    ins(id,tr[u].v,tr[u].id);
}

void mer(int id1,int id2){
    int a=find(id1),b=find(id2);
    if(a!=b){
        if(tr[ro[a]].size>tr[ro[b]].size){
            swap(a,b);
        }
        dfs(ro[a],b);
        pa[a]=b;
    }
}

int getknum(int u,int k){
//	int p=root;
    int p=ro[u];
	while(p){
		if(tr[tr[p].ch[0]].size>=k){
			p=tr[p].ch[0];
		}
		else if(tr[tr[p].ch[0]].size+1==k){
//			return tr[p].v;
            return tr[p].id;
		}
		else {
			k-=tr[tr[p].ch[0]].size+1;
			p=tr[p].ch[1];
		}
	}
	return -1;
}

int main(){
	return 0;
}
