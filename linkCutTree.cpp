#include<bits/stdc++.h>

using namespace std;

const int N=1e5+10,M=1e5+10,INF=0x3f3f3f3f;

int n,m;

struct Node{
    int s[2],p,w;
    int sum,isreverse;
}tr[N];

int s[N];

void pushrev(int u){
    swap(tr[u].s[0],tr[u].s[1]);
    tr[u].isreverse^=1;
}
void pushup(int u){
    tr[u].sum=tr[tr[u].s[0]].sum^tr[u].w^tr[tr[u].s[1]].sum;
}

void pushdown(int u){
    if(tr[u].isreverse){
        pushrev(tr[u].s[0]),pushrev(tr[u].s[1]);
        tr[u].isreverse=0;
    }
}

bool isroot(int x){
    return tr[tr[x].p].s[0]!=x&&tr[tr[x].p].s[1]!=x;
}

void rotate(int x){
    int y=tr[x].p,z=tr[y].p;
    int k=tr[y].s[1]==x;
    if(!isroot(y))tr[z].s[tr[z].s[1]==y]=x;
    tr[x].p=z;
    tr[y].s[k]=tr[x].s[k^1],tr[tr[x].s[k^1]].p=y;
    tr[x].s[k^1]=y,tr[y].p=x;
    pushup(y),pushup(x);
}

void splay(int x){
    int top=0,r=x;
    s[++top]=r;
    while(!isroot(r)){
        s[++top]=r=tr[r].p;
    }
    while(top){
        pushdown(s[top--]);
    }
    while(!isroot(x)){
        int y=tr[x].p,z=tr[y].p;
        if(!isroot(y)){
            if((tr[y].s[1]==x)^(tr[z].s[1]==y))rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}

void setpath(int x){
    int z=x;
    for(int y=0;x;y=x,x=tr[x].p){
        splay(x);
        tr[x].s[1]=y;
        pushup(x);
    }
    splay(z);
}

void setroot(int x){
    setpath(x);
    pushrev(x);
}

int getroot(int x){
    setpath(x);
    while(tr[x].s[0]){
        pushdown(x);
        x=tr[x].s[0];
    }
    splay(x);
    return x;
}

void split(int x,int y){
    setroot(x);
    setpath(y);
}

void link(int x,int y){
    setroot(x);
    if(getroot(y)!=x){
        tr[x].p=y;
    }
}

void cut(int x,int y){
    setroot(x);
    if(getroot(y)==x&&tr[y].p==x&&!tr[y].s[0]){
        tr[x].s[1]=tr[y].p=0;
        pushup(x);
    }
}
